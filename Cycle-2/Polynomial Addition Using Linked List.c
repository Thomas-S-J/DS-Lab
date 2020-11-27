/*
 * Program to add two polynomials using linked lists.
 * This program is built on the original linked list program made earlier.
 */

#include<stdio.h>
#include<stdlib.h>

char *message;

struct node{

	int coefficient;
	int exponent;
	struct node *link;
};

int insert_node_at_rear(struct node** FRONT, int coefficient, int exponent){

	struct node *new_node = malloc(sizeof(struct node));
	new_node->link = NULL;
	new_node->coefficient = coefficient;
	new_node->exponent = exponent;

	if(*FRONT == NULL){
		
		/*
		 * Is the linked list empty ?
		 * If yes, there is no actual last node to check/find...
		 * We just insert our new node as the first element of the linked list, 
		 * and return a successful insertion.
		 */
		*FRONT = new_node;
		return 1;

	}else{
	
		/*
		 * Is the linked list empty ?
		 * If not, then there actually exists a last node (or a rear node), behind
		 * which, we must insert our node...
		 * All we need to do is traverse through the linked list and once we find the
		 * last node, we just inert our node behind it by updating the last node's
		 * link field.
		 */
		struct node *node_ptr = *FRONT;
		while(node_ptr->link != NULL)
			node_ptr = node_ptr->link;

		node_ptr->link = new_node;
	}
	return 1;
}

int display_list(struct node **FRONT){

	if(*FRONT == NULL){
	
		printf("Nothing to display.\n");
	}else{
		/*
		 * Just traverse through the linked list and print the individual terms.
		 */
	
		struct node *node_ptr = *FRONT;
		printf("%s: -\n", message);
		while(node_ptr != NULL){
		
			printf("%+dx^%d\t", node_ptr->coefficient, node_ptr->exponent);
			node_ptr = node_ptr->link;
		}
		printf("\n");
	}
	return 1;
}

int get_polynomial(struct node** FRONT){

	/*
	 * This function asks the user for the highest power of
	 * the polynomial (say n), and creates a linked list with (n+1)
	 * nodes to store the polynomial (n for the power terms, and 1
	 * for the constant).
	 *
	 * Each node of the linked list stores a term of the polynomial.
	 * For example, take the following polynomial:-
	 * 	
	 * 			4x^3 + 5x +7
	 *
	 * We store this polynomial as a LL in the following manner:-
	 *
	 *  FRONT -----> (4,3,link) -----> (5,1,link) -----> (7,0,NULL)
	 *
	 * Note: We dont store terms having zero as a coefficient... Doing
	 *       so would just be a waste of memory. Instead we write code
	 *       to make sure that while we add, we are adding terms having
	 *       the same exponent.
	 *
	 */
	printf("Enter the power of the polynomial: ");
	int power;
	scanf("%d", &power);

	int coefficient;
	for(int exponent = power; exponent >= 0; exponent--){
	
		printf("Enter the coefficient of x^%d: ", exponent);
		scanf("%d", &coefficient);

		if(coefficient != 0){
		
			insert_node_at_rear(FRONT, coefficient, exponent);
		}

	}

	return 1;
}

