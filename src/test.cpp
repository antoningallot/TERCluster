#include <vector>
#include <chrono>
#include "Solver.h"
#include "Solver_kmeans.h"
#include <experimental/filesystem>
 
using namespace std;

// trim from end (in place)
void rtrim(string &s) {
    s.erase(s.size()-4, 4);
    // return s;
}

vector<string> get_filenames(experimental::filesystem::path path){
    namespace stdfs = experimental::filesystem ;

    vector<string> filenames ;
    
    const stdfs::directory_iterator end{} ;
    
    for( stdfs::directory_iterator iter{path} ; iter != end ; ++iter )
    {
        if( is_regular_file(*iter) ) // comment out if all names (names of directories tc.) are required
            filenames.push_back( iter->path().string() ) ;
    }

    return filenames;
}


int main (int argc, char *argv[]) {
    std::string dir = "../dataAlea/";
    vector<string> files = get_filenames(dir);
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    std::string methode = argv[3];
    std::string filename = argv[4];
    float seuil = (float) atoi(argv[5]);
    int maxiter = atoi(argv[6]);

    double time_DP = 0.0;
    double time_lloyd;
    float cost = 0.0;

    for(std::string f : files){
        Solver s(n, k, dir+f);
        Solver_kmeans km(n, k, dir+f, seuil, maxiter);

        // Record start time
        auto start_DP = std::chrono::high_resolution_clock::now();
        s.solve(1);
        s.backtrack(1);
        // Record end time
        auto finish_DP = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_DP = finish_DP - start_DP;

        float result_DP = s.get_result(); 
        std::cout << "Temps d'exécution de DP pour " << f << " : " << elapsed_DP.count() << endl;
        std::cout << "Cout de DP pour " << f << " : " << result_DP << endl;

        // Record start time
        auto start_lloyd = std::chrono::high_resolution_clock::now();
        km.K_means();
        auto finish_lloyd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_lloyd = finish_lloyd - start_lloyd;
        
        float result_lloyd = km.compute_result();
        
        std::cout << "Temps d'exécution de Lloyd pour " << f << " : " << elapsed_lloyd.count() << endl;
        std::cout << "Cout de Lloyd pour " << f << " : " << result_lloyd << endl;
        
        std::cout << "Gap Lloyd/DP pour " << f << " : " << result_lloyd - result_DP << endl;

        time_DP += elapsed_DP.count();
        time_lloyd += elapsed_lloyd.count();
        cost += result_lloyd - result_DP;
    }

    // cout << "Temps d'exécution moyen pour "
    return 0;
}

/*
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
        cout << "Debut constructeur\n";
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

        float result_DP = s.get_result(); 
        cout << "Temps d'exécution de DP : " << elapsed_DP.count() << endl;
        cout << "Cout de DP : " << result_DP << endl;

        // Record start time
        auto start_lloyd = chrono::high_resolution_clock::now();
        km.K_means();
        auto finish_lloyd = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_lloyd = finish_lloyd - start_lloyd;
        
        cout << "Lloyd fini\n";
        float result_lloyd = km.compute_result();
        
        cout << "Temps d'exécution de Lloyd : " << elapsed_lloyd.count() << endl;
        cout << "Cout de Lloyd : " << result_lloyd << endl;
        
        cout << "Gap Lloyd/DP : " << result_lloyd - result_DP << endl;
        // rtrim(filename);
        // filename = filename + "_result.txt";
        // km.write_result(filename);
    }
    
    return 0;
}*/
