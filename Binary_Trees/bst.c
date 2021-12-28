#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


int frees = 0;

void tree_insert(Tree_Node** root, char data){
  Tree_Node * node;
   node = *root;
     if (*root == NULL){
       Tree_Node* temp = (Tree_Node*)malloc(sizeof(Tree_Node));
       temp->data = data;
       temp->right = NULL;
       temp->left = NULL;
       *root = temp;
       return;
     } 
     else if (data < node->data){
      tree_insert(&node->left, data);
       
     }
     else {
       tree_insert(&node->right, data);
        }
     
     return;
}

Tree_Node* create_bst (char data[]){
    Tree_Node* root = NULL; 
    int size = strlen(data);
    for (int i = 0; i < size; i++) {
      tree_insert(&root, data[i]);
    }

    return root;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    if(root == NULL){
      return NULL;
    } else {
		if (data == root->data) {
			
			return root; 
		} else {
			if (data < root->data) {
				return tree_search(root->left, data);
			} else {
				return tree_search(root->right, data);
			}
		}
	}
     
}

void tree_print_sorted(Tree_Node* root){
  if(root!= NULL){
    tree_print_sorted(root->left);
    printf("%c", root->data);
    tree_print_sorted(root->right);
    
  }
  
}

void tree_delete(Tree_Node* currentNode){
    if(currentNode == NULL){
        return;
    }

    tree_delete(currentNode->left);
    tree_delete(currentNode->right);
    frees++;
    free(currentNode);
}

Tree_Node *root = NULL;

int main(){
  
char data[] = "FLOCCINAUCINIHILIPILIFICATION";
printf("Raw data:\n");
printf("%s", data);
printf("\n");
root = create_bst(data);
printf("\n");
printf("Sorted data:\n");
tree_print_sorted(root);
printf("\n");
tree_delete(root);
printf("tree has been deleted");

}
 
