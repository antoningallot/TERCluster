#include <iostream>
#include <Solver_Kmeans.h>

//Construction de la classe Solver_kmeans
Solver_Kmeans::Solver_Kmeans(int n, int k, string filename, float s, int m){
    Solver_parent(n, k, filename);
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    solution = new vector<int>();
    seuil = s;
    maxinter = m;
}
    
Solver_Kmeans::K_means(int i, int k){
    //Initialisation
    float N = (float) i;
    int div = static_cast<int>(N/k);
    int centroids[k];
    for(int j=div; j<i-div;j= j+div){centroids->push_back(j);}
    int M = 0;
    int new_epsilon = INT_MAX;
    int old_espilon = 0;

    //Assignation
    while(maxinter>M && (abs(new_epsilon-old_epsilon)>seuil){
        old_epsilon = new_epsilon;
        m += 1;

    }
}