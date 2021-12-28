//There are two input CSV files, one contains a list of all bus stops in Dublin (nodes) and the other contains a list of routes between those bus stops(edges). 
//The weights on each of the edges is the distance in metres between each bus stop.  This program loads the data from both files and uses the edges and nodes to build
//a graph which models the public transport system of Dublin City.  Then, using Dijkstra’s algorithm on the graph, prints the
//optimal sequence of bus stops from a given source to a given destination.

#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum
#include <limits.h>
#include <stdbool.h>


#define MAX_STRING_SIZE 80 //max length of a string
#define MAX_VERTICES 7668 // max vertices in graph

typedef struct bus_stop {
int stop_id, latitude, longitude;
char name[MAX_STRING_SIZE];
}bus_stop;

typedef struct Graph{
    int V;
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int from, to, weight;

}Graph;

bus_stop* array[MAX_VERTICES];
Graph* g;

Graph* create_graph(int num_nodes);
void add_edge(Graph *g, int from, int to, int weight); // adds an undirected weighted edge between from and to
int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void dijkstra(int origin, int destination); 
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

int minDistance(int dist[], bool sptSet[]);
void printSolution(int dist[], int prev[], int v, int origin, int dest);

// The CSV parser
int
next_field( FILE *f, char *buf, int max ) {
    int i=0, end=0, quoted=0;
    
    for(;;) {
        // fetch the next character from file
        buf[i] = fgetc(f);
        // if we encounter quotes then flip our state and immediately fetch next char
        if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
        // end of field on comma if we're not inside quotes
        if(buf[i]==',' && !quoted) { break; }
        // end record on newline or end of file
        if(feof(f) || buf[i]=='\n') { end=1; break; }
        // truncate fields that would overflow the buffer
        if( i<max-1 ) { ++i; }
    }

    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}

void
fetch_vertices(FILE *csv, bus_stop *p) {
    char buf[MAX_STRING_SIZE];

    next_field( csv, buf, MAX_STRING_SIZE );
    p->stop_id = atoi(buf); 

    next_field( csv, p->name, MAX_STRING_SIZE );

    next_field( csv, buf, MAX_STRING_SIZE );
    p->latitude = atof(buf); 

    next_field( csv, buf, MAX_STRING_SIZE );
    p->longitude = atof(buf); 
    


     
}
void
fetch_edges (FILE *csv, Graph *p) {
    char buf[MAX_STRING_SIZE];

    next_field( csv, buf, MAX_STRING_SIZE );
    p->from = atoi(buf); 
    
    next_field( csv, buf, MAX_STRING_SIZE );
    p->to = atoi(buf); 

    next_field( csv, buf, MAX_STRING_SIZE );
    p->weight = atoi(buf);


     
}

Graph* create_graph(int num_nodes){
 Graph* g = (Graph*) malloc(sizeof( Graph));
 g->V = num_nodes;

    for (int i=0; i<MAX_VERTICES; i++){
      for(int j=0; j<MAX_VERTICES; j++){
        g->matrix[i][j] = 0; // initilaising every vertex in the graph to 0
      }
    }

 return g;
}

void add_edge(Graph *g, int from, int to, int weight){
  g->matrix[from][to] = weight;
  g->matrix[to][from] = weight;
  //double sided edges
}

int load_vertices ( char *fname ) {
    FILE *f;
    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    bus_stop* v =(bus_stop*) malloc(sizeof(bus_stop));
    fetch_vertices(f, v);
    free(v); 
    int i = 0;
    // read until the end of the file
    while ( !feof(f) && i<MAX_VERTICES ) {
      
       bus_stop* p =(bus_stop*) malloc(sizeof(bus_stop));
        fetch_vertices(f, p);
        array[p->stop_id] = p; 
        i++; //keeps a count of how many vertices loaded 
    }
    printf("Loaded %d vertices\n", i);
    // close file stream
    fclose(f);
    
    

    return 1;
}
int load_edges ( char *fname ){  //we build our graph in this function
g = create_graph(MAX_VERTICES);

FILE *f;
     

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    
   
   fetch_edges(f, g); //discard header
   
   int i = 0; //keeps count of the edges for output 
   while ( !feof(f) ) {
      
       fetch_edges(f,g);
       
      add_edge(g, g->from, g->to,g->weight); //put them into our graph
      i++;
    }
    // always remember to close your file stream
    fclose(f);
    printf("Loaded %d edges\n", i);
    
    return 1;
}


void shortest_path(int startNode, int endNode){
  dijkstra(startNode, endNode);
}

void dijkstra(int origin, int destination)
{
  int V = g->V; //num of vertices
   
    int dist[MAX_VERTICES];  //Holds distances from origin
    int prev[MAX_VERTICES]; //keeps track of route
    bool sptSet[MAX_VERTICES];  //shortest path tree set
    // Initialize all variables
    
    for (int i = 0; i < MAX_VERTICES; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false; 
        prev[i]=-1;
    }
    // Distance of origin to itself is always 0
    dist[origin] = 0;
    prev[origin] = origin;
     
      
    // Find shortest path for all vertices
    while (!sptSet[destination]) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet made sptSet.
        int u = minDistance(dist, sptSet);
 
        // Mark the picked vertex as sptSet
        sptSet[u] = true;
        
        
       
 
        // Update dist value of the adjacent vertices of the picked vertex and prev value of where it came from
        for (int v = 0; v < MAX_VERTICES; v++){
 
            // Update dist[v] only if is not sptSet, there is an edge from
            // u to v, and total weight of path from origin to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && g->matrix[u][v] && dist[u] != INT_MAX
                && dist[u] + g->matrix[u][v] < dist[v]){
                dist[v] = dist[u] + g->matrix[u][v];
                prev[v]=u;
                }
        }
    }
 
    // print the shortest path from origin to destination
    
    printSolution(dist, prev, V, origin, destination);
}
 
 void free_memory ( void ) {
   free(g);
   for (int i = 0; i < MAX_VERTICES; i++){
     free(array[i]);
   }
 }



// Function to find the vertex with minimum distance value, from
// the set of vertices not yet made sptSet
int minDistance(int dist[], bool sptSet[])
{
    
    int min = INT_MAX, min_index;
    
 
    for (int v = 0; v <MAX_VERTICES ; v++)
        if (sptSet[v] == false && dist[v] < min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 

void printData(int i){
  printf("%d %s\n", i, array[i]->name);
}

//prints shortest path 
void printSolution(int dist[], int prev[], int v, int origin, int dest){
 
//this will reverse the order so that we are printing from orgin to destination instead of backwards
  
  int array[100]; 
  int j = 99;
  int i = prev[dest];
  array[j] = dest; 
  j--;
  while(i!=origin){
       array[j]=i;
       i = prev[i];
       j--;
  }
  
  array[j]=i;
         
  for(int k = j; k <100; k++){
      printData(array[k]);
        }
         
}
 

 int main ( int argc, char *argv[] ) {

	load_vertices("vertices.csv");
  load_edges("edges.csv");
  
	int startingNode = 300, endingNode = 253; 
   

    /*get the start and end point
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode); 
    */

	shortest_path(startingNode, endingNode);
    

	free_memory();

	
}

