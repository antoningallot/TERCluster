import subprocess
import sys
import os

directory = sys.argv[1]
N = sys.argv[2]
K = sys.argv[3]
method = sys.argv[4]
seuil = sys.argv[5]
maxiter = sys.argv[6]
solver1 = sys.argv[7]
solver2 = sys.argv[8]

if solver1 == "DP":
     s1 = 1
elif solver1 == "Kmeans":
    s1 = 2
else:
    s1 = 3

if solver2 == "DP":
     s2 = 1
elif solver2 == "Kmeans":
    s2 = 2
else:
    s2 = 3


result_filename = "Result_" + solver1 + "/" + solver2 + directory + ".csv"
f = open(result_filename, "w")
f.write("Solver1:" + solver1 + ";" + "Solver2:" + solver2 + ";\n")
f.write("N;K;Seuil;Maxiter;Temps Solver1;Cout Solver1;Temps Solver2;Cout Solver2\n")

for filename in os.listdir(directory):
    cmd = ["./src/test", N, K, method, directory + "/" + filename, seuil, maxiter]
    output = subprocess.run(cmd, capture_output=True, text=True)
    out_string = output.stdout.split("\n") # On récupère le résultat sous forme de liste avec [temps solver1, cout solver1, temps solver2, cout solver2]
    f.write(N + ";" + K + ";" + method + ";" + seuil + ";" + out_string[0] + ";" + out_string[1] + ";" + out_string[2] + ";" + out_string[3] + ";\n")

f.close()