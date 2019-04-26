import random as rd
import sys


numberOfTest = sys.argv[1]
for test in range(int(numberOfTest)):
	print("coucou")
	file = open("test"+str(test)+".txt", "w")

	numberOfPoints = rd.randint(0, 500)
	abscisse = 0
	file.write(str(numberOfPoints)+"\n")
	for i in range(numberOfPoints-1):
		abscisse = rd.randint(0, 500)
		file.write(str(i+1) + " " + str(abscisse)+"\n")
	file.write(str(numberOfPoints)+ " "+ str(rd.randint(0, 500)))

	file.close()
