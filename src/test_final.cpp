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
    if(argc != 9){
        cout << "Need 9 arguments\n";
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
        int solver1 = atoi(argv[7]); // Type du premier solver
        int solver2 = atoi(argv[8]); // Type du deuxième solver
        
        switch (solver1)
        {
            case 1:
            Solver s1(n, k, filename);
            break;

            case 2:
            Solver_kmeans s1(n, k, filename, seuil, maxiter);
            break;

            case 3:
            Solver_kmeans_pareto s1(n, k, filename, seuil, maxiter);
            break;
        }

        switch (solver2)
        {
            case 1:
            Solver s2(n, k, filename);
            break;

            case 2:
            Solver_kmeans s2(n, k, filename, seuil, maxiter);
            break;

            case 3:
            Solver_kmeans_pareto s2(n, k, filename, seuil, maxiter);
            break;
        }
        
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

        // Record start time Solver1
        auto start_solver1 = chrono::high_resolution_clock::now();

        s1.solve(methode_code);
        if (solver1 == 1){ s1.backtrack(methode_code); }

        // Record end time Solver1
        auto finish_solver1 = chrono::high_resolution_clock::now();
        
        // Compute execution time Solver1
        chrono::duration<double> elapsed_solver1 = finish_solver1 - start_solver1;

        // Result Solver1
        float result_solver1 = s1.get_result(); 
        
        // Cout results Solver1 to CompletedProcess
        cout << elapsed_solver1.count() << endl; // Temps d'exécution du solver1
        cout << result_solver1 << endl; // Cout du solver1

        // Record start time Solver2
        auto start_solver2 = chrono::high_resolution_clock::now();
        
        s2.solve();
        if (solver2 == 1){ s2.backtrack(methode_code); }
        
        // Record end time Solver2
        auto finish_solver2 = chrono::high_resolution_clock::now();

        // Compute execution time Solver2
        chrono::duration<double> elapsed_lloyd = finish_solver2 - start_solver2;
        
        // Result Solver2
        float result_solver2 = s2.get_result();
        
        // Cout results Solver1 to CompletedProcess
        cout << elapsed_solver2.count() << endl; // Temps d'exécution du solver2
        cout <<  result_solver2 << endl; // Cout du solver2
        
        // rtrim(filename);
        // filename = filename + "_result.txt";
        // km.write_result(filename);
    }
    
    return 0;
}
