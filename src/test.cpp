#include <vector>
#include "Solver.h"

using namespace std;

// trim from end (in place)
void rtrim(string &s) {
    s.erase(s.size()-4, 4);
    // return s;
}

int main (int argc, char *argv[]) {
    if(argc != 5){
        cout << "Need 4 arguments\n";
    }
    else {
        int n = atoi(argv[1]);
        int k = atoi(argv[2]);
        string methode = argv[3];
        string filename = argv[4];
        // cout << n << " " << k << " " << filename << " " << methode << "\n";
        Solver s(n, k, filename);
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
        //s.fillArray();
        s.solve(methode_code);
        // s.displayMatrix();
        s.backtrack(methode_code);
        //s.displayMatrix();
        s.displaySolution();
        rtrim(filename);
        filename = filename + "_result.txt";
        s.write_result(filename);
    }

    return 0;
}
