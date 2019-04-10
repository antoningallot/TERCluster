#include "Solver_kmeans_pareto.h"
#include<bits/stdc++.h> 

using namespace std;

//Construction de la classe Solver_kmeans_pareto
Solver_kmeans_pareto::Solver_kmeans_pareto(int n, int k, string filename, float s, int m){
    Solver_parent(n, k, filename);
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    solution = new vector<pair<int, int> >();
    seuil = s;
    maxinter = m;
}

void Solver_kmeans_pareto::write_result(string filename){
    ofstream file(filename.c_str());
    if(file.is_open()){
        for(int i = solution->size()-1; i >= 0; i--){
            file << (*solution)[i].first << " " << (*solution)[i].second << "\n";
        }
        file.close();
    }
}

Point Solver_kmeans_pareto::cost_means(pair<int,int> pair){
    Point p(0,0);
    float cpt = 0.0;
    for(int j= pair.first; j<= pair.second; j++){
        p.addPoint(pareto->getPoint(j));
        cpt ++;
    }
    p.multInt(1.0/cpt);
    return p;
}

int int_precision (float f){
    int x = (int) f;
    if(f>=(float) x +0.5){
            x += 1;
    }
    return x;
}

float Solver_kmeans_pareto::get_result(int methode){
    // TODO
}

void Solver_kmeans_pareto::solver(){
    //Initialisation
    vector<Point> centroids(K);
    int M = 0;
    int new_epsilon = 0;
    int old_epsilon = INT_MAX;
    vector<pair<int, int> > cluster (K);
    for(int c=0; c<K;c++){
        int x = int_precision((c+1)*((float)N/((float)K+1)));
        centroids[c]= pareto->getPoint(x);
    }
    //Assignation
    while(maxinter>M && (abs(new_epsilon-old_epsilon)>seuil)){
        old_epsilon = new_epsilon;
        M += 1;
        if(M==1){
            int min = 0;
            int max = 0;
            int centre = 0;
            int cpt = 1;
            for(int j=0;j<K-1;j++){
                centre = int_precision((j+1)*((float)N/((float)K+1))*(3.0/2.0));
                if(pareto->getPoint(centre).distance(centroids[j]) < pareto->getPoint(centre).distance(centroids[j+1])){
                    while(pareto->getPoint(centre+cpt).distance(centroids[j]) < pareto->getPoint(centre+cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    max = centre+cpt-1;
                    pair<int, int> pair;
                    pair = make_pair(min,max);
                    cluster[j] =pair;
                    min = centre+cpt;
                }
                else{
                    while(pareto->getPoint(centre-cpt).distance(centroids[j]) > pareto->getPoint(centre-cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    max = centre-cpt;
                    pair<int, int> pair;
                    pair = make_pair(min,max);
                    cluster[j] =pair;
                    min = centre-cpt+1;
                }
                cpt = 1;
            }
            pair<int, int> pair;
            pair = make_pair(min,N-1);
            cluster[K-1] =pair;
        }
        else{
            int centre = 0;
            int cpt = 1;
            for(int j=0;j<K;j++){
                centre = cluster[j].second;
                if(pareto->getPoint(centre).distance(centroids[j]) > pareto->getPoint(centre).distance(centroids[j+1])){
                    while(pareto->getPoint(centre+cpt).distance(centroids[j]) > pareto->getPoint(centre+cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second=centre+cpt-1;
                    cluster[j+1].first=centre+cpt;
                }
                else if(pareto->getPoint(centre+1).distance(centroids[j]) < pareto->getPoint(centre+1).distance(centroids[j+1])){
                    centre = centre+1;
                    while(pareto->getPoint(centre-cpt).distance(centroids[j]) < pareto->getPoint(centre-cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second = centre-cpt;
                    cluster[j+1].first= centre-cpt+1;
                }
                cpt = 1;
            }
        }
        //Update
        for(int c=0;c<K;c++){
            centroids[c] = cost_means(cluster[c]);
        }
        new_epsilon = 0;
        for(int c=0;c<static_cast<int>(cluster.size());c++){
            for(int j=cluster[c].first; j<=cluster[c].second;j++){
                new_epsilon += pareto->getPoint(j).distance(centroids[c]);
            }
        }
        //Solution
        if(maxinter==M || (abs(new_epsilon-old_epsilon)<=seuil)){
            *solution = cluster;
        }
    }
}