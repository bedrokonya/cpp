#include "CGraph.h"
#include "Bfs.h"
#include <iostream>
#include <vector>
#include "Bfs.h"
#include "Dfs.h"
#include "Tests.h"
//#include <random>



int main() {
    /*
    CGraph<int, int>* gr = new CGraph<int, int>();

    
    gr->AddVertex(0);
    gr->AddVertex(1);
    gr->AddVertex(2);
    gr->AddVertex(3);
    gr->AddVertex(4);
    gr->AddDirectedEdge(0, 1, 15);
    gr->AddDirectedEdge(1, 0, 15);
    gr->AddDirectedEdge(0, 2, 4);
    gr->AddDirectedEdge(2, 0, 4);
    gr->AddDirectedEdge(0, 4, 7);
    gr->AddDirectedEdge(4, 0, 7);
    gr->AddDirectedEdge(1, 3, 17);
    gr->AddDirectedEdge(3, 1, 17);
    gr->AddDirectedEdge(1, 2, 3);
    gr->AddDirectedEdge(2, 1, 3);
    gr->AddDirectedEdge(2, 3, 10);
    gr->AddDirectedEdge(3, 2, 10);
    gr->AddDirectedEdge(2, 4, 11);
    gr->AddDirectedEdge(4, 2, 11);
    
    CBfs<int, int>* bfs = new CBfs<int, int>(5, gr->GetVertex(0));
    CDfs<int, int>* dfs = new CDfs<int, int>(5, gr->GetVertex(0));
    bfs->RunCBfs();
    bfs->CheckCBfs();
    dfs->RunCDfs();
    dfs->CheckCDfs();
*/
    int N;
    CGraph<int, int> gr;
    CGraph<int, int> &ref = gr;
    std::cout << "Enter the number of graphs, which you want to test\n";
    std::cin >> N;
    Tester<int, int> test(N);
    //test.genGraph(ref);
    test.test(ref);
    
    
    
    return 0;
}