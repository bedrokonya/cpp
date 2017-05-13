#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

/*Параметр num_threads определяет число потоков, синхронизуемых барьером.
 Метод void enter() блокируется, пока все num_threads потоков его не вызовут, после чего все заблокированные потоки продолжат исполнение. Цикличность барьера означает, что вызвать у него N раз enter в одном и том же потоке эквивалентно тому, чтобы вызвать enter у N барьеров по одному разу.
 
 Сложность реализации циклического барьера состоит в обработке следующей ситуации: поток, только покинувший барьер, может тут же подойти к нему снова, пока остальные потоки его еще не покинули. Поэтому идея с простым счетчиком потоков не работает.
 Первый способ - обнаружить такую ситуацию с помощью эпох (или поколений). Эпоха - это счетчик, который инкрементируется в тот момент, когда все потоки подошли к барьеру.
 Другой способ - сделать в барьере пару виртуальных ворот: одни на вход, другие - на выход. Войти в первые ворота нельзя, пока есть потоки, которые не вышли через вторые ворота.
*/

class barrier {
public:
    explicit barrier(std::size_t num_threads);
    void enter();
private:
    std::size_t _counter;
    std::size_t _another_counter;
    std::size_t _num_threads;
    std::size_t _generation;
    std::size_t _next_generation;
    std::size_t _one_more_counter;
    std::mutex mut;
    std::mutex mut2;
    
    std::condition_variable cond_var;
    std::condition_variable gates;
};

barrier::barrier(std::size_t num_threads) {
    this->_num_threads = num_threads;
    _generation = 0;
    _next_generation = 1;
    _another_counter = 0;
    _one_more_counter = num_threads;
    _counter = 0;
}

void barrier::enter() {
    // не работает(((
    while (_counter < _num_threads) {
        std::unique_lock<std::mutex> lock(mut);
        _counter++;
        //_another_counter++;
        if (_counter == _num_threads)
            _generation++;
        while(!(_generation == _next_generation) || !(_counter == _num_threads)) {
            cond_var.wait(lock);
        }
        cond_var.notify_one();
        //_another_counter--;
    }
    

    //_one_more_counter = _num_threads;
    //_another_counter = 0;
    std::unique_lock<std::mutex> lock(mut2);
    while(_another_counter != _num_threads - 1) {
        _another_counter++;
        gates.wait(lock);
    }
    _counter = 0;
    _next_generation = _generation + 1;
    gates.notify_all();
    _one_more_counter--;
    if (_one_more_counter == 0) {
        _another_counter = 0;
        _one_more_counter = _num_threads;
    }
}
