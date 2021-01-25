#include<stdio.h>
#include<stdlib.h>

struct node{

	int data;
	struct node *left_child;
	struct node *right_child;
};

struct node *ROOT = NULL;

int insert_node(){

	int data;
	printf("Enter the value that must be inserted: ");
	scanf("%d", &data);

	struct node *newnode = malloc(sizeof(struct node));
	newnode->data = data;
	newnode->left_child = NULL;
	newnode->right_child = NULL;

	if(ROOT == NULL){
		ROOT = newnode;
		return 1;
	}else{
		struct node *temp;
		temp = ROOT;
		int flag = 0;

		while(flag == 0){
			if(newnode->data < temp->data){
				if(temp->left_child != NULL){
					temp = temp->left_child;
				}else{
					flag = 1;
				}
			}else if(newnode->data >= temp->data){
				if(temp->right_child != NULL){
					temp = temp->right_child;
				}else{
					flag = 1;
				}
			}
		}

		if(newnode->data < temp->data){
			temp->left_child = newnode;
		}else{
			temp->right_child = newnode;
		}
	}

	return 1;
}

int delete_node(){

	printf("Enter the element that has to be deleted: ");
	int data;
	scanf("%d", &data);

	struct node *temp, *parent;
	
	if(ROOT == NULL){
		printf("The tree is empty !\n");
		return 1;
	}else{
		temp = ROOT;
		parent = temp;
		int flag = 0;

		while(temp!= NULL){
			if(temp->data < data){
				
				parent = temp;
				temp = temp->right_child;
			}else if(temp->data > data){
				
				parent = temp;
				temp = temp->left_child;
			}else{

				/* 
				 * The node we are deleting can be of three types:-
				 * 1) The node has no child
				 * 2) The node has only one child
				 * 3) The node has two children
				 */

				if((temp->left_child == NULL) && (temp->right_child == NULL)){
					//leaf node case
					if(temp == ROOT){
						ROOT = NULL;
						free(temp);
						return 1;
					}
					if((parent->left_child != NULL) && (parent->left_child)->data == data){
						parent->left_child = NULL;
					}else{
						parent->right_child = NULL;
					}
					free(temp);
					return 1;
				
				}else if((temp->left_child == NULL) || (temp->right_child == NULL)){
					//node with one child
					if(temp == ROOT){
						ROOT = (temp->left_child == NULL)?temp->right_child:temp->left_child;
						free(temp);
						return 1;
					}
					if((parent->left_child != NULL) && ((parent->left_child)->data == data)){
						//node to be deleted is a left child
						if(temp->left_child != NULL){
							//patching parent node with the left child of the node to be destroyed
							parent->left_child = temp->left_child;
						}else{
							//patching parent node with the right child of the node to be destroyed
							parent->left_child = temp->right_child;
						}
					}else if((parent->right_child != NULL) && (parent->right_child)->data == data){
						//node to be deleted is a right child
						if(temp->left_child != NULL){
							//patching the parent node with the left child of the node to be destroyed
							parent->right_child = temp->left_child;
						}else{
							//patching the parent node with the right child of the node to be destroyed
							parent->right_child = temp->right_child;
						}
					}
					free(temp);
					return 1;

				}else{
					//node with two children
					struct node *newnode;
					struct node *parent_newnode;

					newnode = temp->right_child;
					parent_newnode = newnode;
					while(newnode->left_child != NULL){
						parent_newnode = newnode;
						newnode = newnode->left_child;
					}
					if(newnode == parent_newnode){
						temp->right_child = (newnode->right_child == NULL)?NULL:newnode->right_child;
					}
					parent_newnode->left_child = NULL;
					temp->data = newnode->data;
					free(newnode);
					return 1;
				}
			}
		}
	}

	return 1;
}

void preorder(struct node *current){

	//Data-Left-Right
	printf("%d\n", current->data);
	
	if(current->left_child != NULL){
		preorder(current->left_child);
	}

	if(current->right_child != NULL){
		preorder(current->right_child);
	}
	
}

void inorder(struct node *current){

	//Left-Data-Right
	if(current->left_child != NULL){
		inorder(current->left_child);
	}

	printf("%d\n", current->data);
	
	if(current->right_child != NULL){
		inorder(current->right_child);
	}
	

}

void postorder(struct node *current){

	//Left-Right-Data
	if(current->left_child != NULL){
		postorder(current->left_child);
	}

	if(current->right_child != NULL){
		postorder(current->right_child);
	}
	
	printf("%d\n", current->data);

}

int traverse_tree(){

	printf("How would you like to traverse the tree ? \n");
	printf("1. Pre-order Traversal\n");
	printf("2. In-order Traversal\n");
	printf("3. Post-order Traversal\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);

	if(ROOT == NULL){

		printf("The tree is empty\n");
	}else{
		
		switch(choice){
	
			case 1:
				preorder(ROOT);
				break;
			case 2:
				inorder(ROOT);
				break;
			case 3:
				postorder(ROOT);
				break;
			default:
				printf("Enter a valid choice !\n");
		}
	}

	return 1;
}

int search_node(){

	printf("Enter the element that must be searched: ");
	int data;
	scanf("%d", &data);

	int flag = 0;
	struct node *temp;
	if(ROOT == NULL){
		printf("The given tree is empty\n");
	}else{
		temp = ROOT;
		while(temp != NULL){
			if(temp->data > data){
				temp = temp->left_child;
			}
			else if(temp->data < data){
				temp = temp->right_child;
			}else{
				printf("The element %d has been found !\n", temp->data);
				flag = 1;
				break;
			}
		}
	}

	if(flag == 0){
		printf("The element has not been found\n");
	}

	return 1;
}

int frontend(){

	printf("******* MENU *******\n");
	printf("1. Enter an element\n");
	printf("2. Delete an element\n");
	printf("3. Traverse the tree\n");
	printf("4. Search for an element\n");
	printf("5. Exit\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);

	int retval;
	switch(choice){

		case 1: retval = insert_node();
			return retval;

		case 2: retval = delete_node();
			return retval;

		case 3: retval = traverse_tree();
			return retval;
		
		case 4:	retval = search_node();
			return retval;

		case 5: printf("Exiting the program...\n");
			return 0;

		default: printf("Enter a valid input !\n");
			 return 1;
	}
}

int main(int argc, char *argv[]){

	while(frontend())
		;

	return 1;
}
