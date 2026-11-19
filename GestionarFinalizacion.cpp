//*****************************************************************
// File:   GestionarFinalizacion.cpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026

//*****************************************************************

#include "GestionarFinalizacion.hpp"


//-----------------------------------------------------
GestionarFinalizacion::GestionarFinalizacion(const int numClientes) : numClientes(numClientes), numClientFin(0) {
}
//-----------------------------------------------------
GestionarFinalizacion::~GestionarFinalizacion() {
}
//-----------------------------------------------------
void GestionarFinalizacion::finalizarCliente() {
    unique_lock<mutex> lck(mtxMonitor);
    numClientFin++;
    if( numClientFin == numClientes){
        cvFin.notify_all();
    }
}
//-----------------------------------------------------
void GestionarFinalizacion::esperarATodos() {
    unique_lock<mutex> lck(mtxMonitor);
    while(numClientFin < numClientes){
        cvFin.wait(LCK);
    }
}
//-----------------------------------------------------
    
...
