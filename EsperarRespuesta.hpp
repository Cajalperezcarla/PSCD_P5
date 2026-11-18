//*****************************************************************
// File:   EsperarRespuesta.hpp
// Author: Carla Genoveva Cajal Pérez - 875406
// Date:   noviembre 2026
//*****************************************************************

#ifndef ESPERAR_RESPUESTA
#define ESPERAR_RESPUESTA

#include <mutex>
#include <condition_variable>
/*....*/

using namespace std;
//-----------------------------------------------------

class EsperarRespuesta {
public:
    //-----------------------------------------------------
    //Pre:  
    //Post: 
    //Com:  constructor
    EsperarRespuesta();
    
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
    void escribirRespuesta(const int idCliente, Respuesta resp);
    
private:
	mutex mtxMonitor;
    condition_variable var_condition;
    /*....*/
};

#endif
