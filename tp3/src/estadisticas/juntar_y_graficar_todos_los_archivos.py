#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
from glob import glob
import os
from fnmatch import fnmatch
import sys
import linecache
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#BUSCA TODOS LOS ARCHIVOS DE met0 Y PARA CADA UNO LE HACE juntar_todo.py
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
def listfiles(root, pattern):
  for path, subdirs, files in os.walk(root):
    for name in files:
      if fnmatch(name, pattern):
        yield os.path.join(path, name)


def main(argv = sys.argv):
    archivos_movsgol = listfiles("met0/","*.movsgol")
    archivos_movstodos = listfiles("met0/","*.movstodos")
    archivos_movsestimacion = listfiles("met0/","*.movsestimacion")
    print "Calculando movsgol \n"
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
    print "Calculando movsestodos \n"
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
    print "Calculando movsestimacion \n"
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
