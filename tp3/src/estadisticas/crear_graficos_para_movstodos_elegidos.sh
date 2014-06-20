#!/bin/sh
#se ejecuta primero haciendo
#MODO DE USO: ./scriptGNUPLot.sh archivito.movstodos.TODOS
name=$1
/usr/bin/gnuplot << EOF
set datafile separator ","
set term postscript
# set style line 1  linetype 2 linecolor rgb "red"  linewidth 3.000 pointtype 2 pointsize default pointinterval 0
# set style line 2  linetype 2 linecolor rgb "orange"  linewidth 2.000 pointtype 2 pointsize default pointinterval 0
# set style line 3  linetype 2 linecolor rgb "yellow"  linewidth 3.000 pointtype 2 pointsize default pointinterval 0
# set style line 4  linetype 2 linecolor rgb "green"  linewidth 2.000 pointtype 2 pointsize default pointinterval 0
set style line 1 lc rgb '#0060ad' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 2 lc rgb '#cd4a4a' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 3 lc rgb '#ff7538' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 4 lc rgb '#ffa343' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 5 lc rgb '#8a795d' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 6 lc rgb '#848302' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 7 lc rgb '#1df914' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 8 lc rgb '#1cac78' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 9 lc rgb '#c0448f' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 10 lc rgb '#B2B247' lt 1 lw 1.5 pt 7 pi -1 ps 1
set style line 11 lc rgb '#232323' lt 1 lw 1.5 pt 7 pi -1 ps 1
set y2tics ("7(ataja)" 7)
set grid noxtics x2tics
unset grid
set grid
set xlabel "Tiempo" 
set ylabel "Distancia a la posición y actual de la pelota" 
set grid
set title "Métodos elegidos para $name Midiendo la distancia a la coordenada y de la pelota"
set output "graficos/$name.elegidos.png"
plot "./todos/$name" using 1:5 with linespoints ls 1 title "Método 3", \
     "./todos/$name" using 1:9 with linespoints ls 2 title "Método 7", \
     "./todos/$name" using 1:11 with linespoints ls 3 title "Método 9", \
     "./todos/$name" using 1:13 with linespoints ls 4 title "Método 11", \
     "./todos/$name" using 1:21 with linespoints ls 5 title "Método 19", \
     "./todos/$name" using 1:22 with linespoints ls 6 title "Método 20", \
     "./todos/$name" using 1:29 with linespoints ls 7 title "Método 27", \
     "./todos/$name" using 1:32 with linespoints ls 8 title "Método 30", \
     "./todos/$name" using 1:34 with linespoints ls 9 title "Método 32", \
     "./todos/$name" using 1:38 with linespoints ls 10 title "Método 36", \
     "./todos/$name" using 1:41 with linespoints ls 11 title "Método 39"
EOF

