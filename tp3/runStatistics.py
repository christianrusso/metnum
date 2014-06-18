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
   Corre todos los .tiro (y respectivos .arq si existen) existentes en el dir \n \
   (o del file si es un file) para todos los métodos desde 0 hasta 9.\n \
   Automáticamente se crean los respectivos .movsgol y .movs todos en \n \
   la carpeta /src/estadisticas/meti para los i desde 0 hasta 9.'

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
    os.chdir("./src")
    ret_make = subprocess.call("make")
    if(not(ret_make ==0)):
        sys.exit(1)
    #2) Generar .arq
    for metodo in range(22,40):
        if(os.path.isfile("../"+file_o_path)):
            print "\n*-*-*-* Corriendo estadísticas para el file .... *-*-*-* \n"
            atajar_sin_guardar("../"+file_o_path, metodo)
            print "Se generaron las estadísticas para "+file_o_path + "con método" + metodo
        else:
            #tengo que correr para cada uno de los .tiro de un dir
            print "\n *-*-*-* Corriendo estadísticas para los archivos del directorio *-*-*-* \n"
            archivos = listfiles("../"+file_o_path, '*.tiro')
            if(not archivos):
                print "No se corrieron las estadísticas dado que no había .tiro"
                sys.exit(1)
            for fname in archivos:
                atajar_sin_guardar(fname, metodo)
                print "Se generaron las estadísticas para "+fname.replace("../", "./")+ 'con método' + str(metodo)
    sys.exit(0)
############################################################################################33
def atajar_sin_guardar(arch_tiro, metodo):
    #Asume que si no existe un .jug con la misma raiz, entonces no hay jugadores.
    #asume que se lo corre en ./src
    arch_jug = dameJugadores(arch_tiro)
    arch_arq = arch_tiro.replace(".tiro", ".arq")
    ret_atajo= subprocess.call(["./yoAtajo", arch_tiro, arch_jug, '/dev/null', str(metodo)])
    if(not(ret_atajo==0)):
        sys.exit(1)

############################################################################################33
def dameJugadores(arch_tiro):
    #Dado el path de un .tiro, devuelve si el .jug si hay alguno asociado, o el
    #path al vacio si no lo hay.
    arch_jug = arch_tiro.replace(".tiro", ".jug")
    if (not(os.path.isfile(arch_jug))):
        print "*-*-*-* No hay archivo de jugadores, voy a pasar el file de jugadores vacio. *-*-*-*"
        arch_jug = "../visualizador/instancias/vacio.jug"
        assert os.path.isfile(arch_jug), "No existe el file de jugadores vacio."
    return arch_jug

############################################################################################33
if __name__ == "__main__":
    main()

