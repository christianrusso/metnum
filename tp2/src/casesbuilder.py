#!/usr/bin/env python
import math
import random

directoryVariandoPersonas = 'cases/ImagenesCaras/variandoPersonas/'
directoryVariandoPersonasEIters = 'cases/ImagenesCaras/variandoPersonasEIters/'
directoryVariandoPersonasEItersECantImgs = 'cases/ImagenesCaras/variandoPersonasEItersECantImgs/'
directoryVariandoPersonasEItersECantImgsRandom = 'cases/ImagenesCaras/variandoPersonasEItersECantImgsRandom/'


directoryVariandoPersonasRed = 'cases/ImagenesCarasRed/variandoPersonas/'
directoryVariandoPersonasEItersRed = 'cases/ImagenesCarasRed/variandoPersonasEIters/'
directoryVariandoPersonasEItersECantImgsRed = 'cases/ImagenesCarasRed/variandoPersonasEItersECantImgs/'
directoryVariandoPersonasEItersECantImgsRandomRed = 'cases/ImagenesCarasRed/variandoPersonasEItersECantImgsRandom/'

# Considerar al menos dos instancias de prueba, generando distintas discretizaciones para cada
#una de ellas y comparando la ubicacion de la isoterma buscada respecto de la pared externa del
#horno. Se sugiere presentar graficos de temperatura o curvas de nivel para los mismos, ya sea
#utilizando las herramientas provistas por la catedra o implementando sus propias herramientas de
#graficacion. Estudiar la proximidad de la isoterma buscada respecto de la pared exterior del horno
#en funcion de distintas granularidades de discretizacion y las condiciones de borde. Analizar
#tambien el tiempo de computo requerido en funcion de la granularidad de la discretizacion.


def caseVariandoPersonas():
	
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y 15 iteraciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonas+filename,'w')
		cantPersonas = random.randint(1, 41)
		f.write("../data/ImagenesCaras/ 112 92 " + str(cantPersonas) + ' 5 15' +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		for x in personas:
			f.write("s" + str(x) + "/ 1 2 3 4 5" +'\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCaras/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 

def caseVariandoPersonasEIters(maxIteraciones):
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y vario la cantidad de itereaciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasEIters+filename,'w')
		cantPersonas = random.randint(1, 41)
		iters = random.randint(1,maxIteraciones)
		f.write("../data/ImagenesCaras/ 112 92 " + str(cantPersonas) + ' 5 '+ str(iters) +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		for x in personas:
			f.write("s" + str(x) + "/ 1 2 3 4 5" +'\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCaras/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 

def caseVariandoPersonasEItersECantImgs(maxIteraciones):
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y vario la cantidad de itereaciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasEItersECantImgs+filename,'w')
		cantPersonas = random.randint(1, 41)
		iters = random.randint(1,maxIteraciones)
		f.write("../data/ImagenesCaras/ 112 92 " + str(cantPersonas) + ' 5 '+ str(iters) +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		cantImg = random.randint(1,9)	
		for x in personas:
			f.write("s" + str(x) + "/")
			for y in range(1,cantImg):
				f.write(" " + str(y))
			f.write('\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCaras/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 


def caseVariandoPersonasEItersECantImgsRandom(maxIteraciones):
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y vario la cantidad de itereaciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasEItersECantImgsRandom+filename,'w')
		cantPersonas = random.randint(1, 41)
		iters = random.randint(1,maxIteraciones)
		f.write("../data/ImagenesCaras/ 112 92 " + str(cantPersonas) + ' 5 '+ str(iters) +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		cantImg = random.randint(1,9)	
		for x in personas:
			f.write("s" + str(x) + "/")
			for y in range(1,cantImg):
				numImg = random.randint(1,9)
				f.write(" " + str(numImg))
			f.write('\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCaras/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 








def caseVariandoPersonasRed():
	
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y 15 iteraciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasRed+filename,'w')
		cantPersonas = random.randint(1, 41)
		f.write("../data/ImagenesCarasRed/ 28 23 " + str(cantPersonas) + ' 5 15' +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		for x in personas:
			f.write("s" + str(x) + "/ 1 2 3 4 5" +'\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCarasRed/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 

def caseVariandoPersonasEItersRed(maxIteraciones):
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y vario la cantidad de itereaciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasEItersRed+filename,'w')
		cantPersonas = random.randint(1, 41)
		iters = random.randint(1,maxIteraciones)
		f.write("../data/ImagenesCarasRed/ 28 23 " + str(cantPersonas) + ' 5 '+ str(iters) +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		for x in personas:
			f.write("s" + str(x) + "/ 1 2 3 4 5" +'\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCarasRed/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 

def caseVariandoPersonasEItersECantImgsRed(maxIteraciones):
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y vario la cantidad de itereaciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasEItersECantImgsRed+filename,'w')
		cantPersonas = random.randint(1, 41)
		iters = random.randint(1,maxIteraciones)
		f.write("../data/ImagenesCarasRed/ 28 23 " + str(cantPersonas) + ' 5 '+ str(iters) +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		cantImg = random.randint(1,9)	
		for x in personas:
			f.write("s" + str(x) + "/")
			for y in range(1,cantImg):
				f.write(" " + str(y))
			f.write('\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCarasRed/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 


def caseVariandoPersonasEItersECantImgsRandomRed(maxIteraciones):
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y vario la cantidad de itereaciones'
	for x in range(0,5):
		personas = []
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directoryVariandoPersonasEItersECantImgsRandomRed+filename,'w')
		cantPersonas = random.randint(1, 41)
		iters = random.randint(1,maxIteraciones)
		f.write("../data/ImagenesCarasRed/ 28 23 " + str(cantPersonas) + ' 5 '+ str(iters) +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		cantImg = random.randint(1,9)	
		for x in personas:
			f.write("s" + str(x) + "/")
			for y in range(1,cantImg):
				numImg = random.randint(1,9)
				f.write(" " + str(numImg))
			f.write('\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCarasRed/s" + str(x) + '/10.pgm ' + str(x) +'\n')
		f.close() 


caseVariandoPersonas(); 
caseVariandoPersonasEIters(100);
caseVariandoPersonasEItersECantImgs(100);
caseVariandoPersonasEItersECantImgsRandom(100);


caseVariandoPersonasRed(); 
caseVariandoPersonasEItersRed(100);
caseVariandoPersonasEItersECantImgsRed(100);
caseVariandoPersonasEItersECantImgsRandomRed(100);

