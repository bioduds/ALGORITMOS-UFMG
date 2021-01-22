/* 
** Título: Trabalho Prático I - Vacinação COVID-19
** Contato: eduardocapanema@ufmg.br
** Matrícula: 2020041515
** Disciplina: Algoritmos I
*/

// C++ program to print DFS traversal from
// a given vertex in a given graph
#include<iostream>
#include <sstream>
#include<list>
#include <vector>
#include <algorithm>

using namespace std;


// Graph class represents a directed graph
// using adjacency list representation
class Graph {

    int V; // No. of vertices
  	// Pointer to an array containing
	// adjacency lists
	list<int> * adj;
	// A recursive function used by DFS
	void DFSUtil( int v, bool visited[], int f );

  public:
	Graph( int V ); // Constructor
	// function to add an edge to graph
	void addEdge( int v, int w );
	// DFS traversal of the vertices
	// reachable from v
	void DFS( int v );
    vector<int> path;
    int fuel;
    int hasCycle = 0;

};

Graph::Graph( int V ) {
	
    this->V = V; // assign do construtor
	adj = new list<int>[V]; // iniciamos uma lista de adjacencia

}

void Graph::addEdge( int v, int w ) {

	adj[v].push_back( w ); // Add w to v’s list.

}

void Graph::DFSUtil( int v, bool visited[], int f=0 ) {

    //cout << "DFSUtil fuel: " << f << endl;
	// Mark the current node as visited and
	// print it
	visited[v] = true;
	//cout << v << " ";
    path.push_back( v );
	// Recur for all the vertices adjacent
	// to this vertex
	list<int>::iterator i;
	for( i = adj[v].begin(); i != adj[v].end(); ++i ) {
        //cout << "Checing iter: " << *i << endl;
  		if( !visited[*i] ) {
            //cout << "Recursivando..." << endl;
            int nFuel = f-1;
            if( nFuel >= 0 ){ DFSUtil( *i, visited, nFuel ); }
        }
    }

}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS( int v ) {

    //cout << "Doing DFS com fuel: " << fuel << endl;

	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for( int i = 0; i < V; i++ ) { 
        visited[i] = false; 
    }
	// Call the recursive helper function
	// to print DFS traversal
	DFSUtil( v, visited, fuel );

}

// Driver code
int main() {

    int c, p, x;
    cin >> c >> p >> x;
    Graph g( p + c );
    vector<string> pLines; 
    for( int i=0; i <= ( p + c ); i++ ) {
        string line;
        getline( cin, line );
        istringstream is( line );
        int n;
        while( is >> n ) {
            if( i <= c ) { g.addEdge( 0, n ); } 
            else {
                if( n != 0 ) { g.addEdge( ( i - 2 ), n ); }
            }
        }
    }

    // calc fuel
    g.fuel = 30/x;
    //cout << "x: " << x << " 30/x (fuel): " << g.fuel << endl;
    g.DFS( 0 );
    sort( g.path.begin(), g.path.end() );
    cout << g.path.size() - 1 << endl;
    for( int j=1; j < g.path.size(); j++ ) {
        cout << g.path[j] << " ";
    }
    cout << endl;
    cout << g.hasCycle << endl;

	return 0;
    
}