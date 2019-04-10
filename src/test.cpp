#include <vector>
#include <chrono>
#include "Solver.h"
#include "Solver_kmeans.h"
#include "Solver_kmeans_pareto.h"
 
using namespace std;

// trim from end (in place)
void rtrim(string &s) {
    s.erase(s.size()-4, 4);
    // return s;
}

int main (int argc, char *argv[]) {
    if(argc != 7){
        cout << "Need 7 arguments\n";
    }
    else {

        // Récupération de tous les paramètres des test
        int n = atoi(argv[1]); // Nb de points
        int k = atoi(argv[2]); // Nb de clusters
        string methode = argv[3];
        string filename = argv[4];
        float seuil = (float) atoi(argv[5]);
        int maxiter = atoi(argv[6]);
        
        cout << "Debut constructeur Solver\n";
        Solver s(n, k, filename);
        Solver_kmeans km(n, k, filename, seuil, maxiter);
        // cout << "Contructeur fini\n";
        int methode_code = 0;
        if (methode == "median"){ methode_code = 1; }
        else if (methode == "means"){ methode_code = 2; }
        else if (methode == "medoids"){ methode_code = 3; }
        else if (methode == "dcenter"){ methode_code = 4; }
        else if (methode == "dcenterv2"){ methode_code = 5; }
        else if (methode == "ccenter"){ methode_code = 6; }
        else {
            cout << "Methode de calcul invalide\n";
        }
        cout << "Start DP\n";
        // Record start time
        auto start_DP = chrono::high_resolution_clock::now();
        s.solve(methode_code);
        s.backtrack(methode_code);
        // Record end time
        auto finish_DP = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_DP = finish_DP - start_DP;

        cout << "DP fini\n";

        float result_DP = s.get_result(methode_code); 
        cout << "Temps d'exécution de DP : " << elapsed_DP.count() << endl;
        cout << "Cout de DP : " << result_DP << endl;

        // Record start time
        auto start_lloyd = chrono::high_resolution_clock::now();
        km.solve(methode_code);
        auto finish_lloyd = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_lloyd = finish_lloyd - start_lloyd;
        
        cout << "Lloyd fini\n";
        float result_lloyd = km.get_result(methode_code);
        
        cout << "Temps d'exécution de Lloyd : " << elapsed_lloyd.count() << endl;
        cout << "Cout de Lloyd : " << result_lloyd << endl;
        
        cout << "Gap Lloyd/DP : " << result_lloyd - result_DP << endl;
        // rtrim(filename);
        // filename = filename + "_result.txt";
        // km.write_result(filename);
    }
    
    return 0;
}
