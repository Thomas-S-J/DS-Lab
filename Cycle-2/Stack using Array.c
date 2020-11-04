#include<stdio.h>
#include<stdlib.h>


int TOP = -1, MAXSIZE;

void 
push(int *stack, int element_to_be_pushed)
{
	if(TOP == MAXSIZE-1){
		printf("The element cannot be pushed into the stack as it is full.\n");
	}
	else{
		TOP++;
		stack[TOP] = element_to_be_pushed;
	}
}

void
pop(int *stack)
{
	if(TOP == -1){
		printf("The stack is empty. No element can be removed from the stack.\n");
	}
	else{
		int element_that_has_been_popped = stack[TOP];
		TOP--;
		printf("%d has been popped\n", element_that_has_been_popped);
	}
}

void 
display_stack(int *stack)
{
	
	if(TOP == -1){
		printf("The stack is empty, so there is nothing to display.\n");
	}
	else{
		printf("The stack currently looks like this:- \n");
		for(int i = TOP; i >= 0; i--){
			printf("| %d |\n|___|\n", stack[i]);
		}
	}
}

int 
main(int argc, char *argv[])
{

	printf("Enter the size of the stack that must be implemented: ");
	scanf("%d", &MAXSIZE);
	int *stack = malloc(sizeof(int)*MAXSIZE);
	while(1){
		printf("Enter the action that must be performed on stack:- \n");
		printf("1. PUSH elements\n");
		printf("2. POP elements\n");
		printf("3. DISPLAY stack\n");
		printf("4. EXIT PROGRAM\n");
		int choice;
		scanf("%d", &choice);
		switch(choice){
		
			case 1:{
					printf("Enter the element to be pushed into the stack: ");
					int element_to_be_pushed;
					scanf("%d", &element_to_be_pushed);
					push(stack, element_to_be_pushed);
					break;
			       }
			case 2:{
					pop(stack);
					break;
			       }
			case 3:{
					display_stack(stack);
					break;
			       }
			case 4:{
					exit(0);
					break;
			       }
			default:{
					printf("Enter a valid choice.\n");
				}
		}
	}
	return 0;
}
