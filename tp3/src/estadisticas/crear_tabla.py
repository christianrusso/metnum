#!/usr/bin/env python
# -*- coding: utf-8 -*-
import subprocess
from glob import glob
import os
from fnmatch import fnmatch
import sys
import linecache

modo_de_uso=' ERROR: Cantidad de parámetros inválida \n \
 No Recibe nada \n \
 ejemplo: r1_125.movsgol \n \
 Hace:  \n \
Une todas las estadísticas en un mismo archivo: file.TODOS'
def listfiles(root, pattern):
  for path, subdirs, files in os.walk(root):
    for name in files:
      if fnmatch(name, pattern):
        yield os.path.join(path, name)


def main(argv = sys.argv):
  if(len(argv) != 1):
    print "Este script no recibe parametros"
    sys.exit(1)

  #Checkeo que sean parámetros válidos:

  matriz = []
  path = 'met0/'
  # print "Archivo: " + path_archivito
  archivos_movsgol = listfiles(path,"*.movsgol")

  fila_estadistica = crear_fila_estadistica()
  cant_tiros = 0
  filas_finales = [crear_fila_titulos()]
  for x in archivos_movsgol:
    arch = x.split("/")[1]
    ret_juntar_todo =subprocess.call(["python","juntar_todo.py",arch])
    if(ret_juntar_todo!=0):
        print "Falló el juntar_todo.py para el archivo: " + arch
        sys.exit(1)
    #Ya tengo todas las estadísticas con todos los métodos del tiro x
    #Lo agrego a un string
    fila_tabla = nueva_fila_desde_archivo("todos/"+arch+".TODOS",fila_estadistica)
    filas_finales.append(fila_tabla)
    cant_tiros = cant_tiros+1
  #Ya tengo la tabla principal. Ahora a crear las estadísticas
  porc_atajados = ['% atajados']
  for i in range(1,41):
    porc_atajados.append(str(float(fila_estadistica[i])/float(cant_tiros)))

  filas_finales.append(fila_estadistica)
  filas_finales.append(porc_atajados)
  #Ya tengo la tabla completa. Ahora a imprimir:
  f = open("tabla/tabla.csv",'w')
  print "Escribiendo tabla/tabla.csv"
  for x in filas_finales:
    stringsito = str(x[0])
    for i in range(1,len(x)-1):
        stringsito = stringsito +","+ str(x[i])
    f.write(stringsito+"\n")
  f.close()




#################################################################
def nueva_fila_desde_archivo(arch,fila_estadistica):
    #Extrae la última línea del archivo, que se convertirá en una nueva fila de mi tabla
    #Además, actualiza los totales en la última línea dependiendo si la atajo o no
    lineas = linecache.getlines(arch)
    ultima_linea = lineas[len(lineas)-1].split(",")
    assert len(ultima_linea)==41,"El archivo"+arch+"no tiene 41 columnas"
    for i  in range(1,41):
        #Me salteo la primera columna porque es de la función f(x)=x+1
        #El método i corresponde a la columna i+1
        if(float(ultima_linea[i])<=7):
            #Si lo atajo:
            fila_estadistica[i] = fila_estadistica[i]+1
    primera_col = ultima_linea.pop(0) #popeo la primer columna que no sirve para nada
    list_path = arch.split("/")
    archivito = list_path[len(list_path)-1]
    archivito_sin_extension = archivito.split("_125")[0]
    fila_final= [archivito_sin_extension]
    fila_final.extend(ultima_linea)
    return fila_final


#################################################################
def crear_fila_estadistica():
    #Crea las línea final, en la cual se van a ir actualizando:
    #Pos 0) los totales atajos por método
    #Pos 1) el porcentaje de atajados
    #Pos 2) la distancia mediaA
    #Cada fila tiene 41 columnas: el nombre del método y los 40 métodos
    fila_totales = ['TOTALES']

    for i in range(1,41):
        fila_totales.append(0)
    return fila_totales
#################################################################
def crear_fila_titulos():
    fila_titulos = ['Tiros']
    for i in range(0,40):
        fila_titulos.append('met'+str(i))
    return fila_titulos
#################################################################
if __name__ == "__main__":
    main()
