#!/usr/bin/env python
import math
import random

directory = '../../testVisualizador/instancias/rectas/'


def caseLineal(arq_y, palo1, palo2, mu, bola_x,bola_y):
	for i in range(1,11):
		filename = 'lineal'+str(i)+'.tiro'
		f = open(directory+filename,'w')
        # (bola_x,bola_y) es la posicion inicial de la pelota.
        # ax y ay describen la linealidad del eje x segun el tiempo
        # (x0,y0) es la posicion por donde va a entrar la pelota al arco.
		primera_linea = str(arq_y) +" "+ str(palo1) +" "+ str(palo2) +" "+ str(mu)
		# f.write("375 315 385 4"  +'\n')
		f.write(primera_linea  +'\n')
		ax = 1.0
		ay = 1.0
		x0 = 100.0
		y0 = random.uniform(palo1, palo2)
		print y0
		x1= bola_x
		y1 = bola_y
		my = -(y1-y0)/(x1-x0)
		result_x = 1000.0
		t = 0
		while(result_x > 100.0):
			result_y = my*t +bola_y
			result_x = -ax*t + bola_x
			if(t%17 == 0):
				f.write(str(result_x)[:6] + " " + str(result_y)[:6]  +'\n')
			t = t + 1
		f.close()

def interpolate(x, x_values, y_values):
    #Basado en el artículo de wikipedia.
    #Dado un x, una lista de x y otra de y, devuelve el y asociado al x dado.
    def _basis(j):
        p = [(x - x_values[m])/(x_values[j] - x_values[m]) for m in xrange(k) if m != j]
        return reduce(operator.mul, p)
    assert len(x_values) != 0 and (len(x_values) == len(y_values)), 'x and y cannot be empty and must have the same length'
    k = len(x_values)
    return sum(_basis(j)*y_values[j] for j in xrange(k))

def caseGeneral(gol_y, inicial_x, inicial_y, tiempo, cant_puntos_intermedios):
    #x lineal e y polinómico con grado máximo 
    #elige los y según x lineal y después divide según el tiempo a tardar.
    #Se asume que el arco está en x=125
    assert inicial_x >= 125, 'El inicial de la pelota es atrás del arco'
    assert inicial_x-125 <= cant_puntos_intermedios, 'Me estás pidiendo más puntos de los que hay'
    a = []
    b = []
    for i in abs(inicial_x-125):
        a.append(i)
        b.append(random.uniform(0,500))
    cant_puntos_finales = int(inicial_x/tiempo)
    res = []
    for i in cant_puntos_finales:
        res.append("i " + interpolate(i,a,b))
    return res


#caseLineal();
bola_x = random.uniform(300,1000)
bola_y = random.uniform(0,500)
# caseLineal(arq_y, palo1, palo2, mu, bola_x,bola_y):
caseLineal(375,315,385,4, bola_x, bola_y);
