#*****************************************************************
# File:   Makefile
# Author: Carla Genoveva Cajal Pérez - 875406
# Date:   noviembre 2026
# Coms:   Makefile para compilar la Práctica 5 (Monitores C++)
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # para compilar
#---------------------------------------------------------
# opciones de compilacion y enlazado ("linkado")
CPPFLAGS = -I. -O2 -std=gnu++11 -fmax-errors=1 #opciones de compilacion
LDFLAGS = -pthread #opciones de "linkado"
#---------------------------------------------------------
# Nombre del ejecutable y archivos objeto (.o)
EJEC = main #practica5
ER = EsperarRespuesta
GF = GestionarFinalizacion
IW = ImageWindow
AC = AccederACola
BQ = BoundedQueue
#---------------------------------------------------------
all: $(EJEC)
#---------------------------------------------------------
# Regla de enlazado ("linkado")
$(EJEC): $(EJEC).o $(ER).o $(GF).o $(IW).o
	$(CC) $(EJEC).o $(ER).o $(GF).o $(IW).o -o $(EJEC) $(CPPFLAGS) $(LDFLAGS)

#---------------------------------------------------------
# REGLAS DE COMPILACION DE CADA MODULO
$(EJEC).o: $(EJEC).cpp $(AC).hpp $(AC).cpp $(BQ).hpp $(BQ).cpp $(ER).hpp $(GF).hpp $(IW).hpp
		   $(CC) -c  $(EJEC).cpp $(CPPFLAGS)

$(ER).o: $(ER).cpp $(ER).hpp
		 $(CC) -c $(ER).cpp $(CPPFLAGS)

$(GF).o: $(GF).cpp $(GF).hpp
		 $(CC) -c $(GF).cpp $(CPPFLAGS)

$(IW).o: $(IW).cpp $(IW).hpp
		 $(CC) -c $(IW).cpp $(CPPFLAGS)

# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) *.o $(EJEC)
