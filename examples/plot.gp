reset                                                                           
set xlabel 'array size'
set ylabel 'time(usec)'
set title 'Avg. case performance'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:]'list_insertsort.log' using 1:2 with points title 'insertion sort',\
'list_qsort.log' using 1:2 with points title 'quick sort',\
'list_mergesort.log' using 1:2 with points title 'merge sort',\
'list_bubblesort.log' using 1:2 with points title 'bubble sort'
