//
//  lock_free_queue.h
//  Lock Free Queue (Address Sanitizer)
//
//  Created by Ирина Дмитриева on 11.12.16.
//  Copyright © 2016 Ирина Дмитриева. All rights reserved.
//
#include <atomic>

template <typename T>
class lock_free_queue {
private:
    struct node {
        T data;
        std::atomic<node*> next;
        
        node(T data_) : data(data_), next(nullptr) {}
        node() : next(nullptr) {}
    };
    
    node* head_of_list_to_delete;
    std::atomic<node*> head;
    std::atomic<node*> tail;
    
public:
    lock_free_queue() {
        node* new_node = new node();
        head.store(new_node);
        tail.store(new_node);
        head_of_list_to_delete = new_node;
    }
    
    void enqueue(T data) {
        node* new_node = new node(data);
        node* current_tail;
        node* current_tail_next;
        
        while (true) {
            current_tail = tail.load();
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
    }
    
    bool dequeue(T& data) {
        node* current_head;
        node* current_tail;
        node* current_head_next;
        
        while (true) {
            current_head = head.load();
            current_tail = tail.load();
            current_head_next = current_head->next;
            if (current_head == current_tail) {
                if (!current_head_next) {
                    return false;
                } else {
                    //helping another thread
                    tail.compare_exchange_strong(current_head, current_head_next);
                }
            } else {
                if (head.compare_exchange_strong(current_head, current_head_next)) {
                    data = current_head_next->data;
                    return true;
                }
            }
        }
    }
    
    ~lock_free_queue() {
        while (true) {
            node* current_node = head_of_list_to_delete;
            node* next_node = current_node->next;
            if (next_node == nullptr) {
                delete(current_node);
                break;
            }
            head_of_list_to_delete = next_node;
            delete(current_node);
        }
    }
    
};
