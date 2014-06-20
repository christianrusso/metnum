#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
from glob import glob
import os
from fnmatch import fnmatch
import sys
import linecache

modo_de_uso=' ERROR: Cantidad de parámetros inválida \n \
 Recibe: file \n \
 ejemplo: r1_125.movsgol \n \
 Hace:  \n \
Une todas las estadísticas en un mismo archivo: file.TODOS'

def main(argv = sys.argv):
  if(len(argv) != 1):
    print "Este script no recibe parametros"
    sys.exit(1)

  #Checkeo que sean parámetros válidos:

  matriz = []
  #Si llegó hasta acá, está todo piola con los parámetros.
  for metodo in range(0,40):
    # print "Generando para método: "+str(metodo)
    path = 'met'+str(metodo)+'/'
    # print "Archivo: " + path_archivito
    archivos_movsgol = listfiles(path,"*.movsgol")
    archivos_movstodos = listfiles(path,"*.movstodos")
    archivos_movsestimacion = listfiles(path,"*.movsestimacion")
    print "Calculando tabla movsgol \n"
    for x in archivos_movsgol:
        print x
        arch = x.split("/")[1]
        ret_juntar_todo =subprocess.call(["python","juntar_todo.py",arch])
        if(ret_juntar_todo!=0):
            print "Falló el juntar_todo.py para el archivo: " + arch
            sys.exit(1)
        ret_graficos=subprocess.call(["bash","crear_graficos_para_movsgol.sh",arch+".TODOS"])
        if(ret_graficos!=0):
            print "Falló el graficar para el archivo: " + arch
            sys.exit(1)
    print "Calculando tabla movsestodos \n"
    for x in archivos_movstodos:
        print x
        arch = x.split("/")[1]
        ret_juntar_todo=subprocess.call(["python","juntar_todo.py",arch])
        if(ret_juntar_todo!=0):
            print "Falló el juntar_todo.py para el archivo: " + arch
            sys.exit(1)
        ret_graficos=subprocess.call(["bash","crear_graficos_para_movstodos.sh",arch+".TODOS"])
        if(ret_graficos!=0):
            print "Falló el graficar para el archivo: " + arch
            sys.exit(1)
    print "Calculando tabla movsestimacion \n"
    for x in archivos_movsestimacion:
        print x 
        arch = x.split("/")[1]
        ret_juntar_todo=subprocess.call(["python","juntar_todo.py",arch])
        if(ret_juntar_todo!=0):
            print "Falló el juntar_todo.py para el archivo: " + arch
            sys.exit(1)
        ret_graficos=subprocess.call(["bash","crear_graficos_para_movsestimacion.sh",arch+".TODOS"])
        if(ret_graficos!=0):
            print "Falló el graficar para el archivo: " + arch
            sys.exit(1)
    return 0

if __name__ == "__main__":
    main()
