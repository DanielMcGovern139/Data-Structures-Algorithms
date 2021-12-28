#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10 // you can assume that the graph has at most 10 vertex
typedef struct Graph{
    int V;
    int matrix[MAX_VERTICES][MAX_VERTICES];

}Graph;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight); // adds an undirected weighted edge between from and to

void dijkstra(Graph* g, int origin); // implements the dijkstra algorithm and prints the order in which the nodes are made permament, 
                                    //and the length of the shortest path between the origin node and all the other nodes
void delete_graph(Graph* g);
void print_graph(Graph *g);

int minDistance(int dist[], bool sptSet[]);
void printSolution(int dist[], int v, int origin);

Graph* create_graph(int num_nodes){
 Graph* g = (Graph*) malloc(sizeof( Graph));
 g->V = num_nodes;

 for (int i=0; i<MAX_VERTICES; i++){
   for(int j=0; j<MAX_VERTICES; j++){
     g->matrix[i][j] = 0;
   }
 }

 return g;
}

void add_edge(Graph *g, int from, int to, int weight){
  g->matrix[from][to] = weight;
  g->matrix[to][from] = weight;
}

//this method is heavily inspired by geeks for geeks..https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
void dijkstra(Graph* g, int origin)
{
  int V = g->V; //num of vertices
   
  int dist[MAX_VERTICES];  //Holds distances from origin
 
  bool sptSet[MAX_VERTICES];  //Create a set sptSet (shortest path tree set) that keeps track of vertices to 
                              //be included in the shortest path tree whose minimum distance from 
                              //the source is calculated and finalized, if the vertex is to be included 
                              //we mark it as true 
 
  // Initialize all distances as INFINITE and vertices as not sptSet
  for (int i = 0; i < MAX_VERTICES; i++) {
       dist[i] = INT_MAX; 
       sptSet[i] = false;  
   }
      //Distance of origin to itself is always 0
      dist[origin] = 0;
    
      // Find shortest path for all vertices
      for (int count = 0; count < V; count++) { //once we have seen all routes up to our destination 
        
        // Pick the minimum distance vertex from the set of vertices that are not
        // yet in the sptSet.
        int u = minDistance(dist, sptSet);
 
        //add this vertex to the shortest path tree
        sptSet[u] = true;
        printf("%c ", u +'A');
        
        //Update dist value of the adjacent vertices of the picked vertex.
        //for loop will go through all the current nodes edges. 
        for (int v = 0; v < MAX_VERTICES; v++){
 
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from orogin to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && g->matrix[u][v] && dist[u] != INT_MAX
                && dist[u] + g->matrix[u][v] < dist[v]){ //g->matrix[u][v] == weight
                dist[v] = dist[u] + g->matrix[u][v];
            }
         }
      }
 // print the constructed distance array
printSolution(dist, V, origin);
}
 

void delete_graph(Graph* g){
  free(g);
}



// Function to find the vertex with minimum distance value, from
// the set of vertices not yet made sptSet
int minDistance(int dist[], bool sptSet[])
{
    
    int min = INT_MAX, min_index; //note every time this function is called min index is initialised to INT_MAX
    
 
    for (int v = 0; v < MAX_VERTICES; v++)
        if (sptSet[v] == false && dist[v] < min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
void printSolution(int dist[], int v, int origin) {
//this will move through the distances, so dist between A and A, dist between A and B, dist between A and C...
printf("\n");
    for (int i = 0; i < v; i++) { //v is the number if vertices 
        printf("The length of the shortest path between %c and %c is %d\n", origin + 'A', i+'A', dist[i]);
    }
}

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 7;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('B'),1);
    add_edge(graph, char2val('A'), char2val('C'),3);
    add_edge(graph, char2val('A'), char2val('F'), 10);
    add_edge(graph, char2val('B'), char2val('G'), 2);
    add_edge(graph, char2val('B'), char2val('D'), 7);
    add_edge(graph, char2val('B'), char2val('E'), 5);
    add_edge(graph, char2val('B'), char2val('C'), 1);
    add_edge(graph, char2val('C'), char2val('D'), 9);
    add_edge(graph, char2val('C'), char2val('E'), 3);
    add_edge(graph, char2val('D'), char2val('G'), 12);
    add_edge(graph, char2val('D'), char2val('F'), 1);
    add_edge(graph, char2val('D'), char2val('E'), 2);
    add_edge(graph, char2val('E'), char2val('F'), 2);

    dijkstra(graph, char2val('A'));
   
    delete_graph(graph);


}


      
