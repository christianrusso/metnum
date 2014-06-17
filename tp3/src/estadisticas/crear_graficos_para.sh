#!/bin/sh
#se ejecuta primero haciendo
#MODO DE USO: ./scriptGNUPLot.sh archivito.movsgol.TODOS
name=$1
/usr/bin/gnuplot << EOF
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
set title "Métodos 0-10 para $1"
set xlabel "Tiempo" 
set ylabel "Cercanía a la posición final de la pelota" 
set autoscale
# set bmargin  6
# unset colorbox
set output "graficos/$1-0a10.png"
plot "./todos/1_125.movs.TODOS" using 1:2 with linespoints ls 1 title "Método 0", \
     "./todos/1_125.movs.TODOS" using 1:3 with linespoints ls 2 title "Método 1", \
     "./todos/1_125.movs.TODOS" using 1:4 with linespoints ls 3 title "Método 2", \
     "./todos/1_125.movs.TODOS" using 1:5 with linespoints ls 4 title "Método 3", \
     "./todos/1_125.movs.TODOS" using 1:6 with linespoints ls 5 title "Método 4", \
     "./todos/1_125.movs.TODOS" using 1:7 with linespoints ls 6 title "Método 5", \
     "./todos/1_125.movs.TODOS" using 1:8 with linespoints ls 7 title "Método 6", \
     "./todos/1_125.movs.TODOS" using 1:9 with linespoints ls 8 title "Método 7", \
     "./todos/1_125.movs.TODOS" using 1:10 with linespoints ls 9 title "Método 8", \
     "./todos/1_125.movs.TODOS" using 1:11 with linespoints ls 10 title "Método 9" , \
     "./todos/1_125.movs.TODOS" using 1:12 with linespoints ls 11 title "Método 10"

set output "graficos/$1-10a21.png"
plot "./todos/1_125.movs.TODOS" using 1:13 with linespoints ls 1 title "Método 11", \
     "./todos/1_125.movs.TODOS" using 1:14 with linespoints ls 2 title "Método 12", \
     "./todos/1_125.movs.TODOS" using 1:15 with linespoints ls 3 title "Método 13", \
     "./todos/1_125.movs.TODOS" using 1:16 with linespoints ls 4 title "Método 14", \
     "./todos/1_125.movs.TODOS" using 1:17 with linespoints ls 5 title "Método 15", \
     "./todos/1_125.movs.TODOS" using 1:18 with linespoints ls 6 title "Método 16", \
     "./todos/1_125.movs.TODOS" using 1:19 with linespoints ls 7 title "Método 17", \
     "./todos/1_125.movs.TODOS" using 1:20 with linespoints ls 8 title "Método 18", \
     "./todos/1_125.movs.TODOS" using 1:21 with linespoints ls 9 title "Método 19", \
     "./todos/1_125.movs.TODOS" using 1:22 with linespoints ls 10 title "Método 20", \
     "./todos/1_125.movs.TODOS" using 1:23 with linespoints ls 11 title "Método 21"
EOF

