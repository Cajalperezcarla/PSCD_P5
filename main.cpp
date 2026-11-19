//*****************************************************************
// File:   practica_5.cpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
// Coms:   Compilar mediante el "Makefile" asociado
//*****************************************************************

#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <cstdlib>

#include "AccederACola.hpp"
#include "EsperarRespuesta.hpp"
#include "GestionarFinalizacion.hpp"
#include "ImageWindow.hpp"

using namespace std;

//----------------------------------------------------
const int NUM_Cl = 10; 
const int NUM_Pub = 3; 
const int MAX_IMG = 10; 
const int MAX_INTENTOS = 2; 
const int TAM_COLA_VG = 10; 
const int TAM_COLA_VP = 15; 
const int PRECIO_BASE = 100;


enum tpPeticion { 
    Publicar, 
    Finalizar 
}; struct 

Peticion { 
    int idC; 
    tpPeticion tpPet; 
    string imagen; 
    int tServ; 
};

string escogerImagen() { 
    int nImagen = 1 + rand() % 20; 
    string pref = "nature_"; 
    if (nImagen &lt; 10) { 
        return pref + "0" + to\_string(nImagen) + ".jpg"; 
    } else { 
        return pref + to\_string(nImagen) + ".jpg"; 
    } 
}

void mostrarImagen(ImageWindow &win, const string &rutaImagen, int tServ) { 
    win.show(rutaImagen); 
    this_thread::sleep_for(chrono::milliseconds(tServ)); 
}

//----------------------------------------------------
void Cliente(const int id, 
    AccederACola<Peticion>& mVG, AccederACola<Peticion>& mVP, 
    EsperarRespuesta &mrespuestas, GestionarFinalizacion &mFinalizacion){
    
    Peticion pet;
    Respuesta resp;
    int numPetAceptadas = 0;
    int numPetRechazadas = 0;
    double precioTotal = 0.0;

    for(int i = 0; i < MAX_IMG; i++){
        int numIntentos = 0;
        //configuramos las peticiones
        resp.estado = false;
        pet.idC = id;
        pet.tpPet = Publicar;
        pet.imagen = "./images/" + escogerImagen();
        pet.tServ = rand();

        int numCola = rand() % 2;

        while(not resp.estado and numIntentos < MAX_INTENTOS){
            if( numCola == 1 ){ //cola grande
                mVG.encolar(pet);
            }else{
                mVP.encolar(pet);
            }

            mrespuestas.leerRespuesta(id, resp);

            if(resp.estado){
                numPetAceptadas++;
                precioTotal += resp.precio;
            }else{
                numIntentos++;
                if(numIntentos == MAX_INTENTOS){
                    numPetRechazadas++;
                }
            } 
        }
        cout << "Peticiones aceptadas: " << numPetAceptadas << endl;
        cout << "Peticiones rechazadas: " << numPetRechazadas << endl; 
        cout << "Precio total: " << precioTotal << endl; 

    }

    mFinalizacion.finalizarCliente();

    
}
//----------------------------------------------------
void Publicador(const int id, AccederACola<Peticion>& colaPeticiones, EsperarRespuestas &mRespuestas){
    int probabilidad = rand() % 100;
    bool fin = false;
    double precio = 0.0;

    Peticion pet;
    Respuesta resp;
    pet.tpPet=Publicar;
    int numPetAtendidas = 0;
    int numPetAceptadas = 0;

    while(pet.tpPet != Finalizar){

        colaPeticiones.desencolar();

        if(pet.tpPet == Publicar){
            if (probabilidad < 5){
                fin = false;
            } else {
                fin = true;
                numPetAceptadas++;
            }

            resp.estado = fin;

            if(fin){
                precio = PRECIO_BASE * (1.0/(c.length()+1));
                resp.precio = precio;
            } else {
                resp.precio= 0.0;
            }

            int indice = pet.idC;

            mRespuestas.escribirRespuesta(id, resp);
        }
        cout << "Peticiones atendidas: " << numPetAtendidas << endl;
        cout << "Peticiones aceptadas: " << numPetAceptadas << endl;
        cout << "Peticiones rechazadas: " << numPetAtendidas - numPetAceptadas << endl;
    }

}

//----------------------------------------------------
void Finalizador(AccederACola<Peticion>& mVG, AccederACola<Peticion>& mVP, GestionarFinalizacion &mFinalizacion){
    Peticion pet;
    pet.tpPet = Finalizar;

    mFinalizacion.esperarATodos();

    mVG.encolar(pet);
    mVP.encolar(pet);
    mVP.encolar(pet);
}
//----------------------------------------------------
int main(int argc, char *argv[]) {
    AccederACola<Peticion> monColaGrande(TAM_COLA_VG);
    AccederACola<Peticion> monColaPequena(TAM_COLA_VP);
    EsperarRespuesta monEspera;
    GestionarFinalizacion monFin;

    srand(time(NULL));  
    thread clientes [NUM_Cl];
    for(int i = 0; i < NUM_Cl; i++){
        clientes[i] = thread(&Cliente, i, ref(colaVG), ref(colaVP), ref(numClientFin));
    }

    thread publicador [NUM_Pub];
    publicador[0] = thread(&Publicador, 0, ref(colaVG), true);
    publicador[1] = thread(&Publicador, 1, ref(colaVP), false);
    publicador[2] = thread(&Publicador, 2, ref(colaVP), false);

    thread finalizador = thread(&Finalizador, ref(colaVG), ref(colaVP), ref(numClientFin));

    for(int i = 0; i < NUM_Cl; i++){
        clientes[i].join();
    }

    for(int i = 0; i < NUM_Pub; i++){
        publicador[i].join();
    }

    finalizador.join();

    //----------------------------------------------------|
    return 0;
}
