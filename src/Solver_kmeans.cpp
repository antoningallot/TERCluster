#include "Solver_kmeans.h"
#include <fstream>
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

Point Solver_kmeans::cost_means(vector<int> vect){
    Point p(0,0);
    float cpt = 0.0;
    for(int j= 0; j < static_cast<int>(vect.size()); j++){
        p.addPoint(pareto->getPoint(vect[j]));
        cpt ++;
    }
    p.multInt(1.0/cpt);
    // cout<<"Fini"<<endl;
    return p;
}

void Solver_kmeans::K_means(){
    //Initialisation
    vector<Point> centroids(K);
    int M = 0;
    float new_epsilon = 0;
    float old_epsilon = FLT_MAX;
    pair<int, int> pair;
    for(int c=0; c<K;c++){centroids[c]= pareto->getPoint(rand()%N);}
    while(maxinter>M && (abs(new_epsilon-old_epsilon)>seuil)){
        old_epsilon = new_epsilon;
        M += 1;
        vector<vector<int> > cluster(K, vector<int>());
        // cout << "Assignation\n";
        //Assignation
        for(int j=0; j<N; j++){
            float dist = 0;
            float dist_min = FLT_MAX;
            int min = -1;
            for(int I=0; I<K; I++){
                dist = pareto->getPoint(j).distance(centroids[I]);
                // cout << "Dist : " << dist << "\n";
                if(dist<dist_min){
                    min = I;
                    dist_min = dist;
                }
            }
            cluster[min].push_back(j);
        }
        // display_clusters(cluster);
        // cout << "Update\n";
        //Update
        for(int c=0;c<K;c++){
            // display_vect(cluster[c]);
            centroids[c] = cost_means(cluster[c]);
        }
        // display_points(centroids);
        // cout << "Limit\n";
        
        //Limit
        new_epsilon = 0;
        for(int c=0;c<K;c++){
            for(int j=0; j<static_cast<int>(cluster[c].size());j++){
                new_epsilon += pareto->getPoint(j).distance(centroids[c]);
            }
        }
        //cout<<endl;

        // for(int i=0; i<static_cast<int>(cluster.size()); i++){
        //     cout <<"[";
        //     for(int j=0; j<static_cast<int>(cluster[i].size()); j++){
        //         cout<< cluster[i][j] << " ";
        //     }
        //     cout << "]" << endl;
        // }
        // cout<<endl;

        // cout << "Solution\n";
        
        //Solution
        // cout << M << " " << (new_epsilon-old_epsilon) << "\n";
        if(maxinter<=M || (abs(new_epsilon-old_epsilon)<seuil)){
            for(int I=0; I<K;I++){
                int max = -1;
                int min = N+1;
                for(int j=0; j<static_cast<int>(cluster[I].size());j++){
                    // cout << i << " " << j << "\n";
                    if(min>cluster[I][j]){min = cluster[I][j];}
                    if(max<cluster[I][j]){max = cluster[I][j];}
                }
                pair = make_pair(min,max);
                solution->push_back(pair);
            }
        }
        

    }
}

