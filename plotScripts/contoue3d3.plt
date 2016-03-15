# set terminal png transparent nocrop enhanced size 450,320 font "arial,8" 
# set output 'contours.10.png'
set key at screen 1, 0.9, 0 right top vertical Right noreverse enhanced autotitle nobox
set key opaque
unset key
set style textbox opaque margins  0.5,  0.5 noborder
set view 60, 30, 1, 1.1
set samples 20, 20
set isosamples 21, 21
set contour base
set cntrlabel  format '%8.3g' font ',7' start 5 interval 20
set cntrparam levels auto 10
set style data lines
set title "some more interesting contours" 
set xlabel "X axis" 
set ylabel "Y axis" 
set zlabel "Z " 
set zlabel  offset character 1, 0, 0 font "" textcolor lt -1 norotate
set zrange [ -1.00000 : 1.00000 ] noreverse nowriteback
splot [x=-3:3] [y=-3:3] sin(x) * cos(y)
pause -1
