//*****************************************************************
// File:   AccederACola.cpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
//*****************************************************************

#include "AccederACola.hpp"
#include <cassert>

//-----------------------------------------------------
template <class T>
AccederACola<T>::AccederACola(const int N) : bq(N) {
}

//-----------------------------------------------------
template <class T>
void AccederACola<T>::~AccederACola() {

   //...
}
//-----------------------------------------------------
template <class T>
void AccederACola<T>::encolar(const T d) {
    unique_lock<mutex> lck(mtxMonitor);

    //<await bq.length() < bq.size()
    //  bq.enqueue(d)
    //>
    while(bq.length() < bq.size()){
        hay_hueco.wait(lck);
    }

    bq.enqueue(d);
    hay_elemento.notify_one();
    
}
//-----------------------------------------------------
template <class T>
void AccederACola<T>::desencolar(T &d) {
    unique_lock<mutex> lck(mtxMonitor);

    //<await bq.length() > 0
    //  d = bq.first();
    //   bq.dequeue();
    //>

    while(bq.length() > 0){
        hay_elemento.wait(lck);
    }

    d = bq.first();
    bq.dequeue();
    hay_hueco.notify_one();
}
