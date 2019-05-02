#!/bin/bash
x=1
while [ $x -le 50 ]
do
  /usr/bin/time -f "%e" -o ./timesDynamique2.txt -a ./dynamique.o ./tests/test$x.txt
  x=$(( $x + 1 ))
done

	
