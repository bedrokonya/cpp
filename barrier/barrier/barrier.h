#include <thread>
#include <condition_variable>
#include <mutex>


class barrier {
public:
    explicit barrier(std::size_t num_threads);
    void enter();
private:
    std::size_t _counter;
    std::size_t _num_threads;
    std::condition_variable gates;
    std::mutex mut;
};

barrier::barrier(std::size_t num_threads) {
    _num_threads = num_threads;
    _counter = 0;
}

void barrier::enter() {
    std::unique_lock<std::mutex> lock(mut);
    std::cout << "entered the gates! \n";
    if (_counter != _num_threads - 1) {
        _counter++;
        gates.wait(lock);
        //lock.unlock();
    }
    else {
        _counter = 0;
        gates.notify_all();
        
    }
    std::cout << "exit the gates! \n";
    lock.unlock();
}
