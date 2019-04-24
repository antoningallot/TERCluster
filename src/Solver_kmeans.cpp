#include "Solver_kmeans.h"
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

//Construction de la classe Solver_kmeans
Solver_kmeans::Solver_kmeans(int n, int k, string filename, float s, int m){
    Solver_parent(n, k, filename);
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    solution = new vector<pair<int, int> >();
    seuil = s;
    maxinter = m;
}

/*** FONCTIONS AUXILIAIRES D'AFFICHAGES POUR LE DEBUG ***/

void Solver_kmeans::displayCluster(vector<vector<int> > vect){
    for(int i=0; i<static_cast<int>(vect.size()); i++){
        cout <<"[";
        for(int j=0; j<static_cast<int>(vect[i].size()); j++){
            cout<< vect[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void display_vect(vector<int> v){
    for (int i = 0; i < (int)v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

void display_vect_points(vector<Point> v){
    for (int i = 0; i < (int)v.size(); i++){
        v[i].display();
    }
    cout << "\n";
}

void display_points(vector<Point> v){
    for (int i = 0; i < (int)v.size(); i++){
        v[i].display();
        cout << " ";
    }
    cout << "\n";
}

void display_clusters(vector<vector<int> > v){
    for (int i = 0; i < (int)v.size(); i++){
        for (int j = 0; j < (int)v[i].size(); j++){
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
}




/*** FONCTIONS DE CLUSTERING ***/

bool Solver_kmeans::belongs(Point p, vector<Point> v){
    for (int i = 0; i < (int)v.size(); i++){
        if(p.equals(v[i])){
            return true;
        }
    }
    return false;
}

Point Solver_kmeans::kmeans_center(vector<int> vect){
    Point p(0,0);
    float cpt = 0.0;
    for(int j= 0; j < static_cast<int>(vect.size()); j++){
        p.addPoint(pareto->getPoint(vect[j]));
        cpt ++;
    }
    p.multInt(1.0/cpt);
    return p;
}

Point Solver_kmeans::kmedoids_center(vector<int> vect){
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

Point Solver_kmeans::kmedian_center(vector<int> vect){
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

Point Solver_kmeans::dcenter(vector<int> vect){
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

Point Solver_kmeans::ccenter(vector<int> vect){
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

void Solver_kmeans::solve(int methode){
    //Initialisation   
    srand (time(NULL));
    vector<Point> centroids(K);
    int M = 0;
    float new_epsilon = 0;
    float old_epsilon = FLT_MAX;
    pair<int, int> pair;
    for(int c=0; c<K;c++){
        Point centre = pareto->getPoint(rand()%N);
        while (belongs(centre, centroids)){
            centre = pareto->getPoint(rand()%N);
        }
        centroids[c] = centre;
    }
    // display_vect_points_pareto(centroids);
    //Assignation
    while(maxinter>M && (abs(new_epsilon-old_epsilon)>seuil)){
        old_epsilon = new_epsilon;
        M += 1;
        vector<vector<int> > cluster(K, vector<int>());
        for(int j=0; j<N; j++){
            float dist = 0;
            float dist_min = FLT_MAX;
            int min = -1;
            for(int I=0; I<K; I++){
                dist = pareto->getPoint(j).distance(centroids[I]);
                if(dist<dist_min){
                    min = I;
                    dist_min = dist;
                }
            }
            cluster[min].push_back(j);
        }
        // if (M==1){ display_clusters(cluster);}
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
                    centroids[c] = dcenter(cluster[c]);
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

        // display_vect_points(centroids);
        // display_clusters(cluster);

        new_epsilon = 0;
        for(int c=0;c<K;c++){
            for(int j=0; j<static_cast<int>(cluster[c].size());j++){
                new_epsilon += pareto->getPoint(j).distance(centroids[c]);
            }
        }


        if(maxinter==M || (abs(new_epsilon-old_epsilon)<=seuil)){
            for(int I=0; I<K;I++){
                int max = -1;
                int min = N+1;
                for(int j=0; j<static_cast<int>(cluster[I].size());j++){
                    if(min>cluster[I][j]){min = cluster[I][j];}
                    if(max<cluster[I][j]){max = cluster[I][j];}
                }
                pair = make_pair(min,max);
                solution->push_back(pair);
            }
        }
        
    }
}

float Solver_kmeans::get_result(int methode){
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