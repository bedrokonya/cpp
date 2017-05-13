

#include <iostream>
#include <thread>
#include "barrier.h"


void f(barrier& b) {
    for (int i = 0; i < 3; i++){
        b.enter();
    }
}

int main() {
    barrier barr(3);
    
    std::thread thr1(f, std::ref(barr));
    std::thread thr2(f, std::ref(barr));
    std::thread thr3(f, std::ref(barr));
    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}
