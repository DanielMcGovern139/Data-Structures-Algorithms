//Takes a csv file containing game reviews as an argument. Each line of this file contains the game title, platform, score and release year.  This program parses the file into
//its respective field and sorts the game reviews on the basis of their scores and finds out what the most popular games of the last 20 years are.  This is implemented using
//quicksort because of its effiency.




#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum


#define MAX_STRING_SIZE 50

typedef struct games games;
struct games{
    char title[MAX_STRING_SIZE], platform[MAX_STRING_SIZE];
    int score, release_year; 
    
};

struct games list[20000];


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//
int partition(struct games list[], int start, int end){

    struct games temp;
    if (start == end)
    return start; //base case 

    int pivot = list[end].score; //pivot is the last element 
    int low = start-1;
    int high = end;
    for(;;){
      do{
      low++;
      if (low == end) break;
       }while(list[low].score > pivot);
        
     do{
   
      high--;
      if(high == start) break;
      }while (list[high].score < pivot);

       
      if(low>=high){
      //swap(&list[low].score,&list[end].score);
      temp = list[end];
      list[end] = list[low];
      list[low] = temp;
 
       return low;
     }
      //swap(&list[low].score,&list[high].score);
      temp = list[high];
      list[high] = list[low];
      list[low] = temp;
  
    }
}

void quickSort_helper(struct games list[], int left, int right)
{
  int q;
  
 if (left<right) {
  q = partition(list,left ,right); 
  quickSort_helper(list, left, q-1);
  quickSort_helper(list, q+1, right);
 }
}

void quickSort(struct games list[], int size){
   int p = 0;
   int q = size -1;
   quickSort_helper(list, p, q);
}





void sort_games(struct games list[], int size){
   int i, j, max_idx;
   struct games temp;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < size-1; i++)
    {
        // Find the minimum element in unsorted array
        max_idx = i;
        for (j = i+1; j < size; j++)
          if (list[j].score > list[max_idx].score)
            max_idx = j;
 
        // Swap the found minimum element with the first element
        //swap(&list[max_idx].score, &list[i].score);
        temp = list[i];
        list[i] = list[max_idx];
        list[max_idx] = temp;
        
    }
}



void print_sorted_list(struct games list[], int size){

    for (int i = 0; i < size; i++)
    {
       printf("%s %s %d %d\n", list[i].title, list[i].platform, list[i].score, list[i].release_year);
    }
    
}

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

void split_data ( FILE *f, games *list, int n) { 

    char buf[MAX_STRING_SIZE];
    next_field( f, list[n].title, MAX_STRING_SIZE );     
    next_field( f, list[n].platform, MAX_STRING_SIZE ); 
    next_field(f, buf, MAX_STRING_SIZE);
    list[n].score= atoi(buf); //score gets put in as a string and then parsed to integer 
    next_field(f, buf, MAX_STRING_SIZE);
    list[n].release_year= atoi(buf); 
   
    
}


int main(int argc, char *argv[]){
   
FILE *f;
char *fname; 
int n;

if(argc < 2){ 
   printf("usage: csv FILE\n");
   return EXIT_FAILURE;
  }



f = fopen(argv[1], "r");
if (!f) {
 printf("Unable to open %s\n", fname);
 return 0;
    }
char buffer[MAX_STRING_SIZE];
    
while(!next_field(f, buffer, MAX_STRING_SIZE));

while (!feof(f))
    {
     split_data(f, list, n);
     n++;
          
     //printf("\n");                   
    }

// always remember to close your file stream
fclose(f);

//printf("file %s loaded\n", fname);
//printf("\n");
//printf("sorted by game score\n");

quickSort(list, n);
//int top10games = 10;
print_sorted_list(list, 10);
    

return 1;

}




