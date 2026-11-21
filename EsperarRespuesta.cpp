//*****************************************************************
// File:   EsperarRespuesta.cpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
//*****************************************************************

#include "EsperarRespuesta.hpp"
...
//-----------------------------------------------------
EsperarRespuesta::EsperarRespuesta(const int numClientes) : numClientes(numClientes) {
    hayRespuesta = new bool[numClientes];
    tipoRespuesta = new Respuesta[numClientes];
    cvRespuesta = new condition_variable[numClientes];

    for (int i = 0; i < numClientes; i++){
        hayRespuesta[i] = false;
    }
}
//-----------------------------------------------------
EsperarRespuesta::~EsperarRespuesta() {
    delete[] hayRespuesta; 
    delete[] tipoRespuesta; 
    delete[] cvRespuesta;
}
//-----------------------------------------------------
void EsperarRespuesta::leerRespuesta(const int idCliente, Respuesta &resp) {
    unique_lock<mutex> lck(mtxMonitor);

    //<await hayRespuesta[idCliente]
    //  resp = tipoRespuesta[idC];
    //  hayRespuesta[idC] = false;
    //>
    while(!hayRespuesta[idCliente]){
        cvRespuesta[idCliente].wait(lck);
    }

    resp = tipoRespuesta[idCliente];
    hayRespuesta[idCliente] = false; // reseteo para la siguinete peticion
}
//-----------------------------------------------------
void EsperarRespuesta::escribirRespuesta(const int idCliente, Respuesta resp) {
    unique_lock<mutex> lck(mtxMonitor);

    //Guardar respuesta y marcar el flag
    tipoRespuesta[idCliente] = resp;
    hayRespuesta[idCliente] = true;

    //despertar al cliente con idCliente
    cvRespuesta[idCliente].notify_one();
}
//-----------------------------------------------------
    
...
