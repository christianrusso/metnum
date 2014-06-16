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
  if(len(argv) != 2):
    print modo_de_uso
    sys.exit(1)

  archivito = argv[1]

  #Checkeo que sean parámetros válidos:

  matriz = []
  #Si llegó hasta acá, está todo piola con los parámetros.
  for metodo in range(0,10): 
    print "Generando para método: "+str(metodo)
    path_archivito = 'met'+str(metodo)+'/'+archivito
    print "Archivo: " + path_archivito

    if (not(os.path.isfile(path_archivito))):
      print "No se encontró archivito para módulo"+str(metodo) 
      for i in range(1,len(lineas)):
        matriz[i].append(-1)
    else:
      lineas = linecache.getlines(archivito)
      for i in range(1,len(lineas)):
        matriz[i].append(abs(float(lineas[i])))
  nuevo_path = 'todos/'+archivito.replace('*.movsgol','*.TODOS')
  nuevo_path = nuevo_path.replace('*.movstodos', '*.TODOS')
  print "Nuevo path: " + nuevo_path
  f = open(nuevo_path,'w')
  for fila in matriz:
    stringsito = fila[0]		
    for i in range(1,len(size)):
      stringsito = stringsito + ',' +x
      f.write(stringsito+'\n')
  f.close() # k

if __name__ == "__main__":
    main()
