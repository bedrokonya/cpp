#include <atomic>
#include <thread>

unsigned const MAX_HAZARD_POINTERS = 100;

struct HazardPointer
{
    std::atomic<std::thread::id> id;
    std::atomic<void*> pointer;
};
HazardPointer g_hazardPointers[MAX_HAZARD_POINTERS];

class HPOwner
{
public:
    HPOwner(const HPOwner&) = delete;
    HPOwner operator=(const HPOwner&) = delete;
    
    HPOwner()
    : hp_(nullptr)
    {
        for (unsigned i = 0; i < MAX_HAZARD_POINTERS; ++i) {
            std::thread::id oldId;
            if (g_hazardPointers[i].id.compare_exchange_strong(
                                                               oldId, std::this_thread::get_id())) {
                hp_ = &g_hazardPointers[i];
                break;
            }
        }
        if (!hp_) {
            throw std::runtime_error("No hazard pointers available");
        }
    }
    
    std::atomic<void*>& getPointer()
    {
        return hp_->pointer;
    }
    
    ~HPOwner()
    {
        hp_->pointer.store(nullptr);
        hp_->id.store(std::thread::id());
    }
    
private:
    HazardPointer* hp_;
};

std::atomic<void*>& getHazardPointerForCurrentThread()
{
    thread_local static HPOwner hazard;
    return hazard.getPointer();
}

bool outstandingHazardPointersFor(void* p)
{
    for (unsigned i = 0; i < MAX_HAZARD_POINTERS; ++i) {
        if (g_hazardPointers[i].pointer.load() == p) {
            return true;
        }
    }
    return false;
}

template<typename T>
void doDelete(void* p)
{
    delete static_cast<T*>(p);
}

struct DataToReclaim
{
    void* data;
    std::function<void(void*)> deleter;
    DataToReclaim* next;
    
    template<typename T>
    DataToReclaim(T* p)
    : data(p)
    , deleter(&doDelete<T>)
    , next(nullptr)
    {}
    
    ~DataToReclaim()
    {
        deleter(data);
    }
};

std::atomic<DataToReclaim*> nodesToReclaim;

void addToReclaimList(DataToReclaim* node)
{
    node->next = nodesToReclaim.load();
    while (!nodesToReclaim.compare_exchange_weak(node->next, node));
}

template<typename T>
void reclaimLater(T* data)
{
    addToReclaimList(new DataToReclaim(data));
}

void deleteNodesWithNoHazards()
{
    DataToReclaim* current = nodesToReclaim.exchange(nullptr);
    while (current) {
        DataToReclaim* const next = current->next;
        if (!outstandingHazardPointersFor(current->data)) {
            delete current;
        } else {
            addToReclaimList(current);
        }
        current = next;
    }
}


template <typename T>
class lock_free_queue {
private:
    struct node {
        T data;
        std::atomic<node*> next;
        
        node(T data_) : data(data_), next(nullptr) {}
        node() : next(nullptr) {}
    };
    
    std::atomic<node*> head;
    std::atomic<node*> tail;
    
public:
    lock_free_queue() {
        node* new_node = new node();
        head.store(new_node);
        tail.store(new_node);
    }
    
    void enqueue(T data) {
        std::atomic<void*>& hp = getHazardPointerForCurrentThread();
        node* new_node = new node(data);
        node* current_tail;
        node* current_tail_next;
        
        while (true) {
            current_tail = tail.load();
            node* temp = nullptr;
            do {
                temp = current_tail;
                hp.store(temp);
                current_tail = tail.load();
            } while (current_tail != temp);
            current_tail_next = tail.load()->next.load();
            if (!current_tail_next) {
                if(tail.load()->next.compare_exchange_weak(current_tail_next, new_node)) {
                    break;
                }
            } else {
                // helping another thread
                tail.compare_exchange_strong(current_tail, current_tail_next);
            }
        }
        tail.compare_exchange_strong(current_tail, new_node);
        hp.store(nullptr);
    }
    
    bool dequeue(T& data) {
        while (true) {
            node* current_head = head.load();
            node* temp1 = nullptr;
            node* temp2 = nullptr;
            do {
                temp1 = current_head;
                std::atomic<void*>& hp_for_head = getHazardPointerForCurrentThread();
                hp_for_head.store(temp1);
                current_head = head.load();
            } while (current_head != temp1);
            node* current_tail = tail.load();
            node* current_head_next = current_head->next.load();
            HPOwner hp_owner;
            do {
                temp2 = current_head_next;
                std::atomic<void*>& hp_for_head_next = hp_owner.getPointer();
                hp_for_head_next.store(temp2);
                current_head_next = current_head->next.load();

            } while (current_head_next != temp2);
            
            if (current_head == current_tail) {
                if (!current_head_next) {
                    std::atomic<void*>& hp_for_head = getHazardPointerForCurrentThread();
                    hp_for_head.store(nullptr);
                    return false;
                } else {
                    //helping another thread
                    tail.compare_exchange_strong(current_head, current_head_next);
                }
            } else {
                if (head.compare_exchange_strong(current_head, current_head_next)) {
                    data = current_head_next->data;
                    reclaimLater(current_head);
                    deleteNodesWithNoHazards();
                    std::atomic<void*>& hp_for_head = getHazardPointerForCurrentThread();
                    hp_for_head.store(nullptr);
                    return true;
                }
            }
        }
    }

    ~lock_free_queue() {
        T tmp;
        while (dequeue(tmp)) {}
        delete head.load();
    }
    
};

