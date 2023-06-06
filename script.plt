set xlabel 'x'
set ylabel 'y'
set key off
plot '-' using 1:2 with lines, '-' using 1:2 with points, '-' using 1:2 with lines
1 0.214
1.5 0.221
2 0.2237
2.5 0.2258
3 0.2262
3.5 0.2262
4 0.2275
4.5 0.2283
5 0.2288
e
1 0.218671
1.5 0.220156
2 0.221641
2.5 0.223126
3 0.224611
3.5 0.226096
4 0.227581
4.5 0.229066
5 0.230551
e
set title Regression Line
set key on
plot '-' using 1:2 with lines, '-' using 1:2 with points, '-' using 1:2 with lines
1 0.224532
5 0.22469
e
3 0.224611
set label a = 3.93792e-05at graph 0.5,0.85
set label b = 0.224493 at graph 0.5, 0.8
set label R = 0.875986 at graph 0.5,0.75
e
