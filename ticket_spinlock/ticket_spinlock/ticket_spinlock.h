#include <atomic>
#include <thread>

class ticket_spinlock {
    using ticket = std::size_t;
public:
    ticket_spinlock() : owner_ticket(0), next_free_ticket(0) {}
    void lock() {
        ticket this_thread_ticket = next_free_ticket.fetch_add(1);
        while (owner_ticket.load() != this_thread_ticket) {
            std::this_thread::yield();
        }
    }
    
    void unlock() {
        owner_ticket.store(owner_ticket.load() + 1);
    }
    
private:
    std::atomic<ticket> owner_ticket;
    std::atomic<ticket> next_free_ticket;
};


