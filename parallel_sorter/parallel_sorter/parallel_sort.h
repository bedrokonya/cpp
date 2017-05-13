#include <queue>
#include <future>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>

template <class Value>
class thread_pool {
    
    std::atomic<bool> all_tasks_completed;
    std::queue<std::packaged_task<Value()>> tasks_queue;
    std::vector<std::thread> workers;
    size_t num_workers;
    
    std::mutex mut;
    std::condition_variable cond_var;
    
    void worker_thread() {
        while(!all_tasks_completed) {
            std::unique_lock<std::mutex> locker(mut);
            cond_var.wait(locker, [&]() {return all_tasks_completed || !tasks_queue.empty();} );
            while (!tasks_queue.empty()) {
                locker.unlock();
                run_pending_task();
                locker.lock();
            }
        }
    }
    
public:
    explicit thread_pool(size_t _num_workers) : all_tasks_completed(false) {
        num_workers = _num_workers;
        try {
            for (std::size_t i = 0; i < num_workers; i++) {
                workers.push_back(std::thread(&thread_pool::worker_thread, this));
            }
        }
        catch(...) {
            all_tasks_completed = true;
            throw std::runtime_error("The launch of thread was completed with exception");
        }
    }
    
    std::future<Value> submit(std::function<Value()> f) {
        if (!all_tasks_completed) {
            std::packaged_task<Value()> task(std::move(f));
            std::future<Value> result(task.get_future());
            std::unique_lock<std::mutex> locker(mut);
            tasks_queue.push(std::move(task));
            locker.unlock();
            cond_var.notify_all();
            return result;
        } else {
            throw std::runtime_error("Can't submit after shutdown");
        }
        
    }
    void run_pending_task() {
        std::unique_lock<std::mutex> locker(mut);
        if (!tasks_queue.empty()) {
            std::packaged_task<Value()> pending_task(std::move(tasks_queue.front()));
            tasks_queue.pop();
            locker.unlock();
            pending_task();
        }
        else {
            locker.unlock();
        }
    }
    
    void shutdown() {
        all_tasks_completed = true;
        cond_var.notify_all();
        for (std::size_t i = 0; i < workers.size(); i++) {
            if (workers[i].joinable()) {
                workers[i].join();
            }
        }
    }
};



class parallel_sort {
    thread_pool<void> _thread_pool;
public:
    explicit parallel_sort(size_t num_threads) : _thread_pool(num_threads) {}
    
    template <class RandomAccessIterator, class Compare>
    void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        if (last - first <= 5000) {
            std::sort(first, last, comp);
            return;
        }
        
        RandomAccessIterator middle =  first + ((last - first)/2);
        
        std::future<void> left_part_sorted =
        _thread_pool.submit(std::bind(&parallel_sort::sort<RandomAccessIterator, Compare>, this, first, middle, comp));
        
        sort(middle, last, comp);
        
        while (left_part_sorted.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            _thread_pool.run_pending_task();
        }
        
        std::inplace_merge(first, middle, last, comp);
    }
    
    ~parallel_sort() {
        _thread_pool.shutdown();
    }
};
