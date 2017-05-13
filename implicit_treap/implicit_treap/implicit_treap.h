
//
//  implicit_treap.h
//  implicit_treap
//
//  Created by macbook on 28.02.16.
//  Copyright © 2016 macbook. All rights reserved.
//

#ifndef implicit_treap_h
#define implicit_treap_h

class ImplicitTreap {
private:
    int cost;
    ImplicitTreap* left;
    ImplicitTreap* right;
    ImplicitTreap* leftmost;
    ImplicitTreap* rightmost;
    int sorted_suffix;
    int priority;
    int size;
    int sum_segment;
    bool reversed;
public:
    //ImplicitTreap();
    
    ImplicitTreap(int _cost, int _priority, ImplicitTreap* _left, ImplicitTreap* _right);
    

    ~ImplicitTreap();
    
    ImplicitTreap* Merge(ImplicitTreap* &left, ImplicitTreap* &right);
    
    void Split(int x, ImplicitTreap* &left, ImplicitTreap* &right);
    
    ImplicitTreap* Add(int pos, int _priority);
    
    ImplicitTreap* Remove(int pos);
    
    int SumOnSubsegment(int a, int b);
    
    ImplicitTreap* Reverse(int a, int b);
    
    int SizeOf(ImplicitTreap* trp);
    
    int SumOf(ImplicitTreap* trp);
    
    int SizeOfSortedSuffix(ImplicitTreap* trp);
    
    void Push(ImplicitTreap* trp);
    
    void Recalc();
    
    void RecalcSortedSuffix(ImplicitTreap* trp);
    
    void Print();
};

#endif /* implicit_treap_h */
