/******************************************************
** Disciplina: Algoritmos I 
** Título: Trabalho Prático II - Ciclovia de Belleville
** Autor: Eduardo Capanema
** Contato: eduardocapanema@ufmg.br
** Matrícula: 2020041515
/******************************************************

/** PACOTES E INCLUSÕES **/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// STL implementation of Prim's algorithm for MST
# define INF 0x3f3f3f3f
// iPair ==>  Integer Pair
typedef pair<int, int> iPair;
 
// This class represents a directed graph using adjacency list representation
class Graph {
  private:
    int V; // No. of vertices
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int>> * adj;
  public:
    Graph( int V );  // Constructor
    // function to add an edge to graph
    void addEdge( int u, int v, int w );
    // Print MST using Prim's algorithm
    void primMST();
};
 
// Allocates memory for adjacency list
Graph::Graph( int V ) {
    this->V = V;
    adj = new list<iPair>[V];
}
 
void Graph::addEdge( int u, int v, int w ) {
    adj[u].push_back( make_pair( v, w ) );
    adj[v].push_back( make_pair( u, w ) );
}
 
// Prints shortest paths from src to all other vertices
void Graph::primMST() {
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    int src = 0; // Taking vertex 0 as source
    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key( V, INF );
    // To store parent array which in turn store MST
    vector<int> parent( V, -1 );
    // To keep track of vertices included in MST
    vector<bool> inMST( V, false );
    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push( make_pair( 0, src ) );
    key[src] = 0;
    /* Looping till priority queue becomes empty */
    while( !pq.empty() ) {
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop(); 
        inMST[u] = true;  // Include vertex in MST
        // 'i' is used to get all adjacent vertices of a vertex
        list<pair<int, int>>::iterator i;
        for( i = adj[u].begin(); i != adj[u].end(); ++i ) {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = ( *i ).first;
            int weight = ( *i ).second;
            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if( inMST[v] == false && key[v] > weight ) {
                // Updating key of v
                key[v] = weight;
                pq.push( make_pair( key[v], v ) );
                parent[v] = u;
            }
        }
    }
    // Print edges of MST using parent array
    for( int i = 1; i < V; ++i ) { printf( "%d - %d\n", parent[i], i ); }
}

/************* FUNÇÃO MAIN *************/
// Driver program to test methods of graph class
int main() {
    // create the graph given in above fugure

    int n, t;
    vector<int> vt;

    cin >> n >> t;
    cout << "N: " << n << " T: " << t << endl;

    for( int i=0; i<n; i++ ) {
        int val;
        cin >> val;
        vt.push_back( val );
        cout << "VT: " << vt[i] << endl;

    }

    Graph g( n );
    //  making above shown graph

    for( int j=0; j<t; j++ ) {
        cout << "LINHA " << j << endl;
        int pi, pj, ct;
        cin >> pi >> pj >> ct;
        cout << "pi: " << pi << " pj: " << pj << " ct:" << ct << endl;
        g.addEdge( pi, pj, ct );
    }

    //g.addEdge( 0, 1, 4 );
    g.primMST();
	return 0; // finalizamos nossa implementação
}