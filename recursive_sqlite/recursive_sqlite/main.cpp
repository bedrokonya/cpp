#include <stdio.h>
#include <sqlite3.h>
#include <sqlite3ext.h>
#include <iostream>

int main(int argc, const char * argv[]) {
    sqlite3 *db;
    int rc;
    
    rc = sqlite3_open("ancestors", &db);
    
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }
    
    sqlite3_close(db);
    return 0;
}
