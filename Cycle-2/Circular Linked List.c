#include<stdio.h>
#include<stdlib.h>

struct node* FRONT;

struct node{

	int data;
	struct node *link;
};

/*
 * This program implements the circular list using a singly linked list.
 *
 * Operations performed on circular linked list:-
 * 1. Insert node.
 * 2. Delete node.
 * 3. Display list.
 */

int insert_node(int element){

	/*
	 * Function to add a node after a particular element.
	 */

	struct node *new_node = malloc(sizeof(struct node));
	new_node->data = element;
	new_node->link = new_node;

	if(FRONT == NULL){
		/*
		 * If the list is empty, there is no node after which we can insert
		 * the new node. So we insert the new node as the first element of
		 * the circular linked list and return to the caller.
		 */
		FRONT = new_node;
		return 1;
	}else{

		printf("Enter the element after which this element must be inserted: ");
		int search_element;
		scanf("%d", &search_element);

		/*
		 * So the list is not empty and our node must be inserted after a
		 * particular node in the list. 
		 * We first traverse through the list, to search for the node containing
		 * the given element (our new node will be inserted after this node).
		 * Then we perform the actual insertion operation.
		 */

		struct node *node_ptr = FRONT;
		while((node_ptr->link != FRONT) && (node_ptr->data != search_element))
			node_ptr = node_ptr->link;
		/*
		 * We have to deal with either of the two cases:-
		 * 1) The node was not found. Even after traversing through all the elements
		 *    the required node wasnt found.
		 *  2) The node was found and node_ptr is pointing to it now.
		 */

		if(node_ptr->data == search_element){
			 
			/*
			 * If control reaches here, the node has been found and its the node
			 * after which insertion must occur.
			 */
			new_node->link = node_ptr->link;
			node_ptr->link = new_node;
		}
	}
	return 1;
}

int delete_node(int element){

	if(FRONT == NULL){
	
		/*
		 * If the linked list is empty, there is no node to delete...we just
		 * print out that the list is empty and return to the calling function.
		 */

		printf("The list is empty...there are no nodes to delete.\n");
	}else{

		/*
		 * Okk, so the linked list is not empty... So we need to traverse through
		 * the linked list node by node and find out the node to delete.
		 */
		struct node *node_ptr = FRONT;
		struct node *prev_node_ptr = FRONT;
		while((node_ptr->link != FRONT) && (node_ptr->data != element)){
			prev_node_ptr = node_ptr;
			node_ptr = node_ptr->link;
		}

		if(node_ptr->data != element)
			return 1;

		/*
		 * At this point, node_ptr stores the node that is going to be deleted.
		 * prev_node_ptr stores the node that is present before node_ptr.
		 *
		 * To delete we simply make the previous node's link field to point to the
		 * node after node_ptr... effectively this removes the node, pointed to by
		 * node_ptr, from the linked list.
		 */

		if(node_ptr == FRONT){
		
			/*
			 * This happens for two cases:-
			 * 1) There is only one node in the list, and we want to delete that.
			 * 2) We want to delete the first node of the list. 
			 */
			if(node_ptr->link == node_ptr){
			
				FRONT = NULL;
			}
			else{	
				while(prev_node_ptr->link != FRONT)
					prev_node_ptr = prev_node_ptr->link;
				prev_node_ptr->link = node_ptr->link;
				FRONT = node_ptr->link;
			}
			return 1;
		}

		prev_node_ptr->link = node_ptr->link;
		free(node_ptr);
	}
	return 1;
}

int display_list(){

	if(FRONT == NULL){
	
		printf("The list is empty...there are no nodes to display.\n");
	}else{
		/*
		 * Just traverse through the linked list and print the data fields.
		 */
	
		struct node *node_ptr = FRONT;
		printf("THE LINKED LIST IS: -\n");	
		do{
			
			printf("%d\t", node_ptr->data);
			node_ptr = node_ptr->link;
		}while(node_ptr != FRONT);
		
		printf("\n");
	}
	return 1;
}

int terminate(){

	printf("Good bye...\n");
	return 0;
}

int frontend(){

	printf("********** MENU **********\n");
	printf("1. Insert a node after a particular node in the list.\n");
	printf("2. Delete a node containing a particular item.\n");
	printf("3. Display the linked list.\n");
	printf("4. Exit the program.\n");
	printf("ENTER YOUR CHOICE: ");
	int choice;
	scanf("%d", &choice);
	
	int retval;
	switch(choice){
	
		case 1:{        
		                
			        printf("Enter the value that must be inserted: ");
			        int insert_value;
			        scanf("%d", &insert_value);		
			        retval = insert_node(insert_value);
			        return retval;
		       }
		case 2:{
				printf("Enter the value that must be deleted: ");
				int delete_value;
				scanf("%d", &delete_value);		
			        retval = delete_node(delete_value);
			        return retval;
		       }
		case 3:{
		       		retval = display_list();
				return retval;
		       }
		case 4:{
			        retval = terminate();
			        return retval;
		       }
		default:{
				printf("Enter a valid input.\n");
				break;
			
			}

	}
	return 0;
}

int main(int argc, char *argv[]){


	while(frontend())
		;

	return 0;
}
