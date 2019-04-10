import subprocess
import sys
import os

directory = sys.argv[1]
N = sys.argv[2]
K = sys.argv[3]
method = sys.argv[4]
seuil = sys.argv[5]
maxiter = sys.argv[6]

result_filename = "Result_" + directory + ".csv"
f = open(result_filename, "w")
f.write("N;K;Méthode;Seuil;Maxiter;Temps Solver DP;Cout Solver DP;Temps Solver k-means;Cout Solver k-means;Temps Solver k-mean pareto;Cout solver k-means pareto;\n")

for filename in os.listdir(directory):
    print(filename)
    cmd = ["./src/test_final", N, K, method, directory + "/" + filename, seuil, maxiter]
    output = subprocess.run(cmd, capture_output=True, text=True)
    if (output.returncode != 0):
        print(output.stderr)
    out_string = output.stdout.split("\n") # On récupère le résultat sous forme de liste avec [N nb de points, temps solver DP, cout solver DP, temps solver k-means, cout solver k-means, temps solver k-means pareto, cout solver k-means pareto]
    f.write(out_string[0] + ";" + K + ";" + method + ";" + seuil + ";" + maxiter + ";" + out_string[1] + ";" + out_string[2] + ";" + out_string[3] + ";" + out_string[4] + ";" + out_string[5] + ";" + out_string[6] + ";\n")

# cmd = ["./src/test_final", "500", "5", method, "dataAlea/dataAlea_100_100_100_ex0.txt", "0.5", "1000"]
# output = subprocess.run(cmd, capture_output=True, text=True)
# if (output.returncode != 0):
    # print(output.stderr)
# else:
    # print(output.stdout)

f.close()