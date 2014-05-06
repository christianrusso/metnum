#!/usr/bin/env python
import math
import random

directory = 'cases/'


# Considerar al menos dos instancias de prueba, generando distintas discretizaciones para cada
#una de ellas y comparando la ubicacion de la isoterma buscada respecto de la pared externa del
#horno. Se sugiere presentar graficos de temperatura o curvas de nivel para los mismos, ya sea
#utilizando las herramientas provistas por la catedra o implementando sus propias herramientas de
#graficacion. Estudiar la proximidad de la isoterma buscada respecto de la pared exterior del horno
#en funcion de distintas granularidades de discretizacion y las condiciones de borde. Analizar
#tambien el tiempo de computo requerido en funcion de la granularidad de la discretizacion.


def caseVariandoPersonas():
	
	description = 'Vario la cantidad de personas con 5 imagenes cada una con 5 imagenes y 15 iteraciones'
	personas = []
	for x in range(0,5):
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		cantPersonas = random.randint(0, 41)
		f.write("../data/ImagenesCaras/ 112 92 " + str(cantPersonas) + ' 5 15' +'\n')
		for x in range(0,cantPersonas):
			personas.append(random.randint(0, 41))
		personas.sort()
		for x in personas:
			f.write("s" + str(x) + "/ 1 2 3 4 5" +'\n')
		f.write(str(cantPersonas)+'\n')
		for x in personas:
			f.write("../data/ImagenesCaras/s" + str(x) + ' /10.pgm 1' +'\n')
		f.close() 



def case1():
	
	description = 'Mas radios. Impacto del cambio n de las discretizaciones en el calculo de la Isoterma. Que ocurre en te distintos, n distintos.'

	ri = 50
	re = 65	
	m = 30
	n = 30
	iso = 500
	nist = 4
	

	for x in range(0,5):
		filename = 'case1'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')
	 	buildInst(getTe50,n,f)
	 	buildInst(getTe100,n,f)
	 	buildInst(getTe150,n,f)
	 	buildInst(getTe200,n,f)
	
		m = m*2
		f.close() 

def case2():
	#GENERA DATOS PARA EL CASO 1 DEL INFORME
	# NO BORRAR
	description = 'Mas radios. Impacto del cambio n de las discretizaciones en el calculo de la Isoterma. Que ocurre en te distintos, n distintos.'

	ri = 5
	re = 150	
	m = 4
	n = 30
	iso = 500
	nist = 4
	

	for x in range(0,10):
		filename = 'case2'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')
	 	buildInst(getTe50,n,f)
	 	buildInst(getTe100,n,f)
	 	buildInst(getTe150,n,f)
	 	buildInst(getTe200,n,f)
	
		m = m+10
		f.close() 


def case3():
	
	description = 'Mas radios. Impacto del cambio n de las discretizaciones en el calculo de la Isoterma. Que ocurre en te distintos, n distintos.'

	ri = 5
	re = 15	
	m = 10
	n = 30
	iso = 500
	nist = 4
	

	for x in range(0,10):
		filename = 'case3'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')
	 	buildInst(getTe50,n,f)
	 	buildInst(getTe100,n,f)
	 	buildInst(getTe150,n,f)
	 	buildInst(getTe200,n,f)
	
		n = n+10
		f.close() 

def case4():
	
	description = 'Mas radios. Impacto del cambio n de las discretizaciones en el calculo de la Isoterma. Que ocurre en te distintos, n distintos.'

	ri = 5
	re = 15	
	m = 10
	n = 30
	iso = 500
	nist = 4
	

	for x in range(0,10):
		filename = 'case4'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')
	 	buildInst(getTe50,n,f)
	 	buildInst(getTe100,n,f)
	 	buildInst(getTe150,n,f)
	 	buildInst(getTe200,n,f)
	
		m = m+3
		n = n+3
		f.close() 

def case5():
	
	description = 'Mas radios. Impacto del cambio n de las discretizaciones en el calculo de la Isoterma. Que ocurre en te distintos, n distintos.'

	ri = 5
	re = 100
	m = 30
	n = 30
	iso = 500
	nist = 4
	

	for x in range(0,10):
		filename = 'case5'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')
	 	buildInst(getTe50,n,f)
	 	buildInst(getTe100,n,f)
	 	buildInst(getTe150,n,f)
	 	buildInst(getTe200,n,f)
	
		m = m+15
		n = n+15
		f.close() 


def case6():
	
	description = 'Mas radios. Impacto del cambio n de las discretizaciones en el calculo de la Isoterma. Que ocurre en te distintos, n distintos.'

	ri = 50
	re = 65	
	m = 90
	n = 30
	iso = 500
	nist = 1
	

	for x in range(0,10):
		filename = 'case4'+chr(ord('a')+x)+'.in'	
		f = open(directory+filename,'w')
		f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')
	 	buildInst(getTeOneHotEdge,n,f)
 	    #buildInst(getTeOneHotEdge,n,f)
	 	#buildInst(getTeMultipleHotSpots,n,f)

		n = n*2
		f.close() 

def case8():

	description = 'un punto de mayor temperatura que da una vuelta a todo el horno'

	ri = 10
	re = 100	
	m = 29
	n = 30
	iso = 500
	nist = 90
	
	filename = 'case8.in'	
	f = open(directory+filename,'w')
	f.write(str(ri)+" "+str(re)+" "+str(m+1)+" "+str(n)+" "+str(iso)+" "+str(nist)+'\n')

	for x in range(0,nist):
		Te=""
		Ti=""
		for i in range(0,n):	
			if (i > 0):
				Te = Te + " "

			Ti = Ti + "1500 ";
			Te = Te + str(getTeOneHotEdgeVariable(i,n,x,nist));

		f.write(Ti)
		f.write(Te+"\n")

	f.close() 


def getTeOneHotEdge(i,n):
	return (150/(math.pi**2)) * ((i*2*math.pi/(n+1) - math.pi)**2) + 50


def getTeOneHotEdgeVariable(i,n,caseNumber,TotalCases):
	return ((math.sin(12*i*2*math.pi/n))**2 )*150 + 50


def getTeMultipleHotSpots(i,n):
	return ((math.sin(i*2*math.pi/n) * math.pi*caseNumber/TotalCases )**2 )*150 + 50 #no me acuerdo si iba un dos al lado del pi tmb

def getTe50(tita,n):
	return 50;

def getTe100(tita,n):
	return 100;

def getTe150(tita,n):
	return 150;

def getTe200(tita,n):
	return 200;

	

def buildInst(method,n,f):
	Te=""
	Ti=""
	for i in range(0,n):	
		if (i > 0):
			Te = Te + " "

		Ti = Ti + "1500 ";
		Te = Te + str(method(i,n));

	f.write(Ti)
	f.write(Te+"\n")


# Discretizaciones - Pedido en enunciado 
caseVariandoPersonas(); #caso que se usa en el informe en el punto (a) Leti