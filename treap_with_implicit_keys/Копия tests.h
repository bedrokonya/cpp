
#ifndef tests_h
#define tests_h

#include "treap_implicit_keys.h"
#include "next_permutation.h"
#include "naive_next_permutation.h"

void testing(NextPermutation *real, int n, int minInt, int maxInt) {
    int gap = maxInt - minInt + 1;
    int start = rand() % gap + minInt;
    Vect ev = Vect(start);
    real->Insert(start, 0);
    int cnt = 1;
    std::vector<int> test;
    std::vector<int> right;
    for (size_t i = 0; i < n; ++i)
    {
        int t = 0, a = 0, b = 0, c = 0;
        t = rand() % 5;
        if (t == 0) //INSERT
        {
            a = rand() % gap + minInt;
            b = rand() % (cnt + 1);
            real->Insert(a, b);
            ev.Insert(a, b);
            ++cnt;
        }
        if (t == 1)  //SETUP
        {
            a = rand() % gap + minInt;
            b = rand() % cnt;
            real->SetUp(a, b);
            ev.SetUp(a, b);
        }
        if (t == 2) //SUMSEGMENT
        {
            a = rand() % cnt;
            b = rand() % cnt;
            if (a > b)
                std::swap(a, b);
            if (real->SumSegment(a, b) != ev.SumSegment(a, b))
                std::cout << "error" << ' ' << i << std::endl;
        }
        
        if (t == 3) //NEXTPERMUTATION
        {
            a = rand() % cnt;
            b = rand() % cnt;
            if (a > b)
                std::swap(a, b);
            right.clear();
            ev.Print(right);
            for (size_t i = a; i < b; ++i)
            {
                if (right[i] < right[i + 1])
                {
                    real->nextPermutation(a, b);
                    ev.nextPermutation(a, b);
                    break;
                }
            }
        }
        std::cout << t << ' ' << a << ' ' << b << ' ';
        if (t == 3)
            std::cout << c;
        std::cout << std::endl;
    }
    
    real->Print(test);
    right.clear();
    ev.Print(right);
    if (test.size() != right.size())
        std::cout << "error" << std::endl;
    for (size_t i = 0; i < test.size(); ++i)
        if (test[i] != right[i])
            std::cout << "error" << std::endl;
}

#endif /* tests_h */
