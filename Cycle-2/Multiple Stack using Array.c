#include<stdio.h>
#include<stdlib.h>

int MAXSIZE, TOP1 = -1, TOP2 = -1;
int *actual_stack, *stack1, *stack2;

void
push(int *stack, int item)
{

	int flag = 0;
	if(stack == stack1){
		if(((TOP1 + 1) < TOP2) && (TOP1 != MAXSIZE-1)){
			stack1[++TOP1] = item;
			flag = 1;
		}
	}
	else{
		if(((TOP2 -1) > TOP1) && (TOP2 != 0)){
			stack2[--TOP2] = item;
			flag = 1;
		}
	}
	if(flag == 0){
		printf("Element cannot be pushed into the stack.\n");
	}
}

void
pop(int *stack)
{

	int data, flag = 0;
	if(stack == stack1){
		if(TOP1 == -1){
			printf("The stack is empty and hence no element can be popped.\n");
		}
		else{
			data = stack1[TOP1];
			TOP1--;
			flag = 1;
		}
	}
	if(stack == stack2){
		if(TOP2 == MAXSIZE){
			printf("The stack is empty and hence no element can be popped.\n");
		}
		else{
			data = stack2[TOP2];
			TOP2++;
			flag = 1;
		}
	}
	if(flag == 1){
		flag = 0;
		printf("The element that has been popped is: %d\n", data);
	}

}

void
display(int *stack)
{

	if(stack == stack1){
		if(TOP1 == -1){
			printf("The stack is empty, so there is nothing to display.\n");
		}
		else{
			for(int i = TOP1;i >= 0;i--){
				printf("%d\n", stack1[i]);
			}
		}
	}
	if(stack == stack2){
		if(TOP2 == MAXSIZE){
			printf("The stack is empty, so there is nothing to display.\n");
		}
		else{
			for(int i = TOP2;i < MAXSIZE;i++){
				printf("%d\n", stack2[i]);
			}
		}
	}
}

void
main(int argc, char *argv[])
{
	printf("Enter the maximum size of the stack that must be implemented: ");
	scanf("%d", &MAXSIZE);
	TOP2 = MAXSIZE;
	actual_stack = malloc(sizeof(int)*MAXSIZE);
	stack1 = actual_stack;
       	stack2 = &actual_stack[MAXSIZE-1];

	int choice;
	while(1){
		printf("1. PUSH elements into the stack\n");
		printf("2. POP elements from the stack\n");
		printf("3. DISPLAY elements of the stack\n");
		printf("4. EXIT the program\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		 switch(choice){
		 
			 case 1:{
					int data;
					printf("Enter the number that must be pushed into the stack: ");
					scanf("%d", &data);
					printf("Enter the stack number the element must be pushed into (1 or 2): ");
					int stack_number;
					scanf("%d", &stack_number);
					if(stack_number == 1){
						push(stack1, data);
					}
					else if(stack_number == 2){
						push(stack2, data);
					}
					else{
						printf("Enter a valid stack number\n");
					}
					break;
				}
			case 2:{
					printf("Enter the stack number on which popping must be performed (1 or 2): ");
					int stack_number;
					scanf("%d", &stack_number);
					if(stack_number == 1){
						pop(stack1);
					}
					else if(stack_number == 2){
						pop(stack2);
					}
					else{
						printf("Enter a valid stack number\n");
					}
					break;

			       }
			case 3:{
					printf("Enter the stack number the element must be displayed (1 or 2): ");
					int stack_number;
					scanf("%d", &stack_number);
					if(stack_number == 1){
						display(stack1);
					}
					else if(stack_number == 2){
						display(stack2);
					}
					else{
						printf("Enter a valid stack number\n");
					}
					break;
			       }
			case 4:{
			       		printf("EXITING THE PROGRAM...\n");	
				        exit(0);
			       }
			default:{
					printf("Enter a valid choice\n");
				}
		 }
	}
}
