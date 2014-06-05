#!/usr/bin/env python
import math
import random

directory = 'cases/'


def caseLineal(palox, paloy):
		filename = 'lineal.in'
		f = open(directory+"lineal/"+filename,'w')	
		f.write("375 315 385 4"  +'\n')
		for samples in range(1,11):
			f.write("375"  +'\n')
		f.close()



def linealFunction(palo1,palo2,bx,by):
	ax = 1.0		
	ay = 1.0
	x0 = 100.0
	y0 = 300.0
	x1= bx
	y1 = by
	my = -(y1-y0)/(x1-x0)
	print my
	print str(x0) + " " + str(y0)
	print str(x1) + " " + str(y1)
	for t in range(1,300):
		result_y = my*t +by
		result_x = -ax*t + bx
		print str(result_x) + " " + str(result_y);
	
#caseLineal();
linealFunction(375,315,300,200);
