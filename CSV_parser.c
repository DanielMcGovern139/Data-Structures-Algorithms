#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER  256

int next_field(FILE *f, char *buf, int max ){
int i = 0, end = 0, quoted = 0;
for(;;){
  
  //fetch the next charachter in the file
  buf[i] = fgetc(f); //buf[i] is the character 
 
  //if we encounter quotes then flip our state and immieditaly fetch next char
  if(buf[i] == '"'){
    quoted = !quoted; //flip the state..like true to false 
    buf[i] = fgetc(f); //get the next char
  }
  //end of field on comma if we are not inside quotes
  if(buf[i] == ',' && !quoted){ //if the char is a comma and we are not inside quote marks we want to go onto a mew line
    break;
  }
  //end record on newline or end of file 
  if(feof(f) || buf[i] == '\n'){
    end = 1; 
    break;
  }
  if(i < max -1){
    i++;
  }
}
  buf[i] = 0;
  return end;

}

int main(int argc, char *argv[]) {
  FILE *f;
  char buffer[MAX_BUFFER];
   
   if(argc < 2){ 
    printf("usage: csv FILE\n");
    return EXIT_FAILURE;
  }
  f = fopen(argv[1], "r");  //argv[1] is the file name sample.csv
  if(!f){ //if we cant open the file 
    printf("unable to open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  
  
  while( !next_field(f, buffer, MAX_BUFFER)); //discard the header
                                              //while 'end' in the function is 0..once end is 1 we move to a new line 
  
  
  //now read and print records until the end of the file
  while(!feof(f)){
    int eor = next_field(f, buffer, MAX_BUFFER); //if eor = 1 then we are the end of the line/field so
                                                 //we move onto the next row 
    printf("%s%c\n", buffer, ((eor)?'\n' : ' '));  

  }
 
  fclose(f);
  
  return EXIT_SUCCESS;
}



  
