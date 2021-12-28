#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum
#include <limits.h>
#include <stdbool.h>
#ifndef T3_H_
#define T3_H_

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

#endif
