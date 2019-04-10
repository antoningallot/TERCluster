#include <chrono>
#include "Solver.h"
#include "Solver_kmeans.h"
#include "Solver_kmeans_pareto.h"
 
using namespace std;

// trim las 4 characters (.txt here) from end (in place)
void rtrim(string &s) {
    s.erase(s.size()-4, 4);
}

int main (int argc, char *argv[]) {
    if(argc != 7){
        cout << "Need 7 arguments\n";
        return 0;
    }
    else {

        // Récupération de tous les paramètres des test
        int n = atoi(argv[1]); // Nb de points
        int k = atoi(argv[2]); // Nb de clusters
        string methode = argv[3]; // Méthode de calcul
        string filename = argv[4]; // Fichier sur lequel tester
        float seuil = (float) atoi(argv[5]); // Seuil pour algo de Lloyd
        int maxiter = atoi(argv[6]); // Maxiter pour algo de Lloyd

        // cout << "Début constructeur" << endl;
        Solver DP(n, k, filename);
        Solver_kmeans km(n, k, filename, seuil, maxiter);
        Solver_kmeans_pareto km_pareto(n, k, filename, seuil, maxiter);
        
        int methode_code = 0;
        if (methode == "median"){ methode_code = 1; }
        else if (methode == "means"){ methode_code = 2; }
        else if (methode == "medoids"){ methode_code = 3; }
        else if (methode == "dcenter"){ methode_code = 4; }
        else if (methode == "dcenterv2"){ methode_code = 5; }
        else if (methode == "ccenter"){ methode_code = 6; }
        else {
            cout << "Methode de calcul invalide\n";
            return 0;
        }

        cout << DP.getSize() << endl;
        // cout << "Début solve DP" << endl;

        // Record start time Solver DP
        auto start_DP = chrono::high_resolution_clock::now();

        DP.solve(methode_code);
        DP.backtrack(methode_code);

        // Record end time Solver DP
        auto finish_DP = chrono::high_resolution_clock::now();
        
        // Compute execution time Solver1
        chrono::duration<double> elapsed_DP = finish_DP - start_DP;

        // Result Solver1
        float result_DP = DP.get_result(methode_code); 
        
        // Cout results Solver DP to CompletedProcess
        cout << elapsed_DP.count() << endl; // Temps d'exécution solver DP
        cout << result_DP << endl; // Cout solver DP

        // cout << "Début solve k-means" << endl;

        // Record start time Solver k-means
        auto start_km = chrono::high_resolution_clock::now();
        
        km.solve(methode_code);
        
        // Record end time Solver k-means
        auto finish_km = chrono::high_resolution_clock::now();

        // Compute execution time Solver k-means
        chrono::duration<double> elapsed_km = finish_km - start_km;
        
        // Result Solver k-means
        float result_km = km.get_result(methode_code);
        
        // Cout results Solver k-means to CompletedProcess
        cout << elapsed_km.count() << endl; // Temps d'exécution du solver k-means
        cout <<  result_km << endl; // Cout du solver k-means
        
        // cout << "Début solve k-means pareto" << endl;

        // Record start time Solver k-means pareto
        auto start_km_pareto = chrono::high_resolution_clock::now();
        
        km_pareto.solve(methode_code);
        
        // Record end time Solver k-means pareto
        auto finish_km_pareto = chrono::high_resolution_clock::now();

        // Compute execution time Solver k-means pareto
        chrono::duration<double> elapsed_km_pareto = finish_km_pareto - start_km_pareto;
        
        // Result Solver k-means pareto
        float result_km_pareto = km_pareto.get_result(methode_code);
        
        // Cout results Solver k-means pareto to CompletedProcess
        cout << elapsed_km_pareto.count() << endl; // Temps d'exécution du solver k-means pareto
        cout <<  result_km_pareto << endl; // Cout du solver k-means pareto
        

        // rtrim(filename);
        // filename = filename + "_result.txt";
        // km.write_result(filename);
    }
    
    return 0;
}
