#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
    char data;
    struct Node* next;
    } Node;


void addNode(char data, Node *head){
 
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->next = NULL;
  newNode->data = data;

  Node *temp = head; //pointer to traverse the list
  
  while((temp->next) != NULL){
      temp = temp->next;
  }

   temp->next = newNode; //link the new node to the previous last node
                         //in the list

}

void printList(Node *list) {
    int i = 0; //this is just used as a counter 
    while(list != NULL){
        printf("%d->",list->data);
        //printf("Item %d = %d\n", i , list->data);
        list = list->next;
        i++;
    }

    printf("Null\n");
}

void deleteList(Node *list){
    Node *nextNode = list->next;
    free(list);

    if(nextNode != NULL)
       deleteList(nextNode);
    else 
       printf("Finished\n");
}

int listlength(Node *list){ 
  int i = 0;
  while(list != NULL){
      i++;
      list = list->next;
    
}
return i;

}

Node* reverseList(Node *list){
    //need a few pointers to start
    Node* prev = list; //1st node
    Node* current = list->next; // 2nd node
    Node* next = current->next; //3rd node

    prev->next = NULL; //flip the 1st nodes next pointer

    while(1) //while true..i think it will keep looping until it enters that if statement 
    {
      current->next = prev; //flip the current nodes next point

      if(next->next == NULL){ //if this the case we are done
          next->next = current;
          return next;
      }
      else {
          prev = current;
          current = next;
          next = next->next;
      }
   }
}

int main() {
    
Node *head = (Node*)malloc(sizeof(Node));
head->data = 0;
head->next = NULL;

for(int i = 1; i < 6; i++)
{
  addNode(i, head);
}

printf("Original List\n");
printList(head);
printf("\n");
int length = listlength(head);
printf("The length of the list is %d\n\n", length);

Node* reversedHead = reverseList(head); //it returns a new head

printf("Reversed List");
printf("\n");
printList(reversedHead);
printf("\n");
deleteList(head);

return 0;
  
}
