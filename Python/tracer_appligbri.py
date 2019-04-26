import numpy as np
import matplotlib.pyplot as plt

def tracer_graphe():
    file = open("/home/romane/Documents/enssat2A/informatique/advancedAlgorithmics/AlgoAvan/test_python.txt","r")
    fileLineByLine = file.readlines()
    numberOfPoints = int(fileLineByLine[0])
    X = [i+1 for i in range(numberOfPoints)]
    Y = [0 for i in range(numberOfPoints)]
    Xcourbe = []
    Ycourbe = []
    #for each line of the file
    for i in range(numberOfPoints):
        line = fileLineByLine[i+1].split(" ")
        Y[i] = int(line[0])
        if line[1] == 'T\n':
            Xcourbe.append(i+1)
            Ycourbe.append(Y[i])


    #draw graphs
    plt.scatter(X, Y)

    plt.title('appligbri')
    plt.xlabel('X')
    plt.ylabel('Y')

    #plt.savefig('appligbri.png')
    #draw line between the concerned points
    plt.plot(Xcourbe,Ycourbe)
    plt.show()

    file.close()

if __name__ == "__main__":
    tracer_graphe()