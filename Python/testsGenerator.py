import random as rd
import sys


numberOfTest = sys.argv[1]
for test in range(int(numberOfTest)):
	file = open("/home/romane/Documents/enssat2A/informatique/advancedAlgorithmics/algoAvanceSuite/AlgoAvan/tests/test"+str(test)+".txt", "w")

	numberOfPoints = 10*(test+1)
	print(numberOfPoints)
	abscisse = 0
	file.write(str(numberOfPoints)+"\n")
	for i in range(int(numberOfPoints)-1):
		abscisse = rd.randint(0, 500)
		file.write(str(i+1) + " " + str(abscisse)+"\n")
	file.write(str(numberOfPoints)+ " "+ str(rd.randint(0, 500)))

	file.close()
