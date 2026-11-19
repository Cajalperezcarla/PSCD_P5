//*****************************************************************
// File:   EsperarRespuesta.hpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
//*****************************************************************

#ifndef ESPERAR_RESPUESTA
#define ESPERAR_RESPUESTA

#include <mutex>
#include <condition_variable>

// Estructura de Respuesta (si no está definida en un header común) 
#ifndef STRUCT_RESPUESTA 
#define STRUCT_RESPUESTA 
struct Respuesta { 
    bool estado; 
    double precio; 
}; 
#endif

using namespace std;
//-----------------------------------------------------

class EsperarRespuesta {
public:
    //-----------------------------------------------------
    //Pre:  
    //Post: 
    //Com:  constructor
    EsperarRespuesta(const int numClientes);
    
    //-----------------------------------------------------
    //Pre:
    //Post:
    //Com:  destructor
    ~EsperarRespuesta();

    //-----------------------------------------------------
    //Pre: ? 
    //Post: ? 
    //Coms: se bloquea hasta que el cliente pueda leer una respuesta
    void leerRespuesta(const int idCliente, Respuesta &resp);
    
    //-----------------------------------------------------
    //Pre: ? 
    //Post: ? 
    //Coms: escribe una respuesta dirigida a un cliente
    void escribirRespuesta(const int idCliente, Respuesta &resp);
    
private:
	const int numClientes; 
    mutex mtxMonitor; 
    bool* hayRespuesta; 
    Respuesta* tipoRespuesta; 
    condition_variable* cvRespuesta; // Una variable de condición por cliente
};

#endif
