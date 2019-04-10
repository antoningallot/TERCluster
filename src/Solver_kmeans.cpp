#include "Solver_kmeans.h"
#include <fstream>
#include<cmath>
#include<bits/stdc++.h> 

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

/*** FONCTIONS AUXILIAIRES POUR LA MANIPULATION ***/

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

void Solver_kmeans::write_result(string filename){
    ofstream file(filename.c_str());
    if(file.is_open()){
        for(int i = solution->size()-1; i >= 0; i--){
            file << (*solution)[i].first << " " << (*solution)[i].second << "\n";
        }
        file.close();
    }
}

/*** FONCTIONS DE CLUSTERING ***/

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
    float min = 1000.0;
    int value = 0;
    int center;
    float distance_cost;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        center = vect[i];
        distance_cost = 0;
        for(int j= 0; j < static_cast<int>(vect.size()); j++){
            distance_cost += pow(pareto->getPoint(center).distance(pareto->getPoint(vect[j])),2.0);
        }
        if(distance_cost<min){
            value = center;
            min = distance_cost;
        }
    }
    return pareto->getPoint(value);
}

Point Solver_kmeans::kmedian_center(vector<int> vect){
    float min = 1000.0;
    int value = 0;
    int center;
    float distance_cost;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        center = vect[i];
        distance_cost = 0;
        for(int j= 0; j < static_cast<int>(vect.size()); j++){
            distance_cost += pareto->getPoint(center).distance(pareto->getPoint(vect[j]));
        }
        if(distance_cost<min){
            value = center;
            min = distance_cost;
        }
    }
    return pareto->getPoint(value);
}

Point Solver_kmeans::discrete_kcenter(vector<int> vect){
    int extr1, extr2;
    float dist;
    int value = 0;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        for(int j= 0; i < static_cast<int>(vect.size()); i++){
            dist = pareto->getPoint(vect[i]).distance(pareto->getPoint(vect[j]));
            if(dist>value){
                value = dist;
                extr1 = i;
                extr2 = j;
            }
        }
    }
    int center = 0;
    float d1,d2;
    for(int i= 0; i < static_cast<int>(vect.size()); i++){
        d1 = pareto->getPoint(vect[i]).distance(pareto->getPoint(extr1));
        d2 = pareto->getPoint(vect[i]).distance(pareto->getPoint(extr2));
        if(d1>d2){
            if (d1<value){
                center = i;
                value = d1;
            }
        }
        else{
            if (d2<value){
                center = i;
                value = d2;
            }
        }
    }
    return pareto->getPoint(center);
}

void Solver_kmeans::solve(int methode){
    //Initialisation
    vector<Point> centroids(K);
    int M = 0;
    float new_epsilon = 0;
    float old_epsilon = FLT_MAX;
    pair<int, int> pair;
    for(int c=0; c<K;c++){centroids[c]= pareto->getPoint(rand()%N);}
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
        //Update
        for(int c=0;c<K;c++){
            centroids[c] = kmeans_center(cluster[c]);
        }
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
    for(int i = 0; i < (int)solution->size(); i++){
        result += pareto->cost_means((*solution)[i].first, (*solution)[i].second);
    }
    return result;
}

       //cout<<endl;

        // for(int i=0; i<static_cast<int>(cluster.size()); i++){
            // cout <<"[";
            // for(int j=0; j<static_cast<int>(cluster[i].size()); j++){
                // cout<< cluster[i][j] << " ";
            // }
            // cout << "]" << endl;
        // }
        // cout<<endl;
        //Solution
        // cout << M << " " << (new_epsilon-old_epsilon) << "\n";