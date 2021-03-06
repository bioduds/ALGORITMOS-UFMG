/******************************************************
** Disciplina: Algoritmos I 
** Título: Trabalho Prático II - Ciclovia de Belleville
** Autor: Eduardo Capanema
** Contato: eduardocapanema@ufmg.br
** Matrícula: 2020041515
/******************************************************

/** PACOTES E INCLUSÕES **/
#include <bits/stdc++.h>
using namespace std;

// Ordenamos as entradas
bool compareByValue( const vector<int> &a, const vector<int>&b ) {
   if( a[2] < b[2] ) return true;
   if( b[2] < a[2] ) return false;
   if( a[3] < b[3] ) return false;
   if( b[3] < a[3] ) return true;
   return false;
} 

// Ordenamos as entradas
bool compareByValue2( const vector<int> &a, const vector<int>&b ) {
   if( a[0] < b[0] ) return true;
   if( b[0] < a[0] ) return false;
   return false;
} 

// a structure to represent a weighted edge in graph
class Edge {
  public:
    int src, dest, weight, cost;
};
 
// a structure to represent a connected, undirected and weighted graph
class Graph {
  public:
    // V-> Number of vertices, E-> Number of edges
    int V, E;
    // graph is represented as an array of edges. Since the graph is undirected, the edge
    // from src to dest is also edge from dest to src. Both are counted as 1 edge here.
    Edge* edge;
    vector<int> vt;
};
 
// Creates a graph with V vertices and E edges
Graph* createGraph( int V, int E ) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}
 
// A structure to represent a subset for union-find
class subset {
  public:
    int parent;
    int rank;
};
 
// A utility function to find set of an element i (uses path compression technique)
int find( subset subsets[], int i ) {
    // find root and make root as parent of i
    // (path compression)
    if( subsets[i].parent != i ) {
        subsets[i].parent = find( subsets, subsets[i].parent );
    }
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y (uses union by rank)
void Union( subset subsets[], int x, int y ) {
    int xroot = find( subsets, x );
    int yroot = find( subsets, y );
    // Attach smaller rank tree under root of high rank tree (Union by Rank)
    if( subsets[xroot].rank < subsets[yroot].rank ) { subsets[xroot].parent = yroot; }
    else if( subsets[xroot].rank > subsets[yroot].rank ) { subsets[yroot].parent = xroot; }
    // If ranks are same, then make one as root and increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Compare two edges according to their weights. Used in qsort() for sorting an array of edges
int myComp( const void* a, const void* b ) {
    Edge* a1 = ( Edge* )a;
    Edge* b1 = ( Edge* )b;
    return a1->weight > b1->weight;
}

int compare( const void* a, const void* b ) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    if( a1->weight == b1->weight )
        return a1->cost < b1->cost;
    else
        return a1->weight > b1->weight;
}
 
// The main function to construct MST using Kruskal's algorithm
void KruskalMST( Graph* graph ) {
    int V = graph->V;
    Edge result[V]; // Tnis will store the resultant MST
    int e = 0; // An index variable, used for result[]
    int i = 0; // An index variable, used for sorted edges
    // Step 1: Sort all the edges in non-decreasing order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of array of edges
    qsort( graph->edge, graph->E, sizeof( graph->edge[0] ), myComp ); 
    // Allocate memory for creating V ssubsets
    subset* subsets = new subset[( V * sizeof( subset ) )];
    // Create V subsets with single elements
    for( int v=0; v<V; ++v ) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
     // Number of edges to be taken is equal to V-1
    while( e<V - 1 && i < graph->E ) {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        Edge next_edge = graph->edge[i++];
        int x = find( subsets, next_edge.src );
        int y = find( subsets, next_edge.dest );
        // If including this edge does't cause cycle, include it in result and increment the index of result for next edge
        if( x != y ) {
            result[e++] = next_edge;
            Union( subsets, x, y );
        }
        // Else discard the next_edge
    }
    // print the contents of result[] to display the built MST
    int minimumCost = 0;
    int agr = 0;
    vector<vector<int>> nodes;
    for( i=0; i<e; ++i ) {
        minimumCost = minimumCost + result[i].weight;
        vector<int> node;
        node.push_back( result[i].src ); node.push_back( result[i].dest ); node.push_back( result[i].weight );
        nodes.push_back( node );
        agr += graph->vt[result[i].src] + graph->vt[result[i].dest];
    }
    cout << minimumCost << " " << agr << endl;
    int counters[e];
    for( int i=0; i<e; ++i ) {
        counters[i] = 0;
    }
    for( int i=0; i<e; ++i ) {
        counters[result[i].src]++; counters[result[i].dest]++;
    }
    for( int i=0; i<e; ++i ) {
        cout << counters[i] << " ";
    }
    cout << endl;
    sort( nodes.begin(), nodes.end(), compareByValue2 );
    for( i=0; i<e; ++i ) {
        cout << result[i].src << " " << result[i].dest << " " << result[i].weight << endl;
    }
    
    
}
 
/************* FUNÇÃO MAIN *************/
int main() {
    int n, t;
    cin >> n >> t;
    Graph* g = createGraph( n, t );
    for( int i=0; i<n; i++ ) {
        int val;
        cin >> val;
        g->vt.push_back( val );

    }
    vector<vector<int>> nodes;
    for( int j=0; j<t; j++ ) {
        vector<int> node;
        int pi, pj, ct;
        cin >> pi >> pj >> ct;
        node.push_back( pi ); node.push_back( pj ); node.push_back( ct ); node.push_back( g->vt[pi] );
        nodes.push_back( node );
    }
    sort( nodes.begin(), nodes.end(), compareByValue );
    int pre = nodes[0][0];
    for( int c=0; c<nodes.size(); c++ ) {
        pre = nodes[c][0];
        g->edge[c].src = nodes[c][0];
        g->edge[c].dest = nodes[c][1];
        g->edge[c].weight = nodes[c][2];
        g->edge[c].cost = nodes[c][3];
    }
    KruskalMST( g );
	return 0; // finalizamos nossa implementação
}
