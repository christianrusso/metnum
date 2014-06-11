#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
from glob import glob
import os
from fnmatch import fnmatch
#Para bufferear el stdout:
from cStringIO import StringIO
import sys

# old_stdout = sys.stdout
# sys.stdout = mystdout = StringIO()

# # blah blah lots of code ...

# sys.stdout = old_stdout

# # examine mystdout.getvalue()
modo_de_uso=' \
 Recibe: file/path método rapido(0)/lento(1) \
 ejemplo: /visualizador/instancias/ 1 0 \
 Hace:  \
1) Compilar /src. Si falla el make, termina. \
2.1) Si es file: correr el /yoAtajo para el file con el método\
2.2) Si es path: correr el /yoAtajo para cada file en el path con el método\
3) Correr el visualizador lento o rápido para las instancias especificadas.\
   Incluir los jugadores <=> hay archivo con misma raíz de nombre pero con\
   extensión .jug'

def main(argv = sys.argv):
    if(len(arg) != 4):
        print modo_de_uso
        sys.exit(1)

    file_o_path = argv[1]
    metodo = int(argv[2])
    rapido_o_lento = int(argv[3])

    #Checkeo que sean parámetros válidos:
    if (not(os.path.isfile(argv[1])) or os.path.isdir(argv[1])):
        print "Archivo/path inválido."
        sys.exit(1)
    else:
        if(not(rapido_o_lento==1) and not(rapido_o_lento==0))
        print 'ERROR:\
    Rápido = 0 \
    Lento = 1 ', "OPCION DADA: "+ str(rapido_o_lento)
        sys.exit(1)

    #Si llegó hasta acá, está todo piola con los parámetros.
    #1)Compilar:
    print "Compilando /src ...."
    os.chdir("/src")
    old_stdout = sys.stdout #me guardo el stdout viejo
    sys.stdout = mystdout = StringIO() #hago que el stdout vaya a un buffer

    ret_make = subprocess.call("make")

    sys.stdout = old_stdout

if __name__ == "__main__":
    main()







# # Programa compilado
# executable = './yoAtajo' if os.name == 'posix' else 'yoAtajo.exe'

# def listfiles(root, pattern):
#   for path, subdirs, files in os.walk(root):
#     for name in files:
#       if fnmatch(name, pattern):
#         yield os.path.join(path, name)


# def runTp(input, output):
#     """Invoca al tp con input y output como parametros"""
#     #fileOut = open(input.replace(".in", ".console"), 'w')
#     print("usando metodo 4")
#     call([executable, input, output, '4'] , stdin=None, stdout=PIPE, stderr=PIPE)
#     #if (input.find("Met0") > 0):
#     #	print("usando metodo 0")
#     #	call([executable, input, output, '0'] , stdin=None, stdout=fileOut, stderr=fileOut)
#     #else:
#     #	print("usando metodo 0")
#     #	call([executable, input, output, '0'] , stdin=None, stdout=fileOut, stderr=fileOut)

# def run():
# 	for fname in listfiles('../testVisualizador/instancias', '*.tiro'):
# 		#if (fname.replace(".tiro", ".out.times") in listfiles('cases', '*.times')):
# 		#	print("Case " + fname + " was already run")
# 		#else:
# 		#	print("Running case: " + fname)
# 		runTp(fname,  fname.replace(".tiro", ".arq"))

# run();