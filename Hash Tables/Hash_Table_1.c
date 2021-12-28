#include<stdio.h>
#include<stdlib.h>
#include <string.h> 
#include <ctype.h>  


#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 59  //best be prime..size of the hash table 
int collisions =0;
int numterms = 0;

typedef struct Element Element;
struct Element{
    char surname[MAX_STRING_SIZE]; //surname that can be a max of 20 letters
    int count;
};

Element* hashTable[ARRAY_SIZE]; //hash table of size 67..can store 67 names 

int hash_function(char* s){ //takes in a charachter 
    int hash = 0;
    while(*s){
        hash = (hash + *s)%ARRAY_SIZE; //hash function
        s++;
    }
    return hash;
}

Element* createNewElement(char* name){
    
    Element* new_element = (Element*) malloc(sizeof(Element)); //creating the new element
    strcpy(new_element->surname, name); //copying name into the surname part of the new element 
    new_element->count = 1; //the count part of the new_element is appended to 1 
    return new_element;
}


// returns the element with name or NULL if the element is not present
Element* search (char* name){
   
    int i = 0;
    int hash = (hash_function(name)+i)%ARRAY_SIZE;
    
    while(hashTable[hash]!=NULL){ //once its null we stop the loop and return null
      
     if (strcmp(hashTable[hash]->surname,name)==0){ //if two strings are the same it returns the cell..otherwise it wil return a non zero value (if surname = name)
      return hashTable[hash];
      
     }
     i++;
      hash = (hash_function(name)+i)%ARRAY_SIZE; //move onto the next hash key
    }
    return NULL;
}

void insert(char* name){
   if(search(name)==NULL){
     int i = 0;
     int hash = (hash_function(name)+i)%ARRAY_SIZE;
     //if the cell is null then we dont have to visit any other ones 
     while(hashTable[hash]!=NULL){
       i++;

       hash = (hash_function(name)+i)%ARRAY_SIZE;
        
      
       collisions++; //every time move to a new hashKey and there is already something there then it is a collision
    }
     hashTable[hash] = createNewElement(name); //create a new element for this name 
     numterms++; 
   }
   else { //else we already have the name in the hash table so we just append its count 
       search(name)->count++;
}
}

//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){
    insert(name);
}


// prints the number of occurences, or 0 if not in the file
void printNumberOfOccurences(char* name){
    int count=0;
        if(search(name)!=NULL){
          count = search(name)->count; //find the count for the name 
        }
        
        printf("%s - %i \n", name, count);

}

// function from the assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) 
    { 
      buf[0] = fgetc(f); 
      }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { break; } // only load letters and numbers
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) 
    { ++i; 
    } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
    FILE *f;
    char buf[MAX_STRING_SIZE];

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    
    // read until the end of the file
    while ( !feof(f) ) {
        next_token(buf, f, MAX_STRING_SIZE);
        addOrIncrement(buf);                         
    }

    // always remember to close your file stream
    fclose(f);
    printf("File %s loaded\n", fname);

    return 1;
}


int main()
{
  load_file("names.csv");
  printf(" Capacity: %d\n", ARRAY_SIZE);
  printf(" Num Terms: %d\n", numterms);
  printf(" Collisions: %d\n", collisions);
  printf(" Load: %f\n", ((double)numterms)/ARRAY_SIZE);

 
  char str[MAX_STRING_SIZE];
  char str1[] = "quit";
  printf("Enter term to get frequency or type \"quit\" to escape\n");
  printf(">>> ");
 scanf("%s", str);

 while(strcmp(str,str1 )!=0){ //if = 0 then we quit 
   if (search(str)!=NULL){ //if we find the string print number of occurences 
     printNumberOfOccurences(str);
   } 
   else printf("%s - 0 \n", str); //else print the count 0 
   //printf("\n");
   printf(">>> "); 
   scanf("%s", str); //next iteration
 }
 return 0;
}

