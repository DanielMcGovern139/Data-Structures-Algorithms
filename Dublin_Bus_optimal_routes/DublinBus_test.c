#include <stdio.h>
#include <stdlib.h>
#include "t3.h"
#include "t3.c"
#include <stdio.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

int
main ( int argc, char *argv[] ) {

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
