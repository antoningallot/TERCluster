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

/*** FONCTIONS DE CLUSTERING ***/

Point Solver_kmeans_pareto::kmeans_center(vector<int> vect){
    Point p(0,0);
    float cpt = 0.0;
    for(int j= 0; j < static_cast<int>(vect.size()); j++){
        p.addPoint(pareto->getPoint(vect[j]));
        cpt ++;
    }
    p.multInt(1.0/cpt);
    return p;
}

Point Solver_kmeans_pareto::kmedoids_center(vector<int> vect){
    float min = FLT_MAX;
    int value = 0;
    int center;
    float distance_cost;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        center = vect[i];
        distance_cost = 0;
        for(int j= 0; j < static_cast<int>(vect.size()); j++){
            distance_cost += pow(pareto->getPoint(center).distance(pareto->getPoint(vect[j])),2.0);
        }
        if(distance_cost<=min){
            value = center;
            min = distance_cost;
        }
    }
    return pareto->getPoint(value);
}

Point Solver_kmeans_pareto::kmedian_center(vector<int> vect){
    float min = FLT_MAX;
    int value = 0;
    int center = 0;
    float distance_cost = 0.0;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        center = vect[i];
        distance_cost = 0;
        for(int j= 0; j < static_cast<int>(vect.size()); j++){
            distance_cost += pareto->getPoint(center).distance(pareto->getPoint(vect[j]));
        }
        if(distance_cost<=min){
            value = center;
            min = distance_cost;
        }
    }
    return pareto->getPoint(value);
}

Point Solver_kmeans_pareto::dcenter(vector<int> vect){
    int extr1, extr2;
    float dist;
    int max = 0;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        for(int j= 0; i < static_cast<int>(vect.size()); i++){
            dist = pareto->getPoint(vect[i]).distance(pareto->getPoint(vect[j]));
            if(dist>= max){max = dist;extr1 = i;extr2 = j;}
        }
    }
    int center = -1;
    float d1, d2;
    float min = FLT_MAX;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        d1 = pareto->getPoint(vect[i]).distance(pareto->getPoint(vect[extr1]));
        d2 = pareto->getPoint(vect[i]).distance(pareto->getPoint(vect[extr2]));
        if(d1>d2){
            if (d1<=min){center = vect[i];min = d1;}
        }
        else{
            if (d2<=min){center = vect[i];min = d2;}
        }
    }
    return pareto->getPoint(center);
}

Point Solver_kmeans_pareto::ccenter(vector<int> vect){
    int extr1, extr2;
    float dist;
    int value = 0;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        for(int j= 0; i < static_cast<int>(vect.size()); i++){
            dist = pareto->getPoint(vect[i]).distance(pareto->getPoint(vect[j]));
            if(dist>= value){value = dist;extr1 = i;extr2 = j;}
        }
    }
    Point p(0,0);
    p.addPoint(pareto->getPoint(vect[extr1]));
    p.addPoint(pareto->getPoint(vect[extr2]));
    p.multInt(1.0/2.0);
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

void Solver_kmeans_pareto::solve(int methode){
    //Initialisation
    vector<Point> centroids(K);
    int M = 0;
    int new_epsilon = 0;
    int old_epsilon = INT_MAX;
    vector<pair<int, int> > cluster (K);
    for(int c=0; c<K;c++){
        int x = int_precision((c+1)*((float)N/((float)K+1)));
        //cout<<"Centre: "<<x<<endl;
        centroids[c]= pareto->getPoint(x);
    }
    //Assignation
    //cout<<"Assignation"<<endl;
    while(maxinter>M && (abs(new_epsilon-old_epsilon)>seuil)){
        old_epsilon = new_epsilon;
        M += 1;
        if(M==1){
            int min = 0;
            int max = 0;
            int centre = 0;
            int cpt = 1;
            for(int j=0;j<K-1;j++){
                centre = int_precision(((j+1)*((float)N/((float)K+1))+(j+2)*((float)N/((float)K+1)))/2);
                //cout<<"Centre: "<<centre<<endl;
                if(pareto->getPoint(centre).distance(centroids[j]) < pareto->getPoint(centre).distance(centroids[j+1])){
                    while(pareto->getPoint(centre+cpt).distance(centroids[j]) < pareto->getPoint(centre+cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    max = centre+cpt-1;
                    pair<int, int> pair;
                    pair = make_pair(min,max);
                    //cout<<"Min: "<<min<<" Max: "<<max<<endl;
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
                    //cout<<"Min: "<<min<<" Max: "<<max<<endl;
                    cluster[j] =pair;
                    min = centre-cpt+1;
                }
                cpt = 1;
                
            }
            pair<int, int> pair;
            pair = make_pair(min,N-1);
            cluster[K-1] =pair;
            //cout<<"Min: "<<min<<" Max: "<<N-1<<endl;

        }
        else{
            int centre = 0;
            int cpt = 1;
            for(int j=0;j<K;j++){
                //cout<<"Before : Min: "<<cluster[j].first<<" Max: "<<cluster[j].second<<endl;
                centre = cluster[j].second;
                if(pareto->getPoint(centre).distance(centroids[j]) > pareto->getPoint(centre).distance(centroids[j+1])){
                    while(pareto->getPoint(centre-cpt).distance(centroids[j]) > pareto->getPoint(centre-cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second=centre-cpt-1;
                    cluster[j+1].first=centre-cpt;
                }
                else if(pareto->getPoint(centre+1).distance(centroids[j]) < pareto->getPoint(centre+1).distance(centroids[j+1])){
                    centre = centre+1;
                    while(pareto->getPoint(centre+cpt).distance(centroids[j]) < pareto->getPoint(centre+cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second = centre+cpt;
                    cluster[j+1].first= centre+cpt+1;
                }
                //cout<<"After : Min: "<<cluster[j].first<<" Max: "<<cluster[j].second<<endl;
                cpt = 1;
            }
        }
        //Update
        //cout<<"Update"<<endl;
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