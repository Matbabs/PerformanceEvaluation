#!/bin/bash
#

for i in 10 100 1000 10000 25000 50000 100000 250000 500000 1000000
do
	for k in {1..10}
	do
	    echo $i >> $2
	    echo 1 >> $2
	    $1 $i 1 >> $2
	    echo >> $2
	done
done
	  
