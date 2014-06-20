#!/bin/sh
#se ejecuta primero haciendo
#MODO DE USO: ./scriptGNUPLot.sh archivito.movstodos.TODOS
name=$1
/usr/bin/gnuplot << EOF
set yrange [0:50] writeback
set datafile separator ","
set term png size 900, 600  #le digo que la salida es un PNG
# set style line 1  linetype 2 linecolor rgb "red"  linewidth 3.000 pointtype 2 pointsize default pointinterval 0
# set style line 2  linetype 2 linecolor rgb "orange"  linewidth 2.000 pointtype 2 pointsize default pointinterval 0
# set style line 3  linetype 2 linecolor rgb "yellow"  linewidth 3.000 pointtype 2 pointsize default pointinterval 0
# set style line 4  linetype 2 linecolor rgb "green"  linewidth 2.000 pointtype 2 pointsize default pointinterval 0
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 2 lc rgb '#cd4a4a' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 3 lc rgb '#ff7538' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 4 lc rgb '#ffa343' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 5 lc rgb '#8a795d' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 6 lc rgb '#fdfc74' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 7 lc rgb '#1df914' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 8 lc rgb '#1cac78' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 9 lc rgb '#c0448f' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 10 lc rgb '#fc2847' lt 1 lw 2 pt 7 pi -1 ps 1.5
set style line 11 lc rgb '#232323' lt 1 lw 2 pt 7 pi -1 ps 1.5
set pointintervalbox 3
set xlabel "Tiempo" 
set ylabel "Distancia a la posición y actual de la pelota" 
set title "Métodos 0-10 para $name Midiendo la distancia a la coordenada y de la pelota"
set output "graficos/$name-0a10CuadMin.png"
plot "./todos/$name" using 1:3 with linespoints ls 2 title "Método 1", \
     "./todos/$name" using 1:4 with linespoints ls 3 title "Método 2", \
     "./todos/$name" using 1:5 with linespoints ls 4 title "Método 3", \
     "./todos/$name" using 1:6 with linespoints ls 5 title "Método 4", \
     "./todos/$name" using 1:7 with linespoints ls 6 title "Método 5", \
     "./todos/$name" using 1:8 with linespoints ls 7 title "Método 6", \
     "./todos/$name" using 1:9 with linespoints ls 8 title "Método 7", \
     "./todos/$name" using 1:10 with linespoints ls 9 title "Método 8", \
     "./todos/$name" using 1:11 with linespoints ls 10 title "Método 9", \
     "./todos/$name" using 1:12 with linespoints ls 11 title "Método 10", \
     "./todos/$name" using 1:13 with linespoints ls 1 title "Método 11"

set title "Métodos 11-21 para $name Midiendo la distancia a la coordenada y de la pelota"
set output "graficos/$1-10a21Estimacion.png"
plot "./todos/$name" using 1:14 with linespoints ls 2 title "Método 12", \
     "./todos/$name" using 1:15 with linespoints ls 3 title "Método 13", \
     "./todos/$name" using 1:16 with linespoints ls 4 title "Método 14", \
     "./todos/$name" using 1:17 with linespoints ls 5 title "Método 15", \
     "./todos/$name" using 1:18 with linespoints ls 6 title "Método 16", \
     "./todos/$name" using 1:19 with linespoints ls 7 title "Método 17", \
     "./todos/$name" using 1:20 with linespoints ls 8 title "Método 18", \
     "./todos/$name" using 1:21 with linespoints ls 9 title "Método 19", \
     "./todos/$name" using 1:22 with linespoints ls 10 title "Método 20", \
     "./todos/$name" using 1:23 with linespoints ls 11 title "Método 21"

set title "Métodos 22-32 para $name Midiendo la distancia a la coordenada y de la pelota"
set output "graficos/$name-22a32MuestrasLimitadas.png"
plot "./todos/$name" using 1:24 with linespoints ls 1 title "Método 22", \
     "./todos/$name" using 1:25 with linespoints ls 2 title "Método 23", \
     "./todos/$name" using 1:26 with linespoints ls 3 title "Método 24", \
     "./todos/$name" using 1:27 with linespoints ls 4 title "Método 25", \
     "./todos/$name" using 1:28 with linespoints ls 5 title "Método 26", \
     "./todos/$name" using 1:29 with linespoints ls 6 title "Método 27", \
     "./todos/$name" using 1:30 with linespoints ls 7 title "Método 28", \
     "./todos/$name" using 1:31 with linespoints ls 8 title "Método 29", \
     "./todos/$name" using 1:32 with linespoints ls 9 title "Método 30", \
     "./todos/$name" using 1:33 with linespoints ls 10 title "Método 31", \
     "./todos/$name" using 1:34 with linespoints ls 11 title "Método 32"

set title "Métodos 32-39 para $name Midiendo la distancia a la posición final de la pelota"
set output "graficos/$name-32a39MuestrasLimitadasYEstimacion.png"
plot "./todos/$name" using 1:35 with linespoints ls 1 title "Método 33", \
     "./todos/$name" using 1:36 with linespoints ls 2 title "Método 34", \
     "./todos/$name" using 1:37 with linespoints ls 3 title "Método 35", \
     "./todos/$name" using 1:38 with linespoints ls 4 title "Método 36", \
     "./todos/$name" using 1:39 with linespoints ls 5 title "Método 37", \
     "./todos/$name" using 1:40 with linespoints ls 6 title "Método 38", \
     "./todos/$name" using 1:41 with linespoints ls 7 title "Método 39", \
     "./todos/$name" using 1:2 with linespoints ls 8 title "Método 0"
EOF

