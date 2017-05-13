
#include "hash_table.h"
#include <iostream>
#include <cassert>

int main()
{
    CHashTable hashTable;
    while( true ) {
        char command = 0;
        std::cin >> command;
        if( std::cin.eof() ) {
            return 0;
        }
        std::string key;
        std::cin >> key;
        switch( command ) {
            case '?':
                std::cout << ( hashTable.Has( key ) ? "OK" : "FAIL" ) << std::endl;
            case '+':
                std::cout << ( hashTable.Add( key ) ? "OK" : "FAIL" ) << std::endl;
            case '-':
                std::cout << ( hashTable.Remove( key ) ? "OK" : "FAIL" ) << std::endl;
                break;
            default:
                assert( false );
                
        }
    }
}