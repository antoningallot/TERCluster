#TERClustering
Ce projet est un projet de Master1 à l'Université Paris Saclay pour l'UE TER.
Notre TER porte sur le sujet "Clustering d'un front de pareto 2D" et plus spécifiquement sur les heuristiques appliquées à ce sujet.

#Présentation du code
Notre code a été pensé programmation objet et comporte donc plusieurs classes :
Point.cpp permet de représenter un point avec ses coordonnées en attribut.
Instance.cpp permet de représenter notre front de pareto sous la forme d'un vecteur de points.
Solver_parent.cpp est la classe mère de nos solvers et n'implémente pas la fonction principale solve, elle ne doit pas etre utilisée.
Solver.cpp est le sovler principal utilisant la programmation dynamique.
Solver_kmeans.cpp est un solver utilisant l'algorithme de Lloyd générique.
Solver_kmeans_pareto.cpp est un solver utilisant l'algorithme de Lloyd optimisé pour un front de pareto.

#Utilisation du code
Le principal fichier exécutable généré par notre code est test_final. Cet exécutable ne sera jamais exécuté seul mais sera utilisé par le programme python test.py qui lancera ce programme et récuperera ses résultats, grace au module python subprocess. Un makefile est présent dans le dossier src, pour compiler la partie C++ il suffit donc de se placer dans ce dossier et appeler make.
Pour exécuter le code il faut exécuter le programme python test.py, qui prend 7 arguments :
directory : le répertoire dans lequel aller chercher les données, qui correspond aussi à la méthode de génération des données
N : le nombre de points des instances que l'on va générer
K : le nombre de clusters que l'on veut considérer
method : la méthode de calcul de cout de clustering utilisée par nos solvers (median, means...)
seuil : le paramètre de seuil utilisé dans l'algorithme de Lloyd
maxiter : le paramètre d'itérations maximum utilisé dans l'algorithme de Lloyd
nb_inst : le nombre d'instances de données que l'on veut créer pour ces paramètres

Le programme va exécuter le programme C++ test_final et récupérer ses sorties consoles, puis écrire les résultats dans un fichier csv.