#set terminal png enhanced transparent size 1600,1000 font vera
#set output 'loadprofile_mc3.png'
set view 60, 30, 0.85, 1.1
set contour base
set cntrparam bspline 
set cntrparam levels incremental 0,0.1,1.0
set title "mc3 load generation profile" 
set xlabel "X axis" 
set ylabel "Y axis" 
set zlabel "Z axis" 
#set zlabel  offset character 1, 0, 0 font "" textcolor lt -1 norotate
set zrange [ 0.00000 : 1.00000 ] noreverse nowriteback
set style data lines
splot 'loadprofile_mc3.dat' matrix linewidth 2
