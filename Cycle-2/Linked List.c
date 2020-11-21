#include<stdio.h>
#include<stdlib.h>

struct node* FRONT;

struct node{

	int data;
	struct node *link;
};

int insert_node_at_front(int element){

	struct node *new_node = malloc(sizeof(struct node));
	new_node->data = element;
	new_node->link = NULL;
	if(FRONT == NULL){
		/*Is the linked list empty ?
		 * If yes, this will be the first node in the linked list.
		 * So we set FRONT equal to the address of the new node.
		 */
		FRONT = new_node;
	}else{
		/* Is the linked list empty ?
		 * If not, then are two things to consider while inserting our node:- 
		 * 
		 * 1) FRONT is already pointing to some other node...and FRONT points to the
		 *    first node in a linked list. So once we are done with our insertion,
		 *    FRONT will have to end up pointing to our new node.
		 *
		 * 2) new_node->link is initially set to null... This can't be the case once
		 *    we're done with our insertion. new_node->link has to point to the current
		 *    first node.
		 */
		new_node->link = FRONT;
		FRONT = new_node;
	}
	return 1;
}

int insert_node_after_selected_node(int element){

	struct node *new_node = malloc(sizeof(struct node));
	new_node->data = element;
	new_node->link = NULL;

	if(FRONT == NULL){
		/*
		 * Is the linked list empty ?
		 * If yes, there is no node which we can find to place our new_node after.
		 * So we just insert our node at the beginning of the list and return
		 */
		FRONT = new_node;
		return 1;
	}else{

		printf("Enter the element after which this element must be inserted: ");
		int search_element;
		scanf("%d", &search_element);

		/*
		 * Is the linked list empty ?
		 * Apparently not. So we traverse through the linked list and search for
		 * the node containing the item after which we intend to insert our new node.
		 * Once the node containing the element we want is found, there are two
		 * memory operations to perform...first we set our new node's link to point to
		 * the link of the node that we just found out points to. Secondly, we change the
		 * link field of the previous node to point to our node.
		 */

		struct node *node_ptr = FRONT;
		while((node_ptr != NULL) && (node_ptr->data != search_element))
			node_ptr = node_ptr->link;
		new_node->link = node_ptr->link;
		node_ptr->link = new_node;
	}
	return 1;
}

int insert_node_at_rear(int element){

	struct node *new_node = malloc(sizeof(struct node));
	new_node->link = NULL;
	new_node->data = element;

	if(FRONT == NULL){
		/*
		 * Is the linked list empty ?
		 * If yes, there is no actual last node to check/find...
		 * We just insert our new node as the first element of the linked list, 
		 * and return a successful insertion.
		 */
		FRONT = new_node;
		return 1;

	}else{
	
		/*
		 * Is the linked list empty ?
		 * If not, then there actually exists a last node (or a rear node), behind
		 * which, we must insert our node...
		 * All we need to do is traverse through the linked list and once we find the
		 * last node, we just insert our node behind it by updating the last node's
		 * link field.
		 */
		struct node *node_ptr = FRONT;
		while(node_ptr->link != NULL)
			node_ptr = node_ptr->link;
		node_ptr->link = new_node;
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
		while((node_ptr != NULL)&&(node_ptr->data != element)){
			prev_node_ptr = node_ptr;
			node_ptr = node_ptr->link;
		}
		/*
		 * At this point, node_ptr stores the node that is going to be deleted.
		 * prev_node_ptr stores the node that is present before node_ptr.
		 */
		if(prev_node_ptr == node_ptr){
		
			/*
			 * This is for the case that the node we want to delete happens to
			 * be the first node itself...if thats the case, changing the prev_node_ptr
			 * link field means nothing... We need to update the FRONT variable of the
			 * linked list to enusre the deletion of the first node
			 */
			FRONT = node_ptr->link;
			return 1;
		}
		if(node_ptr != NULL){
			
			/*
			 * Okk, so the node to be deleted has been found....
			 * To delete we simply make the previous node's link field to point to the
			 * node after node_ptr... effectively this removes the node, pointed to by
			 * node_ptr, from the linked list
			 */
			prev_node_ptr->link = node_ptr->link;
		}
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
		while(node_ptr != NULL){
		
			printf("%d\t", node_ptr->data);
			node_ptr = node_ptr->link;
		}
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
	printf("1. Insert a node at the beginning of the list.\n");
	printf("2. Insert a node after a particular node in the list.\n");
	printf("3. Insert a node at the end of the list.\n");
	printf("4. Delete a node containing a particular item.\n");
	printf("5. Display the linked list.\n");
	printf("6. Exit the program.\n");
	printf("ENTER YOUR CHOICE: ");
	int choice;
	scanf("%d", &choice);
	
	int retval;
	switch(choice){
	
		case 1:{
				printf("Enter the value that must be inserted: ");
				int insert_value;
				scanf("%d", &insert_value);		
			        retval = insert_node_at_front(insert_value);		
			        return retval;
		       }        
		case 2:{        
		                
			        printf("Enter the value that must be inserted: ");
			        int insert_value;
			        scanf("%d", &insert_value);		
			        retval = insert_node_after_selected_node(insert_value);
			        return retval;
		       }
		case 3:{
		       
				printf("Enter the value that must be inserted: ");
				int insert_value;
				scanf("%d", &insert_value);		
			        retval = insert_node_at_rear(insert_value);
			        return retval;
		       }
		case 4:{
				printf("Enter the value that must be deleted: ");
				int delete_value;
				scanf("%d", &delete_value);		
			        retval = delete_node(delete_value);
			        return retval;
		       }
		case 5:{
		       		retval = display_list();
				return retval;
		       }
		case 6:{
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
