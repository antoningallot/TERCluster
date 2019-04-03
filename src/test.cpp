#include <vector>
#include "Solver.h"
#include "Solver_kmeans.h"

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
        int n = atoi(argv[1]);
        int k = atoi(argv[2]);
        string methode = argv[3];
        string filename = argv[4];
        float seuil = (float) atoi(argv[5]);
        int maxiter = atoi(argv[6]);
        // cout << n << " " << k << " " << filename << " " << methode << "\n";
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
        // s.solve(methode_code);
        // s.backtrack(methode_code);
        // s.displaySolution();
        //km.displayPareto();
        km.K_means();
        km.displaySolution();
        // cout << km.getSolution().size() << endl;
        rtrim(filename);
        filename = filename + "_result.txt";
        km.write_result(filename);
    }
    
    return 0;
}
