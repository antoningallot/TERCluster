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

void Solver_kmeans_pareto::solve(int methode){
    //Initialisation
    vector<Point> centroids(K);
    int M = 0;
    float new_epsilon = 0;
    float old_epsilon = FLT_MAX;
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
                centre = int_precision( ((j+1)*((float)N/((float)K+1))+(j+2)*((float)N/((float)K+1)))/2 );
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
            for(int j=0;j<K;j++){
                int cpt = 1;
                //cout<<"Before : Min: "<<cluster[j].first<<" Max: "<<cluster[j].second<<endl;
                centre = cluster[j].second;
                if(pareto->getPoint(centre+1).distance(centroids[j]) < pareto->getPoint(centre+1).distance(centroids[j+1])){
                    centre = centre+1;
                    while(pareto->getPoint(centre+cpt).distance(centroids[j]) < pareto->getPoint(centre+cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second = centre+cpt;
                    cluster[j+1].first= centre+cpt+1;
                }
                else if(pareto->getPoint(centre).distance(centroids[j]) > pareto->getPoint(centre).distance(centroids[j+1])){
                    while(pareto->getPoint(centre-cpt).distance(centroids[j]) > pareto->getPoint(centre-cpt).distance(centroids[j+1])){
                        cpt += 1;
                    }
                    cluster[j].second=centre-cpt-1;
                    cluster[j+1].first=centre-cpt;
                }
                
                //cout<<"After : Min: "<<cluster[j].first<<" Max: "<<cluster[j].second<<endl;
            }
        }
        //Update
        //cout<<"Update"<<endl;
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

        display_vect_points_pareto(centroids);
        display_clusters(cluster);

        new_epsilon = 0;
        for(int c=0;c<static_cast<int>(cluster.size());c++){
            for(int j=cluster[c].first; j<=cluster[c].second;j++){
                new_epsilon += pareto->getPoint(j).distance(centroids[c]);
            }
        }
        if (M<10) { cout << new_epsilon-old_epsilon << endl; }
        //Solution
        if(M == maxinter){
           cout << "Iter\n";
            *solution = cluster;
        }
        if((abs(new_epsilon-old_epsilon)<=seuil)){
            cout << "Seuil\n";
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

/*****************************************************************************************************************
 * 
 * 
 * 
******************************************************************************************************************/
/*
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

void Solver_kmeans_pareto::solve(int methode){
    //Initialisation
    vector<Point> centroids(K);
    int M = 0;
    int new_epsilon = 0;
    int old_epsilon = INT_MAX;
    for(int c=0; c<K;c++){
        int x = int_precision((c+1)*((float)N/((float)K+1)));
        //cout<<"Centre: "<<x<<endl;
        centroids[c]= pareto->getPoint(x);
    }
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
                pair<int, int> pair = make_pair(min,max);
                solution->push_back(pair);
            }
        }
        

    }
}*/