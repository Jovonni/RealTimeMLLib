# set terminal png transparent nocrop enhanced size 450,320 font "arial,8" 
# set output 'contours.20.png'
set key at screen 1, 0.9, 0 right top vertical Right noreverse enhanced autotitle nobox
unset key
set style textbox opaque margins  0.5,  0.5 noborder
set logscale z 10
set view 20, 340, 1, 1.1
set isosamples 60, 60
set cntrlabel  format '%8.3g' font ',7' start 2 interval 20
set hidden3d back offset 1 trianglepattern 3 undefined 1 altdiagonal bentover
set cntrparam order 8
set style data lines
set ticslevel 0
set title "Rosenbrock Function" 
set xlabel "x" 
set ylabel "y" 
set zlabel "Z " 
set zlabel  offset character 1, 0, 0 font "" textcolor lt -1 norotate
Rosenbrock(x,y) = (1-x)**2 + 100*(y - x**2)**2
u = 0.0
x = 0.0
GPFUN_Rosenbrock = "Rosenbrock(x,y) = (1-x)**2 + 100*(y - x**2)**2"
## Last datafile plotted: "glass.dat"
splot [-1.5:1.5] [-0.5:1.5] Rosenbrock(x,y)
pause -1
