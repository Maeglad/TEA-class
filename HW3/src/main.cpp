/* 
 * File:   main.cpp
 * Author: Maeglad
 *
 * Created on April 14, 2016, 4:12 PM
 */

#define MAX_COST 2147483647
#define MAX_VERTICES 4000


#include <cstdlib>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
using namespace std;



/*
 * 
 */


void dijkstra();
void FloydWarshall();

int main(int argc, char** argv) {
    
    //dijkstra();
    FloydWarshall();
    return 0;
}

struct cost{
    int safe, unsafe;
    inline bool operator<(struct cost c){
        if(unsafe < c.unsafe) return true;
        if(unsafe > c.unsafe) return false;
        if(safe < c.safe) return true;
        return false;
    }
    
    inline cost operator+(struct cost c){
        cost n;
        n.safe = safe + c.safe;
        n.unsafe = unsafe + c.unsafe;
        return n;
    }
};

struct edge{
    int to;
    cost costs;
};

struct CostComparator {
    bool operator() (pair<cost, int> left, pair<cost, int> right){
        return right.first < left.first;
    }
};

struct node{
    vector<edge> neighs;
};

/**
 * dijktra implementation for problem
 * since dijkstra algorithm doesnt have to compute all 
 * pairs its a lot faster if query count is low dijkstra is better
 * then Floyd-Warshall algorithm
 */
void dijkstra(){
    pair<int, int>pp;
    int vrcholy, cesty, otazky;
    cin >> vrcholy >> cesty >> otazky;
    vrcholy = 4000;
    cost dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    
    vector<node> nodes;
    for(int i = 0; i < vrcholy; ++i){
        node n;
        n.neighs.clear();
        nodes.push_back(n);
    }
   
    
    for(int i = 0; i < cesty; ++i){
        int a, b, costs;
        char safe;
        cin >> a >> b >> costs >> safe;
        edge c;
        if(safe == 'B'){
            c.costs.safe = costs;
            c.costs.unsafe = 0;          
        }
        else{
            c.costs.safe = 0;
            c.costs.unsafe = costs;
        }
        c.to = b;
        nodes[a].neighs.push_back(c);
        c.to = a;
        nodes[b].neighs.push_back(c);
        
    }
    
    for(int i = 0; i < otazky; ++i){
        int a, b;
        cin >> a >> b;
        for(int i = 0; i < vrcholy; ++i){
            dist[i].safe = MAX_COST;
            dist[i].unsafe = MAX_COST;
            visited[i] = false;
        }
        
        dist[a].safe = 0;
        dist[a].unsafe = 0;
        
        priority_queue< pair<cost, int>, vector< pair<cost, int> >, CostComparator > queue;
        cost d;
        d.safe = 0;
        d.unsafe = 0;
        
        while(!queue.empty()){
            queue.pop();
        }
        pair<cost, int> s;
        s.first = d; s.second = a;
        queue.push( s );
        while(!queue.empty()){
            int id = queue.top().second;
            visited[id] = true;
            if(id == b)break;
            queue.pop();
            for(int j = 0; j < nodes[id].neighs.size(); ++j){
                edge e = nodes[id].neighs[j];
                cost c = dist[id] + e.costs;
                
                if(c < dist[e.to]){
                    
                    dist[e.to] = c;
                    queue.push(pair<cost, int>(c, e.to));
                }
            }
            
        }
        if(visited[b] == false){cout << "-1 -1" << endl;}
        else cout << dist[b].unsafe << " " << dist[b].safe + dist[b].unsafe << endl;
        
    }
}

struct FWCost{
    int safe, unsafe;
    bool visited, set;
    
    inline bool operator<(struct FWCost c){
        if(unsafe < c.unsafe) return true;
        if(unsafe > c.unsafe) return false;
        if(safe < c.safe) return true;
        return false;
    };
    
    inline FWCost operator+(struct FWCost c){
        FWCost n;
        n.safe = safe + c.safe;
        n.unsafe = unsafe + c.unsafe;
        return n;
    };
    
};
/**
 * Finds distances between all node pairs,
 * a lot slower than dijkstra if the number of queries
 * is lower then node count
 * should be O(Vertices^3) not 100% sure about it tho
 */
void FloydWarshall(){    
    int vertices, paths, queries;
    cin >> vertices >> paths >> queries;
    FWCost** nodes = new FWCost*[MAX_VERTICES];
    
    for(int i = 0; i < vertices; ++i){
        nodes[i] = new FWCost[MAX_VERTICES];
    }
    for(int i = 0; i < vertices; ++i){
        for(int j = 0; j < vertices; ++j){
            nodes[i][j].safe = MAX_COST;
            nodes[i][j].unsafe = MAX_COST;
            nodes[i][j].set = false;
        }
    }
    
    
    
    for(int i = 0; i < paths; ++i){
        int a, b, costs;
        char safe;
        cin >> a >> b >> costs >> safe;
        FWCost c;
        if(safe == 'B'){
            c.safe = costs;
            c.unsafe = 0;
            c.set = true;
            c.visited = false; 
        }
        else{
            c.safe = 0;
            c.unsafe = costs;
            c.set = true;
            c.visited = false;
        }
        if(nodes[a][b].set){
            if(c < nodes[a][b]){
                nodes[a][b] = c;
            }
        }else{
            nodes[a][b] = c;
        }
        if(nodes[b][a].set){
            if(c < nodes[b][a]){
                nodes[b][a] = c;
            }
        }else{
            nodes[b][a] = c;
        }
        
    }
    /*
    cout << endl;
    for (int k=0; k<vertices; k++){
        for (int i=0; i<vertices; i++){
            
            cout << nodes[k][i].safe << " " << nodes[k][i].unsafe << ";";
        }
        cout << endl;
    
    }*/
   
    
    for (int k=0; k<vertices; k++)
        for (int i=0; i<vertices; i++){
            if(nodes[i][k].set == false) continue;
            for (int j=0; j<i; j++){
                if(nodes[i][j].set){nodes[i][j].visited = true; nodes[j][i].visited = true;}
                if(nodes[k][j].set == false)continue;
                FWCost c = nodes[i][k] + nodes[k][j];
                c.visited = true;
                c.set = true;
                if (c < nodes[i][j]) {   
                    nodes[i][j] = c;
                    nodes[j][i] = c;
                    
                }
                
            }
        }
    
    /*
        cout << endl;
    for (int k=0; k<vertices; k++){
        for (int i=0; i<vertices; i++){
            
            cout << nodes[k][i].safe << " " << nodes[k][i].unsafe << ";";
        }
        cout << endl;
    
    }*/
    
   for(int i = 0; i < queries; ++i){
       int v1, v2;
       cin >> v1 >> v2;
       if(nodes[v1][v2].visited == false)cout << "-1 -1" << endl;
       else cout << nodes[v1][v2].unsafe << " " << nodes[v1][v2].safe + nodes[v1][v2].unsafe << endl;
   }
}