# Practica 5 - Programación mediante Monitores en C++
## Programación de sistemas concurrentes y distribuidos
Consulta el [enunciado de la practica](practica_5.pdf)

Este proyecto traslada el **sistema concurrente de gestión de publicidad** en C++ a un esquema basado en **Monitores** utilizando las herramientas de la librería estándar (`std::mutex` y `std::condition_variable`). El sistema simula la interacción entre múltiples procesos clientes que solicitan publicar imágenes y varios procesos publicadores que atienden las solicitudes a través de colas acotadas, garantizando la exclusión mutua y la sincronización condicional sin variables de paso de testigo manuales.

### Arquitectura del sistema
El sistema mantiene la misma división de procesos (hilos) concurrentes que la versión previa:
- **Clientes (`NUM_Cl = 10`):** Generan peticiones de publicación de imágenes de forma aleatoria, solicitan su inserción en las colas de publicidad y esperan la respuesta del publicador asignado a través del monitor de respuestas.
- **Publicadores (`NUM_Pub = 3`):** Atienden las peticiones de las colas (1 para la Valla Grande y 2 para las Vallas Pequeñas), evalúan si aceptan la publicidad, calculan el precio según la ocupación y muestran la imagen en la interfaz gráfica (`ImageWindow`).
- **Finalizador (1):** Sincroniza el cierre del sistema esperando a que los 10 clientes terminen su ciclo de peticiones antes de enviar las señales de parada (`Finalizar`) a los publicadores.

###Estructura de Monitores
La sincronización condicional y la exclusión mutua se han encapsulado en tres clases de monitores independientes:

1. **`AccederACola<T>` (Monitor Génerico de cola acotada):**
    - Encapsula la estructura de datos acotada `BoundedQueue<T>`
    - Utiliza las variables de condición `hay_elemento` y `hay_hueco` para bloquear a los publicadores cuando la cola está vacía (`desencolar`) y a los clientes cuando la cola está llena (`encolar`).

2. **`EsperaRespuesta` (Monitor de Intercambio de Respuestas):**
    - Administra la entrega directa punto a punto de las respuestas de los publicadores hacia los clientes.
    - Dispone de un array privado de variables de condición (`cvRespuesta[NUM_Cl]`) para bloquear y despertar de forma individualizada a cada cliente `idC` sin generar despertares innecesarios.

3. **`GestionarFinalizacion` (Monitor Barrera/Contador):**
    - Controla el número de clientes que han completado la totalidad de sus peticiones (`numClientFin`).
    - Bloquea al proceso `Finalizador` en la variable de condición `cvFin` hasta que los 10 clientes han notificado su finalización.

### Compilación y Ejecución
El proyecto incluye un `Makefile` configurado para compilar todos los módulos C++ con el estándar `gnu++11` y soporte de hilos POSIX (`-pthread`):

```bash 
# Limpiar ejecutables y archivos objeto previos 
make 
 
# Compilar el proyecto completo
make 

# Ejecutar la simulación 
./main
