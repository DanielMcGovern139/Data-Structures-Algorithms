//representing a graph using adjacency lists and traversing the graph using breadth first search and depth first search


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40

typedef struct adj_list_node // A structure to represent an adjacency list node
{
    int dest;
    struct adj_list_node* next;
}adj_list_node;
  
typedef struct AdjList // A structure to represent an adjacency list with a pointer to its head 
{
    struct adj_list_node *head;
}AdjList;

typedef struct Graph{
   int num_vertices; // Size of array will be num_vertices (number of vertices in graph)

   struct AdjList* array; //an array of adjacency lists
   int* visited;
} Graph;

struct queue {
  int queue_array[SIZE];
  int front;
  int back;
};

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results

void delete_graph(Graph* g);

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);


adj_list_node* newadj_list_node(int dest) // A function to create a new adjacency list node
{

    adj_list_node* newNode = (adj_list_node*) malloc(sizeof( adj_list_node)); //create the node 
    newNode->dest = dest; //assign the destination 
    newNode->next = NULL; //assign the next pointer 
    return newNode;
}

// A function to creates a graph of size num_vertices
Graph* create_graph(int num_nodes){
  

   Graph* g = (Graph*) malloc(sizeof( Graph));
    g->num_vertices = num_nodes; //v is assigned the num nodes 
   
    // Create an array of adjacency lists. Size of array will be V
    g->array = (AdjList*) malloc(num_nodes * sizeof(AdjList)); 
    g->visited = malloc(num_nodes * sizeof(int)); //visited set also
  
  
    for (int i = 0; i < num_nodes; ++i){  // Initialize each adjacency list as empty by making head as NULL 
        g->array[i].head = NULL;
        g->visited[i] = 0; //set each vertex as not visited 
    }
        
    return g;
}

void add_edge(Graph *g, int from, int to){
  // Add an edge from source to destination. A new node is
  // added to the adjacency list of source. The node
  // is added at the begining
  
    adj_list_node* newNode = newadj_list_node(to); //create the node with the incoming letter say E
    newNode->next = g->array[from].head; //linking the from and to nodes e.g A->E
    g->array[from].head = newNode; // making the new node the head of the adjacency list
  
}

 void dfs_helper(Graph* g, int origin)
{
   //the origin being A for example
  
     adj_list_node *p; //pointer for our list
  
printf(" %c ", origin+'A');  //this will print A, B, C.. etc with help from char2val in the main func
    p=g->array[origin].head; //make p the head of the current nodes list
    g->visited[origin]=1; //mark the current node as visited 
    while(p!=NULL)
    {
       origin=p->dest; //make origin the destination 
      
        if(!(g->visited[origin])){ //if the origin hasn't been visited 
            dfs_helper(g, origin); // call DFS on that origin node 
                            // by calling dfs recursively like this, it will bring us deeper into the graph instead
                            // of bfs which prints all the neigbours and moves on  
    }
        p=p->next; //else we move to the next in the list 
    }
}

void dfs(Graph* g, int origin){
  printf("DFS:");
  dfs_helper(g, origin);
  printf("\n");

  //this is just to initialise them again for bfs
  for (int i = 0; i < g->num_vertices; ++i){
    
      g->visited[i] = 0;
    }
}


 void bfs( Graph* g, int origin) {
  printf("BFS ");
  struct queue* q = createQueue();

  g->visited[origin] = 1;
  enqueue(q, origin); //add the origin node to the queue and mark it has visited

  while (!isEmpty(q)) {
    
    int currentVertex = dequeue(q);
    printf(" %c ", currentVertex+'A');

     adj_list_node* temp = g->array[currentVertex].head;

    while (temp) { // say for A..we would now be in A's list of neigbours, so in this inner while loop visit all 
                   // A's neigbhours, once we have visited all the neigbours then we will move onto C and F because
                   // they are not A's neigbours and they will be in another list 
      int adjVertex = temp->dest;

      if (g->visited[adjVertex] == 0) {
        g->visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
  printf("\n");
  free(q);
}


void delete_graph(Graph* g){
   
    adj_list_node* temp;
    adj_list_node* p;
    
  for (int i=0; i<g->num_vertices; i++){
     temp = g->array[i].head; //goes through each list
     while(temp){
       p = temp; //temparary pointer so that we dont delete our link between two nodes 
       temp = temp->next;
       free(p);
     }
     
  }
  free(g->array);
  free(g->visited);
  free(g);



}


// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->back = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->back == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
  if (q->back == SIZE - 1);
    
  else {
    if (q->front == -1)
      q->front = 0;
    q->back++;
    q->queue_array[q->back] = value;
  }
}

// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    item = -1;
  } else {
    item = q->queue_array[q->front];
    q->front++;
    if (q->front > q->back) {
     
      q->front = q->back = -1;
    }
  }
  return item;
}

static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 6;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));

    dfs(graph, char2val('A'));
    bfs(graph, char2val('A'));
  

    delete_graph(graph);

}
