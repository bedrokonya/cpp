//
//  thread_safe_queue.h
//  thread_safe_queue
//
//  Created by macbook on 04.11.16.
//  Copyright © 2016 macbook. All rights reserved.
//
#include <deque>
#include <condition_variable>
#include <mutex>
/*
 Метод void enqueue(Value v) добавляет элемент в конец очереди. Ожидаемое поведение и инварианты:
 вызов метода enqueue добавляет в очередь ровно один элемент;
 после вызова shutdown любой вызов метода enqueue должен кидать исключение;
 метод enqueue гарантирует, что число элементов в очереди не превысит capacity;
 если в очереди уже capacity элементов, вызов метода enqueue блокируется, пока число элементов в очереди не уменьшится.
 
 Метод void pop(Value& v) извлекает первый элемент из очереди. Ожидаемое поведение и инварианты:
 вызов метода pop извлекает из очереди ровно один элемент;
 вызов метода pop блокируется, если очередь пуста;
 после вызова shutdown вызов метода pop продолжает извлекать элементы из очереди, пока она не опустеет, любой вызов pop на пустой очереди после shutdown должен кидать исключение.
 
 Метод void shutdown() переводит очередь в режим завершения работы. Ожидаемое поведение и инварианты:
 метод shutdown не блокируется;
 после вызова shutdown любой вызов enqueue кидает исключение, заблокированные вызовы enqueue разблокируются и кидают исключение;
 после вызова shutdown любой вызов pop на пустой очереди кидает исключение, заблокированные на пустой очереди вызовы pop разблокируются и, если очередь пуста, кидают исключение.
 
 
 size_t size() const;
 bool empty() const;
 Value& front();
 void pop_front();
 void push_back(Value&&);
 */

/*
#ifndef thread_safe_queue_h
#define thread_safe_queue_h*/
template <class Value, class Container = std::deque<Value>>
class thread_safe_queue {
    //size_t current_num_of_elements;
    size_t capacity;
    std::condition_variable queue_is_not_empty;
    std::condition_variable queue_is_not_full;
    std::mutex mut;
    Container data_queue;
    std::atomic<bool> work_completed;
public:
    explicit thread_safe_queue(size_t _capacity) {
        work_completed = false;
        capacity = _capacity;
        //data_deque = new std::deque<Value>;
        //current_num_of_elements = 0;
    }
    
    void enqueue(Value v) {
        if (work_completed) {
            throw std::runtime_error("Can't enqueue after shutdown");
        }
        std::unique_lock<std::mutex> locker(mut);
        if (data_queue.size() == capacity) {
            queue_is_not_full.wait(locker, [&]() { return data_queue.size() < capacity || work_completed; });
            if (work_completed) {
                throw std::runtime_error("Can't enqueue after shutdown");
            }
        }
        if (data_queue.size() < capacity) {
            data_queue.push_back(std::move(v));
            queue_is_not_empty.notify_all();
        }
        locker.unlock();
    }
    
    void pop(Value& v) {
        std::unique_lock<std::mutex> locker(mut);
        if(data_queue.empty()) {
            queue_is_not_empty.wait(locker, [&]() { return data_queue.size() > 0 || work_completed; });
        }
        if (data_queue.size() > 0) {
            v = std::move(data_queue.front());
            data_queue.pop_front();
            queue_is_not_full.notify_all();
            locker.unlock();
        } else if (work_completed) {
            throw std::runtime_error("Queue is epmty");
        }
    }
    
    void shutdown() {
        work_completed = true;
        queue_is_not_empty.notify_all();
        queue_is_not_full.notify_all();
    }
};


/*#endif thread_safe_queue_h */
