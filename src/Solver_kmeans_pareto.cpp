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

/*** QUELQUES FONCTIONS AUXILIAIRES D'AFFICHAGE POUR LE DEBUG ***/

void display_vect_points_pareto(vector<Point> v){
    for (int i = 0; i < (int)v.size(); i++){
        v[i].display();
    }
    cout << "\n";
}

void display_clusters(vector< pair<int, int> > v){
    for (int i = 0; i < (int)v.size(); i++){
        cout << v[i].first << " " << v[i].second << endl;
    }
    cout << "\n";
}

/*** FONCTIONS DE CLUSTERING ***/

Point Solver_kmeans_pareto::kmeans_center(pair<int,int> pair){
    Point p(0,0);
    float cpt = 0.0;
    for(int j= pair.first; j<= pair.second; j++){
        p.addPoint(pareto->getPoint(j));
        cpt ++;
    }
    p.multInt(1.0/cpt);
    return p;
}

Point Solver_kmeans_pareto::kmedoids_center(pair<int,int> pair){
    float min = FLT_MAX;
    int value = 0;
    int center;
    float distance_cost;
    for(int i= pair.first; i < pair.second; i++){
        center = i;
        distance_cost = 0;
        for(int j= pair.first; j < pair.second; j++){
            distance_cost += pow(pareto->getPoint(center).distance(pareto->getPoint(j)),2.0);
        }
        if(distance_cost<=min){
            value = center;
            min = distance_cost;
        }
    }
    return pareto->getPoint(value);
}

Point Solver_kmeans_pareto::kmedian_center(pair<int,int> pair){
    float min = FLT_MAX;
    int value = 0;
    int center = 0;
    float distance_cost = 0.0;
    for(int i= pair.first; i < pair.second; i++){
        center = i;
        distance_cost = 0;
        for(int j= pair.first; j < pair.second; j++){
            distance_cost += pareto->getPoint(center).distance(pareto->getPoint(j));
        }
        if(distance_cost<=min){
            value = center;
            min = distance_cost;
        }
    }
    return pareto->getPoint(value);
}

Point Solver_kmeans_pareto::dcenter(pair<int,int> pair){
    int center = -1;
    float d;
    float min = FLT_MAX;
    for(int i= pair.first; i < pair.second; i++){
        if(pareto->getPoint(i).distance(pareto->getPoint(pair.first))<pareto->getPoint(i).distance(pareto->getPoint(pair.second))){
            d=pareto->getPoint(i).distance(pareto->getPoint(pair.second));
        }
        else{
            d=pareto->getPoint(i).distance(pareto->getPoint(pair.first));
        }
        if(d<=min){center = i;min = d;}
    }
    return pareto->getPoint(center);
}

Point Solver_kmeans_pareto::dcenterv2(pair<int,int> pair){
    int center = -1;
    float d;
    float min = FLT_MAX;
    for(int i= pair.first; i < pair.second; i++){
        if(pareto->getPoint(i).distance(pareto->getPoint(pair.first))<pareto->getPoint(i).distance(pareto->getPoint(pair.second))){
            d=pareto->getPoint(i).distance(pareto->getPoint(pair.second));
        }
        else{
            d=pareto->getPoint(i).distance(pareto->getPoint(pair.first));
        }
        if(d<=min){center = i;min = d;}
        else{return pareto->getPoint(center);}
    }
    return pareto->getPoint(center);
}

Point Solver_kmeans_pareto::ccenter(pair<int,int> pair){
    Point p(0,0);
    p.addPoint(pareto->getPoint(pair.first));
    p.addPoint(pareto->getPoint(pair.second));
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


void Solver_kmeans_pareto::solve(int methode){
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
            
            for(int j=0;j<K-1;j++){
                int cpt = 1;
                centre = int_precision(((j+1)*((float)N/((float)K+1))+(j+2)*((float)N/((float)K+1)))/2);
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
                
            }
            pair<int, int> pair;
            pair = make_pair(min,N-1);
            cluster[K-1] =pair;

        }
        else{
            int centre = 0;
            for(int j=0;j<K;j++){
                int cpt = 1;
                centre = cluster[j].second;
                if(pareto->getPoint(centre+1).distance(centroids[j]) < pareto->getPoint(centre+1).distance(centroids[j+1])){
                    centre = centre+1;
                    while(pareto->getPoint(centre+cpt).distance(centroids[j]) < pareto->getPoint(centre+cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second = centre+cpt-1;
                    cluster[j+1].first= centre+cpt;
                }
                else if(pareto->getPoint(centre).distance(centroids[j]) > pareto->getPoint(centre).distance(centroids[j+1])){
                    while(pareto->getPoint(centre-cpt).distance(centroids[j]) > pareto->getPoint(centre-cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second=centre-cpt;
                    cluster[j+1].first=centre-cpt+1;
                }
            }
        }

        //Update
        switch (methode){
            case 1:
                for(int c=0;c<K;c++){
                    centroids[c] = kmedian_center(cluster[c]);
                }    
                break;
            case 2:
                for(int c=0;c<K;c++){
                    centroids[c] = kmeans_center(cluster[c]);
                }
                break;
            case 3:
                for(int c=0;c<K;c++){
                    centroids[c] = kmedoids_center(cluster[c]);
                }
                break;
            case 4:
                for(int c=0;c<K;c++){
                    centroids[c] = dcenter(cluster[c]);
                }
                break;
            case 5:
                for(int c=0;c<K;c++){
                    centroids[c] = dcenterv2(cluster[c]);
                }
                break;
            case 6:
            for(int c=0;c<K;c++){
                centroids[c] = ccenter(cluster[c]);
            }
            break;
            default:
                break;
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

float Solver_kmeans_pareto::get_result(int methode){
    float result = 0.0;
    switch (methode) {
        case 1:  
            for(int i = 0; i < (int)solution->size(); i++){ 
                result += pareto->cost_median((*solution)[i].first, (*solution)[i].second);
            }
            break;
         case 2:  
            for(int i = 0; i < (int)solution->size(); i++){ 
                result += pareto->cost_means((*solution)[i].first, (*solution)[i].second);
            }
            break;
         case 3:  
            for(int i = 0; i < (int)solution->size(); i++){ 
                result += pareto->cost_medoids((*solution)[i].first, (*solution)[i].second);
            }
            break;
         case 4:  
            for(int i = 0; i < (int)solution->size(); i++){ 
                result += pareto->cost_dcenter((*solution)[i].first, (*solution)[i].second);
            }
            break;
         case 6:  
            for(int i = 0; i < (int)solution->size(); i++){ 
                result += pareto->cost_ccenter((*solution)[i].first, (*solution)[i].second);
            }
            break;
    
        default:
            break;
    }
    return result;
}