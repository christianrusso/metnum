#!/bin/sh
#se ejecuta primero haciendo
#MODO DE USO: ./scriptGNUPLot.sh archivito.movstodos.TODOS
name=$1
echo $name
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
set xlabel "Tiempo t" 
set ylabel "Distancia en la coordenada Y de la pelota y el arquero" 
set autoscale
# set title "Mejores métodos elegidos para $name"
# set output "tabla/graficos/$name.mejores_elegidos.ps"
# plot "./todos/$name" using 1:26 with linespoints ls 1 title "Método 24", \
#      "./todos/$name" using 1:28 with linespoints ls 2 title "Método 26", \
#      "./todos/$name" using 1:32 with linespoints ls 3 title "Método 30"

# set title "Peores métodos elegidos para $name"
# set output "tabla/graficos/$name.peores_elegidos.ps"
# plot "./todos/$name" using 1:15 with linespoints ls 4 title "Método 13", \
#      "./todos/$name" using 1:20 with linespoints ls 5 title "Método 18", \
#      "./todos/$name" using 1:22 with linespoints ls 6 title "Método 20"
set title "Metodos elegidos para $name"
set output "tabla/graficos/$name.elegidos.ps"
plot "./todos/$name" using 1:2 with linespoints ls 1 title "Método 0", \
     "./todos/$name" using 1:6 with linespoints ls 2 title "Método 4", \
     "./todos/$name" using 1:11 with linespoints ls 3 title "Método 9", \
     "./todos/$name" using 1:16 with linespoints ls 4 title "Método 14", \
     "./todos/$name" using 1:21 with linespoints ls 5 title "Método 19", \
     "./todos/$name" using 1:26 with linespoints ls 6 title "Método 24", \
     "./todos/$name" using 1:29 with linespoints ls 7 title "Método 27"
EOF

