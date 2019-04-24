#include <vector>
#include <chrono>
#include "Solver.h"
#include "Solver_kmeans.h"
#include "Solver_kmeans_pareto.h"
#include <experimental/filesystem>
 
using namespace std;

// trim from end (in place)
void rtrim(string &s) {
    s.erase(s.size()-4, 4);
    // return s;
}


int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    string filename = argv[3];
    string methode = argv[4];
    float seuil = (float) atoi(argv[5]);
    int maxiter = atoi(argv[6]);
    int methode_code = 0;
    if (methode == "median"){ methode_code = 1; }
    else if (methode == "means"){ methode_code = 2; }
    else if (methode == "medoids"){ methode_code = 3; }
    else if (methode == "dcenter"){ methode_code = 4; }
    else if (methode == "dcenterv2"){ methode_code = 5; }
    else if (methode == "ccenter"){ methode_code = 6; }
    else {
        cout<<"Erreur Methode:  Non assigné"<<endl;
    }
    Solver DP(n, k, filename);
    Solver_kmeans km(n, k, filename, seuil, maxiter);
    Solver_kmeans_pareto km_pareto(n, k, filename, seuil, maxiter);
    cout << "Contructeur fini\n";
    //s.displayPareto();
    DP.solve(methode_code);
    DP.backtrack(methode_code);
    km.solve(methode_code);
    cout << "Solve normal fini\n";
    km_pareto.solve(methode_code);
    cout << "Solve pareto fini\n";
    //sp.displayMatrix();
    //s.backtrack(methode_code);
    cout << "Backtrack fini\n";
    // km.displaySolution();
    // km_pareto.displaySolution();
    // cout << sp.get_result(methode_code) << endl;
    // rtrim(filename);
    // filename = filename + "_result.txt";
    // km.write_result(filename);
    
}
