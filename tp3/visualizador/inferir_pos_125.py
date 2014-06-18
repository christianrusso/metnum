#!/usr/bin/env python
# -*- coding: utf-8 -*-
import linecache
import subprocess
import os
import sys

modo_de_uso=' ERROR: Cantidad de parámetros inválida \n \
 Recibe: inFile outFile\n \
 ejemplo: instancias/conjugadores/conj1.tiro todos_125/conj1.tiro  \n \
 Hace:  \n \
 Entonces lo que hago es: \n \
 ....Si el 125 está en el archivo, nada. \n \
 ....Si el 125 no está en el archivo, calcular la recta secante entre los 2 puntos que son mayores \n \
 y menores a 125 y calcular el valor de 125 en esa recta.Hacer como si fuera lineal en ese último \n \
 tramo. \n \
 ....Si el final no queda adentro del arco, devolver EERRRRRRRRRRROR! \n'
def main(argv = sys.argv):
    if(len(argv) != 3):
        print modo_de_uso
        sys.exit(1)
    archivito_entrada = argv[1]
    archivito_salida = argv[2]
    print "Viendo si ya estaba incluido el 125 ..."
    estaba = tieneAl125(archivito_entrada)
    if(estaba):
        print "Ya estaba el 125"
        sys.exit(0)
    print "No estaba el 125. Vamos a inferirlo."
    lineas = linecache.getlines(archivito_entrada)
    iniciales = lineas.pop(0)
    iniciales_splitteados = iniciales.split()
    pos_palo_1 = iniciales_splitteados[1]
    pos_palo_2 = iniciales_splitteados[2]
    pos_arq = iniciales_splitteados[0]

    nuevas_lineas = []
    primera_linea_spliteada = lineas[0].split()
    anterior_x = float(primera_linea_spliteada[0])
    anterior_y = float(primera_linea_spliteada[1])
    for una_linea in lineas:
        linea_splitteada = una_linea.split()
        nuevo_x = float(linea_splitteada[0])
        nuevo_y = float(linea_splitteada[1])
        if(nuevo_x<125<anterior_x):
            y_de_125 = calcular_y_de_125(anterior_x, anterior_y, nuevo_x, nuevo_y)
            nueva_linea = '125 ' + str(y_de_125)
            nuevas_lineas.append(nueva_linea+"\n")
        anterior_x = nuevo_x
        anterior_y = nuevo_y
        nuevas_lineas.append(una_linea)
    f = open(archivito_salida,'w')
    print "Escribiendo archivo de salida ..."
    f.write(iniciales)
    for x in nuevas_lineas:
        f.write(x)
    f.close()
    assert tieneAl125(archivito_salida), "ERROR: El archivo devuelto no tiene al 125"
    assert float(pos_palo_1)<=y_de_125<=float(pos_palo_2), "ERROR: El 125 final queda afuera del arco"
    return 0

def tieneAl125(archivito):
    lineas = linecache.getlines(archivito)
    iniciales = lineas.pop(0)
    for una_linea in lineas:
        palabras = una_linea.split()
        x = float(palabras[0])
        if(x==125):
            linecache.clearcache()
            return True
    linecache.clearcache()
    return False

def calcular_y_de_125(anterior_x, anterior_y, nuevo_x, nuevo_y):
    pendiente = (anterior_y-nuevo_y)/(anterior_x-nuevo_x)
    independiente = (anterior_x*nuevo_y-nuevo_x*anterior_y)/(anterior_x-nuevo_x)
    return pendiente*125+independiente

if __name__ == "__main__":
    main()
