#include <vector>
#include "Solver.h"

using namespace std;

int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    string filename = argv[3];
    cout << n << " " << k << " " << filename << "\n";
    Solver s(n, k, filename);
    cout << "Contructeur fini\n";
    
    //s.fillArray();
    s.DP();
    s.displayMatrix();
    cout << "C'est là que ça plante ?\n";
    s.backtrack();
    //s.displayMatrix();
    s.displaySolution();

    return 0;
}
