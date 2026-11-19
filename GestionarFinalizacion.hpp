//*****************************************************************
// File:   GestionarFinalizacion.hpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
//*****************************************************************

#ifndef GESTIONAR_FINALIZACION
#define GESTIONAR_FINALIZACION

#include <mutex>
#include <condition_variable>
/*...*/

using namespace std;
//-----------------------------------------------------

class GestionarFinalizacion {
public:
    //-----------------------------------------------------
    //Pre:  numClientes > 0
    //Post: 
    //Com:  constructor
    GestionarFinalizacion(const int numClientes);
    
    //-----------------------------------------------------
    //Pre: true
    //Post:
    //Com:  destructor
    ~GestionarFinalizacion();

    //-----------------------------------------------------
    //Pre: ? 
    //Post: ? 
    //Coms: incrementa el contador de clientes finalizados
    void finalizarCliente();
    
    //-----------------------------------------------------
    //Pre: ? 
    //Post: ? 
    //Coms: espera a que todos los clientes acaben
    void esperarATodos();
    
private:
	const int numClientes; 
    int numClientFin; 
    mutex mtxMonitor; 
    condition_variable cvFin;
};

#endif
