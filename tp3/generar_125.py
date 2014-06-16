#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
from glob import glob
import os
from fnmatch import fnmatch
import sys

modo_de_uso=' ERROR: Cantidad de parámetros inválida \n \
 Recibe: file/path \n \
 ejemplo: ./visualizador/instancias/  \n \
 Hace:  \n \
    Cambia todos los .tiro de la carpeta indicada (o file indicado) por un _125.tiro \n  \
    tal que lee todos los puntos del archivo, los agrega a un spline, calcula el spline \n \
    para el x=125 y devuelve un archivo con los primeros puntos hasta el 125, agrega \n \
    el spline para el x=125 y ningún otro punto más. Para esto usa a splineTest.cpp. \n \
    Se guardan todos _125 en la carpeta todos_125\n.'

############################################################################################33
def listfiles(root, pattern):
  for path, subdirs, files in os.walk(root):
    for name in files:
      if fnmatch(name, pattern):
        yield os.path.join(path, name)

############################################################################################33
def main(argv = sys.argv):
    if(len(argv) != 2):
        print modo_de_uso
        sys.exit(1)

    file_o_path = argv[1]

    #Checkeo que sean parámetros válidos:
    if (not(os.path.isfile(file_o_path)) and not(os.path.isdir(file_o_path))):
        print "Archivo/path inválido."
        sys.exit(1)

    #Si llegó hasta acá, está todo piola con los parámetros.
    #1)Compilar:
    print "\n*-*-*-* Compilando ./src .... *-*-*-* \n"
    os.chdir("./visualizador")
    ret_make = subprocess.call("make")
    if(ret_make!=0):
        exit(1)
    if(os.path.isfile("../"+file_o_path)):
        print "\n*-*-*-* Generando _125 para un sólo file  .... *-*-*-* \n"
        generar_125("../"+file_o_path, metodo)
        print "Se generaró el _125 para "+file_o_path
    else:
        #tengo que correr para cada uno de los .tiro de un dir
        print "\n *-*-*-* Generando los _125 del directorio.... *-*-*-* \n"
        archivos = listfiles("../"+file_o_path, '*.tiro')
        if(not archivos):
            print "No se generaron _125 dado que no había .tiro"
            sys.exit(1)
        for fname in archivos:
            print "Se va a generar _125 para "+fname.replace("../", "./")
            generar_125(fname)
            print "Generación exitosa"
    sys.exit(0)
###################################################################
def generar_125(arch_tiro):
    #Asume que si no existe un .jug con la misma raiz, entonces no hay jugadores.
    #asume que se lo corre en ./src
    arch_salida = "../visualizador/todos_125/"+arch_tiro.replace(".tiro", "_125.tiro")
    ret_spline= subprocess.call(["./splineTest", arch_tiro, arch_salida, "/dev/null"])
    if(not(ret_spline==0)):
        print "Error con splineTest"
        sys.exit(1)


############################################################################################33
if __name__ == "__main__":
    main()

