import subprocess
import sys
import os
from create_data import *
import time

directory = sys.argv[1]
N = sys.argv[2]
K = sys.argv[3]
#method = sys.argv[4]
seuil = sys.argv[4]
maxiter = sys.argv[5]
nb_inst = sys.argv[6]

methods = ['median','medoids','means','ccenter','dcenter']

if(directory != "dataAlea" and directory != "dataAleaBox" and directory != "dataConcav" and directory != "dataConvex"):
    print("Erreur : format de génération de données non reconnu")
else:
    # On créé un certain nombre d'instances avec ces paramètres
    create_mult_data(directory, int(N), 0, 100, 0.5, 250, 250, int(nb_inst))

    for method in methods:
        print("Method : " + method)
        # Création du fichier de résultat 
        result_filename = "Results/Result_" + directory + "_" + method + "_" + time.asctime( time.localtime(time.time()) ) + ".csv"
        f = open(result_filename, "w")
        f.write("N;K;Méthode;Seuil;Maxiter;Temps Solver DP;Surcout Solver DP;Gain temps Solver k-means;Surcout Solver k-means;Gain temps Solver k-mean pareto;Surcout solver k-means pareto;\n")


        for filename in os.listdir(directory):
            print("Filename : " + filename)
            cmd = ["./src/test_final", N, K, method, directory + "/" + filename, seuil, maxiter]
            output = subprocess.run(cmd, capture_output=True, text=True)
            if (output.returncode != 0):
                print(output.stderr)
            out_string = output.stdout.split("\n") # On récupère le résultat sous forme de liste avec [N nb de points, temps solver DP, cout solver DP, temps solver k-means, cout solver k-means, temps solver k-means pareto, cout solver k-means pareto]
            f.write(out_string[0] + ";" + K + ";" + method + ";" + seuil + ";" + maxiter + ";" + out_string[1] + ";" + out_string[2] + ";" + out_string[3] + ";" + out_string[4] + ";" + out_string[5] + ";" + out_string[6] + ";\n")

        f.close()

    subprocess.run("rm -rf "+ directory+"/*.txt", shell=True)
