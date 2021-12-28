//This program involves implementing a hash table for infromation retrieval. Given a file containing a list of (unordered) people. Along with each person comes 
//their gender, nationality, occupation etc.  Have to parse the file into their seperate fields and insert into a hash table using the surname of each person 
//as a key and provide a way to search for information in the hash table. Allowing a user to enter a surname and get a list of people with the given surname as a search result.


#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 99991  //best be prime
int collisions =0;
int num_terms = 0;

typedef struct Element Element;
struct Element{
    char surname[MAX_STRING_SIZE], forename[MAX_STRING_SIZE], persontype[MAX_STRING_SIZE], gender[MAX_STRING_SIZE], nationality[MAX_STRING_SIZE],religion[MAX_STRING_SIZE], occupation[MAX_STRING_SIZE], deposition_id[MAX_STRING_SIZE] ;

    int person_id, age; 

    Element* next; //for the linked list and also for p
    
};

Element* hashTable[ARRAY_SIZE];

int hash_function(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s)%ARRAY_SIZE;
        s++;
    }
    return hash;
}
int hash3_function(char* s){
    int hash = 0;
     while(*s){
     hash = (1+ (hash + *s)) % (ARRAY_SIZE-1);
      s++;
}
return hash;
}
Element* createNewElement(){
  Element* new_item = (Element*) malloc(sizeof(Element));
  new_item->next = NULL;
   
    return new_item;
}
Element* search (char* name){
    int i = 0;
    int  hash = (hash_function(name)+i*hash3_function(name))%ARRAY_SIZE;
    

    while(hashTable[hash]!=NULL){
      
     if (strcmp(hashTable[hash]->surname,name)==0){
      return hashTable[hash];
      
     }
      i++;
      hash = (hash_function(name)+i*hash3_function(name))%ARRAY_SIZE;
    }
    return NULL;
}

void insert(Element* element){
   if(search(element->surname)==NULL){ //if the cell is empty..then try to insert the word into the hash table
      int i = 0;
      int hash = (hash_function(element->surname)+i*hash3_function(element->surname))%ARRAY_SIZE; //create a hash out of just the surname 
     
     while(hashTable[hash]!=NULL){
     i++ ;
     hash = (hash_function(element->surname)+i*hash3_function(element->surname))%ARRAY_SIZE;
     collisions++;
    }
     hashTable[hash] = element;
      
   }
   else  { //else the cell is not empty so we link
     Element* current = search(element->surname); //current will be the hash index
     while(current->next!=NULL){
       current = current->next; //traverse the list until we reach the end 
     }
     current->next = element; //put the new name at the end of the list
   }
}
// The CSV parser
int next_field( FILE *f, char *buf, int max ) { //parser from assignment 0. gets rid of quote marks and commas 
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

void split_data ( FILE *f, Element *element) { //we assign each word to its respective place such as occupation or gender using a pointer element 
//element is a pointer.... element->occupation, element->gender etc
//next field is word by word so that is why there is 10 next field functions in this.. the second string in each line is assigned to the p->deposition ID
    char buf[MAX_STRING_SIZE];
    next_field( f, buf, MAX_STRING_SIZE );     //Id gets put in as a string and then parsed to integer 
    element->person_id = atoi(buf);                     
    next_field( f, element->deposition_id, MAX_STRING_SIZE );   
    next_field( f, element->surname, MAX_STRING_SIZE ); 
    next_field( f, element->forename, MAX_STRING_SIZE ); 
    next_field( f, buf, MAX_STRING_SIZE );   
    element->age = atoi(buf);
    next_field( f, element->persontype, MAX_STRING_SIZE );
    next_field( f, element->gender, MAX_STRING_SIZE );
    next_field( f, element->nationality, MAX_STRING_SIZE );
    next_field( f, element->religion, MAX_STRING_SIZE );
    next_field( f, element->occupation, MAX_STRING_SIZE );
}

void print_data( Element *element ) {
    printf("    %d    %s     ", element->person_id, element->deposition_id);
    printf("       %s         %s       %d ", element->surname,element->forename, element->age);
    printf("   %s            %s", element->persontype, element->gender);
    printf("  %s    %s  %s\n",element->nationality, element->religion, element->occupation);
}

int load_file ( char *fname ) {
    FILE *f;
     

    
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    Element* v =createNewElement();
    split_data(f, v); //for the first line of titles 
    free(v); //getting rid of a temporary pointer 
    //while its not the end of file 
    while ( !feof(f) ) {
       Element* element =createNewElement(); //new element each time to create the p->gender say for example
        num_terms++; //number of people 
        split_data( f, element); //here we get a line of data and we assign p to each description..so first we get the person ID
        insert(element); //insert p, getting a hash index using the surname                      
    }

    // always remember to close your file stream
    fclose(f);
    printf("File %s loaded\n", fname);

    return 1;
}
  void deletep(){
    Element* next;
    for(int i = 0; i < ARRAY_SIZE; i++){
       Element* element = hashTable[i];
      while (element!=NULL){
        next = element->next; //so that we dont lose track of pointers
        free(element);
        element = next;

      }
    }
  }

  void printNumberOfOccurences(char *name){
  printf(" Person ID Deposition ID         Surname        Forename Age Person Type  Gender Nationality Religion Occupation\n");
  Element* element = search(name); //get the pointer for the name 
  if(element!=NULL){
    print_data(element);
    while(element->next != NULL){ //going through the linked list
      print_data(element->next);
      element = element->next;
    }
   } //if p = null then name does not exist
   //printf("not in table");
 }

int main(void) {
  
  load_file("truncated.csv");
  
  printf(" Capacity: %d\n", ARRAY_SIZE);
  printf(" Num Terms: %d\n", num_terms);
  printf(" Collisions: %d\n", collisions);
  printf(" Load: %f\n", ((double)num_terms)/ARRAY_SIZE);

 
  char name[MAX_STRING_SIZE];
  char stop[] = "quit";
  printf("Enter term to get frequency or type \"quit\" to escape\n");
  printf(">>> ");
  scanf("%s", name);

 while(strcmp(name,stop )!=0){ //if = 0 then we quit
   if (search(name)!=NULL){
     printNumberOfOccurences(name);
   } else printf(" %s not in table\n", name); //if the cell is null name not in table 
   printf(">>>");
   scanf("%s", name);  
 }

   
   deletep();
  return 0;
}
