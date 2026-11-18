#*****************************************************************
# File:   Makefile
# Author: Carla Genoveva Cajal Pérez - 875406
# Date:   noviembre 2026
# Coms:   Añadir todo lo que sea necesario
#*****************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # para compilar
#---------------------------------------------------------
#opciones de compilacion y enlazado ("linkado")
CPPFLAGS = -I. -I${MON_LIB} -O2 -std=c++11 -fmax-errors=1 #opciones de compilacion
LDFLAGS = -pthread #opciones de "linkado"
#---------------------------------------------------------
#vars
EJEC = main #practica5
#---------------------------------------------------------
#directorios y clases para monitores
MON_LIB=.
MONITOR=${MON_LIB}/main #practica5

#---------------------------------------------------------
all: ${EJEC}
#---------------------------------------------------------
# "linkar"
${EJEC}: ${EJEC}.o ${MONITOR}.o
	${CC} ${EJEC}.o ${MONITOR}.o -o ${EJEC} ${CPPFLAGS} ${LDFLAGS}

#---------------------------------------------------------
# compilar
${EJEC}.o: ${EJEC}.cpp #PONER DE QUE DEPENDE
	${CC} -c ${EJEC}.cpp ${CPPFLAGS}

$





# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ...
