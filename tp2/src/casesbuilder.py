#!/usr/bin/env python
import math
import random

directory = 'cases/'


# Junto con el presente enunciado, se adjunta una serie de scripts hechos en python y un conjunto
# instancias de test que deberan ser utilizados para la compilacion y un testeo basico de la
# implementacion. Se recomienda leer el archivo README.txt con el detalle sobre su utilizacion.


def caseVariandoPersonasFull(k, cantPersonas, metodo):
#Especificamos el metodo para facilitar luego el nombre del .out
	for samples in range(1,11):
		personas = []
		filename = 'caseSamples'+ str(samples) + 'Personas'+ str(cantPersonas) + 'Met' + str(metodo) + 'Full.in'
		f = open(directory+filename,'w')
		
		#fijamos la cantidad de iteraciones en 100 pues esto lo variamos dentro del codigo, por cuestiones de tiempo de computo, ya que con las 100 podemos realizar hacer los 100 casos.
		f.write("../data/ImagenesCaras/ 112 92 " + str(cantPersonas) + ' ' + str(samples) + ' ' + str(k) + '' +'\n')
		for x in range(1,cantPersonas+1):
			personas.append(random.sample(range(1, 11),10))
		for x in range(1,cantPersonas+1):
			f.write("s" + str(x) + "/")
			for y in range(1,samples+1):
				f.write(" " + str(personas[x-1][y-1]))
			f.write('\n')
		f.write(str(cantPersonas)+'\n')
		for x in range(1,cantPersonas+1):
			if (samples == 10):
				samples = 9
			f.write("../data/ImagenesCaras/s" + str(x) + '/' + str(personas[x-1][samples]) + '.pgm ' + str(x) +'\n')
		f.close()

def caseVariandoPersonasRed(k, cantPersonas, metodo):
#Especificamos el metodo para facilitar luego el nombre del .out
	for samples in range(1,11):
		personas = []
		filename = 'caseSamples'+ str(samples) + 'Personas'+ str(cantPersonas) + 'Met' + str(metodo) + 'Red.in'
		f = open(directory+filename,'w')
		
		#fijamos la cantidad de iteraciones en 100 pues esto lo variamos dentro del codigo, por cuestiones de tiempo de computo, ya que con las 100 podemos realizar hacer los 100 casos.
		f.write("../data/ImagenesCarasRed/ 28 23 " + str(cantPersonas) + ' ' + str(samples) + ' ' + str(k) + '' +'\n')
		for x in range(1,cantPersonas+1):
			personas.append(random.sample(range(1, 11),10))
		for x in range(1,cantPersonas+1):
			f.write("s" + str(x) + "/")
			for y in range(1,samples+1):
				f.write(" " + str(personas[x-1][y-1]))
			f.write('\n')
		f.write(str(cantPersonas)+'\n')
		for x in range(1,cantPersonas+1):
			if (samples == 10):
				samples = 9
			f.write("../data/ImagenesCarasRed/s" + str(x) + '/' + str(personas[x-1][samples]) + '.pgm ' + str(x) +'\n')
		f.close()


#def caseVariandoPersonasFull(k, cantPersonas, metodo):
caseVariandoPersonasFull(100, 1, 0);
caseVariandoPersonasFull(100, 11, 0);
caseVariandoPersonasFull(100, 21, 0);
caseVariandoPersonasFull(100, 31, 0);
caseVariandoPersonasFull(100, 41, 0);
caseVariandoPersonasFull(100, 1, 1);
caseVariandoPersonasFull(100, 11, 1);
caseVariandoPersonasFull(100, 21, 1);
caseVariandoPersonasFull(100, 31, 1);
caseVariandoPersonasFull(100, 41, 1);
caseVariandoPersonasRed(100, 1, 0);
caseVariandoPersonasRed(100, 11, 0);
caseVariandoPersonasRed(100, 21, 0);
caseVariandoPersonasRed(100, 31, 0);
caseVariandoPersonasRed(100, 41, 0);
caseVariandoPersonasRed(100, 1, 1);
caseVariandoPersonasRed(100, 11, 1);
caseVariandoPersonasRed(100, 21, 1);
caseVariandoPersonasRed(100, 31, 1);
caseVariandoPersonasRed(100, 41, 1);
