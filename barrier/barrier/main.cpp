//
//  main.cpp
//  barrier
//
//  Created by macbook on 04.10.16.
//  Copyright © 2016 macbook. All rights reserved.
//

#include <iostream>
#include "barrier.h"

void f(barrier& b) {
    for (int i = 0; i < 1000; i++){
        //std::cout << i << "entered the gates! \n";
        b.enter();
        //std::cout << i << "exit the gates! \n";
    }
}


int main() {
    barrier barr(2);
    
    std::thread thr1(f, std::ref(barr));
    std::thread thr2(f, std::ref(barr));
    //std::thread thr3(f, std::ref(barr));
    thr1.join();
    thr2.join();
    //thr3.join();
    return 0;
}
