#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
from glob import glob
import os
from fnmatch import fnmatch
import sys

modo_de_uso=' ERROR: Cantidad de parámetros inválida \n \
 Recibe: file/path método rapido(0)/lento(1) \n \
 ejemplo: ./visualizador/instancias/ 1 0 \n \
 Hace:  \n \
1) Compilar /src. Si falla el make, termina. \n \
2.1) Si es file: correr el /yoAtajo para el file con el método \n \
2.2) Si es path: correr el /yoAtajo para cada file en el path con el método \n \
3) Correr el visualizador lento o rápido para las instancias especificadas. \n \
   Incluir los jugadores <=> hay archivo con misma raíz de nombre pero con \n \
   extensión .jug'

def listfiles(root, pattern):
  for path, subdirs, files in os.walk(root):
    for name in files:
      if fnmatch(name, pattern):
        yield os.path.join(path, name)

def main(argv = sys.argv):
    if(len(argv) != 4):
        print modo_de_uso
        sys.exit(1)

    file_o_path = argv[1]
    metodo = int(argv[2])
    rapido_o_lento = int(argv[3])

    #Checkeo que sean parámetros válidos:
    if (not(os.path.isfile(file_o_path)) and not(os.path.isdir(file_o_path))):
        print "Archivo/path inválido."
        sys.exit(1)
    else:
        if(not(rapido_o_lento==1) and not(rapido_o_lento==0)):
            print 'ERROR:\
    Rápido = 0 \
    Lento = 1 '
            print "OPCION DADA: "+ str(rapido_o_lento)
            sys.exit(1)

    #Si llegó hasta acá, está todo piola con los parámetros.
    #1)Compilar:
    print "\n*-*-*-* Compilando ./src .... *-*-*-* \n"
    os.chdir("./src")
    ret_make = subprocess.call("make")
    if(not(ret_make ==0)):
        sys.exit(1)
    #2) Generar .arq
    a_visualizar=[]
    
    if(os.path.isfile("../"+file_o_path)):
        print "\n*-*-*-* Generando .arq único .... *-*-*-* \n"
        atajar("../"+file_o_path, metodo)
        print "Se generó .arq para "+file_o_path
        a_visualizar.append(file_o_path)
    else:
        #tengo que correr para cada uno de los .tiro de un dir
        print "\n *-*-*-* Generando los .arq del directorio.... *-*-*-* \n"
        archivos = listfiles("../"+file_o_path, '*.tiro')
        if(not archivos):
            print "No se generaron .arq dado que no había .tiro"
            sys.exit(1)
        for fname in archivos:
            atajar(fname, metodo)
            print "Se generó .arq para "+fname.replace("../", "./")
            a_visualizar.append(fname.replace("../", "./"))

    #3) Correr visualizador lento o rápido.
    os.chdir("../visualizador")
    if(rapido_o_lento):
        #Visualización lenta
        visualizador = "main.py"
    else:
        #Visualización rápida
        visualizador = "mainFast.py"
    for tiro in a_visualizar:
        tiro_path = "../"+tiro
        arq_path = tiro_path.replace(".tiro", ".arq")
        jug_path = dameJugadores(tiro_path)
        print "Se va a correr visualización para "+ tiro_path
        subprocess.call(["python", visualizador, arq_path, tiro_path, jug_path])
    sys.exit(0)


# python main.py instancias/cubicas/cb1.arq instancias/cubicas/cb1.tiro instancias/vacio.jug



    

def atajar(arch_tiro, metodo):
    #Asume que si no existe un .jug con la misma raiz, entonces no hay jugadores.
    #asume que se lo corre en ./src
    arch_jug = dameJugadores(arch_tiro)
    arch_arq = arch_tiro.replace(".tiro", ".arq")
    ret_atajo= subprocess.call(["./yoAtajo", arch_tiro, arch_jug, arch_arq, str(metodo)])
    if(not(ret_atajo==0)):
        sys.exit(1)

def dameJugadores(arch_tiro):
    #Dado el path de un .tiro, devuelve si el .jug si hay alguno asociado, o el 
    #path al vacio si no lo hay.
    arch_jug = arch_tiro.replace(".tiro", ".jug")
    if (not(os.path.isfile(arch_jug))):
        print "*-*-*-* No hay archivo de jugadores, voy a pasar el file de jugadores vacio. *-*-*-*"
        arch_jug = "../visualizador/instancias/vacio.jug"
        assert os.path.isfile(arch_jug), "No existe el file de jugadores vacio."
    return arch_jug

if __name__ == "__main__":
    main()
