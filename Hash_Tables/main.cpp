//
//  main.cpp
//  Hash_Tables
//
//  Created by Alexander Arturo Baylon Ibanez on 9/11/15.
//  Copyright © 2015 aunesto17. All rights reserved.
//

#include "HashTable.h"

static mutex barrier;

void insert_hash(HashTable<string> & hash, const vector<string> & palabras, int L,int R)
{
    //no necesitamos mutex ya que cada palabra generara un hash_key distinto
    for (int i=L; i<R; i++) {
        //lock_guard<mutex> bloqueo(barrier);
        hash.insertItem(palabras[i]);
    }
}


int main(int argc, const char * argv[]) {
    
    //Guardamos todas las palabras en un vector<string>.
    HashTable<string> table;
    ifstream inFile;
    inFile.open("words.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    string str = strStream.str();
    istringstream f(str);
    string line;
    vector<string> palabras;
    while (getline(f,line)) {
        palabras.push_back(line);
    }
    
    cout << "numero de palabras: " << palabras.size();
    
    //declaramos los threads
    vector<thread> threads;
    vector<int> limits;
    int num_threads = 2;
    
    //desde 0 hasta la mitad y desde la mitad hasta el final
    limits.push_back(0);
    limits.push_back(int(palabras.size()/2));
    limits.push_back(int(palabras.size()));
    
    clock_t tstart,tstop;
    tstart = clock();

    for (int i=0; i<num_threads; i++) {
        threads.push_back(thread(insert_hash,ref(table),ref(palabras),limits[i],limits[i+1]));
    }
    
    for (auto &t : threads){
        t.join();
    }
    
    tstop = clock();
    
    
    //Insertamos palabra por palabra.
    //int cont = 0;
    //clock_t tstart,tstop;
    //tstart = clock();
    //while (getline(f, line)) {
    //    cont++;
    //    table.insertItem(line);
    //}
    //tstop = clock();

    table.printTable();
    //cout << "Numero de elementos insertados: " << cont << endl;
    
    //cout << table.getItemByKey("absorbing") << endl;
    //cout << table.getItemByKey("humberto") << endl;
    //printf("tiempo : %.4lf segundos\n", (tstop - tstart)/((double) CLOCKS_PER_SEC));
    //table.printHistogram();
    
    
    
    printf("tiempo : %.4lf segundos\n", (tstop - tstart)/((double) CLOCKS_PER_SEC));
    
    return 0;
}
