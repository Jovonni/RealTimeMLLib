reset
unset key
set xrange [0:40]
set yrange [0:7]
set xlabel 'Effort [a.u.]'
set ylabel 'Output [a.u.]'
p 'helpergrid.dat' u 1:2:(0):1 w xerror ps 0 lt 0 lw 0.5 lc rgb "#ff0000", \
'' u 1:2 w i lt 0 lw 0.5 lc rgb "#ff0000", \
'' u 1:2 w lp pt 7 ps 1.5
pause -1
