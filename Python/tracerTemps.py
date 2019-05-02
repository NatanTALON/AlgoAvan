import numpy as np
import matplotlib.pyplot as plt
import sys

def tracer_graphe():
	file = open("/home/romane/Documents/enssat2A/informatique/advancedAlgorithmics/algoAvanceSuite/AlgoAvan/timesEssaiSucc1Sur2.txt","r")
	fileLineByLine = file.readlines()
	#num_lines = int(fileLineByLine[0])
	X = [(i+1)*10 for i in range(45)]
	#X = [int((fileLineByLine[i+1].split(" "))[0]) for i in range(num_lines-1)]
	Y = [float((fileLineByLine[i].split("\n"))[0]) for i in range(45)]
	#Y = [float((((fileLineByLine[i+1].split(" "))[1]).split("\n"))[0]) for i in range(num_lines-1)]

	print(Y)

		#draw graphs
	plt.plot(X, Y)

	plt.title('temps d\'exécution en secondes de  l\'algorithme par essais successifs avec \n Xopt initial différent en fonction du nombre de points dans l\'ensemble S')
	plt.xlabel('X')
	plt.ylabel('Y')

	plt.savefig('tracerEssaiSucc1sur2.png')
	plt.show()

	file.close()

if __name__ == "__main__":
    tracer_graphe()