int add_polynomials(struct node **FRONT1, struct node **FRONT2, struct node **FRONT_SUM){

	struct node *node_ptr1 = *FRONT1, *node_ptr2 = *FRONT2, *node_ptr3 = *FRONT_SUM;

	/*
	 * To add the polynomials, we traverse through both the
	 * polynomials, from the first node, containing its highest
	 * power to its last node, containing its lowest power.
	 *
	 * We then compare the powers on each individual node, and then
	 * do the appropriate steps, as shown in code.
	 */
	if(!(node_ptr1 && node_ptr2)){

		if(!node_ptr1)
			*FRONT_SUM = *FRONT2;
		else
			*FRONT_SUM = *FRONT1;
		return 1;
	}

	while(node_ptr1 || node_ptr2){
	
		if(node_ptr1->exponent > node_ptr2->exponent){
			insert_node_at_rear(FRONT_SUM, node_ptr1->coefficient, node_ptr1->exponent);
			node_ptr1 = node_ptr1->link;
		}
		else if(node_ptr1->exponent < node_ptr2->exponent){
			insert_node_at_rear(FRONT_SUM, node_ptr2->coefficient, node_ptr2->exponent);
			node_ptr2 = node_ptr2->link;
		}
		else if(node_ptr1->exponent == node_ptr2->exponent){
			int sum_of_coefficients = node_ptr1->coefficient + node_ptr2->coefficient;
			insert_node_at_rear(FRONT_SUM, sum_of_coefficients, node_ptr1->exponent);
			node_ptr1 = node_ptr1->link;
			node_ptr2 = node_ptr2->link;
		}
	}
 	/* 
	 * This piece of code handles the case where both the polynomials have different
         * ending powers. For example, 
         *      
         *      2x + 1  && x  : are two polynomials whose least powers are same.
         */
        if(node_ptr1 || node_ptr2){

                if(node_ptr2){

                        while(node_ptr2 != NULL){

                                insert_node_at_rear(FRONT_SUM, node_ptr2->coefficient, node_ptr2->exponent);
                                node_ptr2 = node_ptr2->link;
                        }
                }
                else if(node_ptr1){

                        while(node_ptr1 != NULL){

                                insert_node_at_rear(FRONT_SUM, node_ptr1->coefficient, node_ptr1->exponent);
                                node_ptr1= node_ptr1->link;
                        }
                }
        }

	return 1;
}

int terminate(){

	printf("%s\n", message);
	return 0;
}

int frontend(){

	static struct node *FRONT1 = NULL, *FRONT2 = NULL, *FRONT_SUM = NULL;

	printf("********** MENU **********\n");
	printf("1. Enter polynomial 1\n");
	printf("2. Enter polynomial 2.\n");
	printf("3. Add the polynomials.\n");
	printf("4. Display polynomial 1.\n");
	printf("5. Display polynomial 2.\n");
	printf("6. Display the sum of polynomials.\n");
	printf("7. Exit the program.\n");
	printf("ENTER YOUR CHOICE: ");
	int choice;
	scanf("%d", &choice);
	
	enum{
	
		ENTER_POLYNOMIAL1 = 1,
		ENTER_POLYNOMIAL2,
		ADD_POLYNOMIALS,
		DISPLAY_POLYNOMIAL1,
		DISPLAY_POLYNOMIAL2,
		DISPLAY_SUM,
		EXIT,
	};
	int retval;
	switch(choice){
	
		case ENTER_POLYNOMIAL1:
			{		
			        FRONT1 = NULL;
				retval = get_polynomial(&FRONT1);		
			        return retval;
		       }        
		case ENTER_POLYNOMIAL2:
			{
				FRONT2 = NULL;	
			        retval = get_polynomial(&FRONT2);
			        return retval;
		       }
		case ADD_POLYNOMIALS:
			{	
			        FRONT_SUM = NULL;
				retval = add_polynomials(&FRONT1, &FRONT2, &FRONT_SUM);
			        return retval;
		       }
		case DISPLAY_POLYNOMIAL1:
			{		
			        message = "Polynomial 1 is:- ";
				retval = display_list(&FRONT1);
			        return retval;
		       }
		case DISPLAY_POLYNOMIAL2:
			{
				message = "Polynomial 2 is:- ";
		       		retval = display_list(&FRONT2);
				return retval;
		       }
		case DISPLAY_SUM:
			{
				message = "Sum of polynomials is:-";
			        retval = display_list(&FRONT_SUM);
			        return retval;
		       }
		case EXIT:
			{
				message = "Goodbye...";
				retval = terminate();
				return retval;
			}
		default:{
				printf("Enter a valid input.\n");
				return 1;
			
			}

	}
	return 0;
}

int main(int argc, char *argv[]){


	while(frontend())
		;

	return 0;
}
