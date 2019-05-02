#!bin/bash
x=1
while [ $x -le 53000 ]
do
  ./dynamique2_temps /home/romane/Documents/enssat2A/informatique/advancedAlgorithmics/algoAvanceSuite/AlgoAvan/tests/test$x.txt
  x=$(( $x + 1 ))
done

	
