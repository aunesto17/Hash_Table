//
//  linked_list.hpp
//  AED_Theory
//
//  Created by Alexander Arturo Baylon Ibanez on 21/09/15.
//  Copyright © 2015 Alexander Arturo Baylon Ibanez. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <map>
#include <random>
#include <bitset>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

//threads
#include <thread>
#include <mutex>
#include <atomic>


using namespace std;


// Funciones para determinar a<b / a>b
template<class T>
bool less(T a,T b) {
    return a < b;
}

template<class T>
bool greater(T a,T b) {
    return a > b;
}


/*
// Struct de Funciones
struct CListTraits
{
    typedef int T;
    typedef Class<T> C;
    typedef Class<C> D;
};*/

// Nodo
template<class F>
struct cNode
{
    F m_data;
    cNode<F> * m_next;
    cNode(F x)
    {
        m_data = x;
        m_next = nullptr;
    }
};


// Clase Lista Enlazada
template <class T>
class cList {
public:
    //cNode<T> * head = nullptr;
    char letras[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',};
    cNode<T> * m_head = nullptr;
    int lenght = 0;
    //C m_cmp;
    //cNode<T> * m_head;
    cList(){};
    bool insert(T);
    bool remove(T);
    bool find(T,cNode<T>**&);
    void printList();
    int getLength(){
        return lenght;
    }
    int get_size();
    ~cList(){};
};


//Implementacion de Metodos
template<class T>
bool cList<T>::insert(T x)
{
    cNode<T> ** p;
    if (find(x,p)) return 0;
    cNode<T> * t = new cNode<T>(x);
    t->m_next = *p;
    *p = t;
    lenght++;
    return 1;
}

template<class T>
bool cList<T>::remove(T x)
{
    cNode<T> ** p;
    if (!find(x,p)) return 0;
    cNode<T> * t = *p;
    *p = (*p)->m_next; // igualamos puntero simple a simple
    delete t;
    return 1;
}

template<class T>
bool cList<T>::find(T x, cNode<T>**&p)
{
    p = &m_head;
    //if(*p)
    while (*p && x>=(*p)->m_data) {
        if (*p && x==(*p)->m_data) return 1;
        p = &(*p)->m_next;
    }
    return 0;
}


template<class T>
void cList<T>::printList()
{
    cNode<T> * temp = m_head;
    int i = 0;
    cout << "-> ";
    while (temp!=nullptr) {
        cout << letras[i++] << "(" << temp->m_data << ")" << " -> ";
        temp = temp->m_next;
    }
    cout << "end" << endl;
}

template<class T>
int cList<T>::get_size()
{
    cNode<T> * temp = m_head;
    int i = 0;
    while (temp!=nullptr) {
        i++;
        temp = temp->m_next;
    }
    return i;
}






#endif /* linked_list_hpp */
