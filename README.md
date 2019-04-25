# AlgoAvan

Soit S un ensemble de n points du plan avec n > 2, dont les abscissent valent 1,2,3,...,n et dont les ordonnées sont quelconques.
Les algorithmes suivants calculent la meilleure approximation de cet ensemble par une ligne brisée (suite de segments dont les extrémités sont des points de S).

La qualité d'une approximation de S par une ligne brisée se mesure pour partie en calculant la somme SD des distances euclidiennes des points de S au segment de droite dont les extrémités les encadrent. On ajoute à SD un terme positif m * C proportionnel au nombre m de segments composant la ligne brisée.

Le premier algoritme propose une recherche de la solution optimale à l'aide d'une approche par essais successifs de type solution à trous. [fichier essais_succ.c]

Le second algorithme propose une recherche du coût optimal à l'aide d'une approche dynamique. [fichier dynamique2.c]

Le troisième algorithme propose une recherche de la solution optimale à l'aide d'une approche dynamique. [fichier dynamique3.c]

Pour compiler chacun des programmes utilisez respectivement :
- gcc essais_succ.c distance.c parser.c writer.c -lm -o [nom]
- gcc dynamique2.c distance.c parser.c -lm -o [nom]
- gcc dynamique3.c distance.c parser.c writer.c -lm -o [nom]

Lancez le programme en indiquant le nom du fichier texte contenant la liste des points à considérer. Vous pouvez aussi renseigner en second argument la valeur de C (sinon C = 1,5).
Lancez le script python pour afficher le tracé de la solution optimale trouvée.
