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

    int c, p, x;
    cin >> c >> p >> x;
    Graph g( p + c );
    vector<string> pLines; 
    for( int i=0; i<( p + c ); i++ ) {
        string line;
        getline( cin, line );
        istringstream is( line );
        int n;
        while( is >> n ) {
            if( i <= c ) { // lendo CDs
                cout << "n: " << n << " ";
                g.addEdge( 0, n );
            }
        }
        pLines.push_back( line );
    }
    cout << endl;

    for( int j=0; j<c; j++ ) {
        cout << "CD line: " << pLines[j+1] << endl;
        for( int j=c+1; j<=pLines.size(); j++ ) {
            cout << "PV line: " << pLines[j] << endl;
        }
    }

    cout << "Travessia em 0: "; g.DFS( 0 ); cout << endl;
    cout << endl;
	return 0;
    
}