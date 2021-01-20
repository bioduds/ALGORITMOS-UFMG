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
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph {

    int V; // No. of vertices
  	// Pointer to an array containing
	// adjacency lists
	list<int> * adj;
	// A recursive function used by DFS
	void DFSUtil( int v, bool visited[] );

  public:
	Graph( int V ); // Constructor
	// function to add an edge to graph
	void addEdge( int v, int w );
	// DFS traversal of the vertices
	// reachable from v
	void DFS( int v );

};

Graph::Graph( int V ) {
	
    this->V = V; // assign do construtor
	adj = new list<int>[V]; // iniciamos uma lista de adjacencia

}

void Graph::addEdge( int v, int w ) {

	adj[v].push_back( w ); // Add w to v’s list.

}

void Graph::DFSUtil( int v, bool visited[] ) {

	// Mark the current node as visited and
	// print it
	visited[v] = true;
	cout << v << " ";
	// Recur for all the vertices adjacent
	// to this vertex
	list<int>::iterator i;
	for( i = adj[v].begin(); i != adj[v].end(); ++i ) {
		if( !visited[*i] ) { DFSUtil( *i, visited ); }
    }

}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS( int v ) {

	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for( int i = 0; i < V; i++ ) { visited[i] = false; }
	// Call the recursive helper function
	// to print DFS traversal
	DFSUtil( v, visited );

}

// Driver code
int main() {

    // begin read of input
    int c, p, x;
    cin >> c >> p >> x;

    Graph g( p + c );

    int s1, s2;

    for( int j=0; j < ( p + c ); j++ ) {
        //cout << "Correndo linha: " << j << endl;
        string line;
        getline( cin, line );
        istringstream is( line );
        int n;

        while( is >> n ) {
            // do something with n
            //cout << "n: " << n << " ";
            if( j <= c ) { // lendo CDs
                if( j == 0 ) { s1 = n; }
                cout << "n: " << n << " ";
                g.addEdge( 0, n );
            } else {

            }

        }
        //cout << "Pula" << endl;

    }
    cout << "Travessia em 0: "; g.DFS( 0 ); cout << endl;

	// Create a graph given in the above diagram
	// Graph g( 4 );
	// g.addEdge( 0, 1 );
	// g.addEdge( 0, 2 );
	// g.addEdge( 1, 2 );
	// g.addEdge( 2, 0 );
	// g.addEdge( 2, 3 );
	// g.addEdge( 3, 3 );
	// cout << "Following is Depth First Traversal (starting from vertex x) \n";
    // g.DFS( 2 );
    cout << endl;
	return 0;
    
}