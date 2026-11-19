//*****************************************************************
// File:   AccederACola.hpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
//*****************************************************************
#ifndef ACCEDER_A_COLA
#define ACCEDER_A_COLA

#include <BoundedQueue.hpp>
#include <mutex>
#include <condition_variable>

using namespace std;

template <class T>
class AccederACola {
public:
    //-----------------------------------------------------
    //Pre:  0<N
    //Post: this->bq=< > AND #this=N
    //Com:  constructor
    AccederACola(const int N);
    
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~AccederACola();

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n >
    //Post: this->bq=< d_1 ... d_n d > 
    //Coms: se bloquea hasta que haya un hueco para insertar el dato
    //      y lo inserta
    void encolar(const T d);

    //-----------------------------------------------------
    //Pre:  this->bq=< d_1 ... d_n> and n>0
    //Post: this->bq=< d_2 ... d_n >
    //Coms: se bloquea hasta que this->bq=< d_1 ... d_n> and n>0
    //      y desencola el primer elemento
    void desencolar(T &d);


private:
	mutex mtxMonitor;
    condition_variable hay_elemento;
    condition_variable hay_hueco;
    BoundedQueue<T> bq;
    /*....*/
};
// Al trabajar con tipos genéricos, especificación e implementación
// deben estar presentes en el momento de la compilación.
// Por eso incluímos aquí la implementación
#include "AccederACola.cpp"
#endif
