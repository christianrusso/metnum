#!/usr/bin/env python
from subprocess import *
from glob import glob
import os
from fnmatch import fnmatch


# Programa compilado
executable = './yoAtajo' if os.name == 'posix' else 'yoAtajo.exe'

def listfiles(root, pattern):
  for path, subdirs, files in os.walk(root):
    for name in files:
      if fnmatch(name, pattern):
        yield os.path.join(path, name)


def runTp(input, output):
    """Invoca al tp con input y output como parametros"""
    fileOut = open(input.replace(".in", ".console"), 'w')
    if (input.find("Met0") > 0):
    	print("usando metodo 0")
    	call([executable, input, output, '0'] , stdin=None, stdout=fileOut, stderr=fileOut)
    else:
    	print("usando metodo 1")
    	call([executable, input, output, '1'] , stdin=None, stdout=fileOut, stderr=fileOut)

def run():
	for fname in listfiles('../visualizador/instancias', '*.tiro'):
		#if (fname.replace(".tiro", ".out.times") in listfiles('cases', '*.times')):
		#	print("Case " + fname + " was already run")
		#else:
		#	print("Running case: " + fname)
		runTp(fname,  fname.replace(".tiro", ".arq"))

run();