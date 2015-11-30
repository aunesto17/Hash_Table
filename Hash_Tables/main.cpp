//
//  main.cpp
//  Hash_Tables
//
//  Created by Alexander Arturo Baylon Ibanez on 9/11/15.
//  Copyright © 2015 aunesto17. All rights reserved.
//

#include "HashTable.h"

int main(int argc, const char * argv[]) {
    
    //Guardamos todas las palabras en un string.
    HashTable<string> table;
    ifstream inFile;
    inFile.open("words.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    string str = strStream.str();
    istringstream f(str);
    string line;
    //Insertamos palabra por palabra.
    int cont = 0;
    clock_t tstart,tstop;
    tstart = clock();
    while (getline(f, line)) {
        cont++;
        table.insertItem(line);
    }
    tstop = clock();

    table.printTable();
    cout << "Numero de elementos insertados: " << cont << endl;
    
    cout << table.getItemByKey("absorbing") << endl;
    cout << table.getItemByKey("humberto") << endl;
    printf("tiempo : %.4lf segundos\n", (tstop - tstart)/((double) CLOCKS_PER_SEC));
    //table.printHistogram();
    
    return 0;
}
