#!/usr/bin/env python
import math
import random

directory = '../../testVisualizador/instancias/rectas/'


def caseLineal(palo1, palo2,bx,by):
	for i in range(1,11):
		filename = 'lineal'+str(i)+'.tiro'
		f = open(directory+filename,'w')
        # (bx,by) es) la posicion inicial de la pelota.
        # (ax,ay) describen la linealidad del eje x segun el tiempo
        # (x0,y0) es la posicion por donde va a entrar la pelota al arco.
		bx = random.uniform(300,1000)
		by = random.uniform(0,500)
		f.write("375 315 385 4"  +'\n')
		ax = 1.0
		ay = 1.0
		x0 = 100.0
		y0 = random.uniform(palo1, palo2)
		print y0
		x1= bx
		y1 = by
		my = -(y1-y0)/(x1-x0)
		result_x = 1000.0
		t = 0 
		while(result_x > 100.0):
			result_y = my*t +by
			result_x = -ax*t + bx
			if(t%17 == 0):
				f.write(str(result_x)[:6] + " " + str(result_y)[:6]  +'\n')
			t = t + 1
		f.close()



def linealFunction(palo1,palo2,bx,by):
	ax = 1.0
	ay = 1.0
	x0 = 100.0
	y0 = 300.0
	x1= bx
	y1 = by
	my = -(y1-y0)/(x1-x0)
	result_x = 1000.0
	t = 0
	while(result_x > 100.0):
		result_y = my*t +by
		result_x = -ax*t + bx
		print str(result_x) + " " + str(result_y);
		t = t + 1

#caseLineal();
caseLineal(375,315,300,200);
