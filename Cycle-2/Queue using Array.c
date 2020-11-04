#include<stdio.h>
#include<stdlib.h>

int FRONT = 0, REAR = -1, MAXSIZE = 0;

int
isfull()
{

	if(REAR == MAXSIZE - 1){
		return 1;
	}
		return 0;
}

int
isempty()
{

	if(FRONT < 0 || FRONT > REAR){
		return 1;
	}
	return 0;
}

void
enqueue(int *queue, int data)
{

	if(isfull()){
		printf("The queue is full. No more elements can be added.\n");
	}

	else{
		REAR++;
		queue[REAR] = data;
	}
}

void
dequeue(int *queue)
{

	if(isempty()){
		printf("The queue is empty. No element can be removed\n");
	}
	else{
		int data = queue[FRONT];
		FRONT++;
		printf("The element that has been removed is %d.\n", data);

	}
}

void
display_queue(int* queue)
{

	if(isempty()){
		printf("The queue is empty. There is nothing to print.\n");
	}
	for(int i = FRONT;i <= REAR; i++){
		printf("%d ", queue[i]);
	}
	printf("\n");
}

int
main(int argc, char *argv[])
{

	printf("Enter the size of the queue to be implemented: ");
	scanf("%d", &MAXSIZE);
	int *queue = malloc(sizeof(int)*MAXSIZE);
	
	int choice;
	while(1){
		printf("Enter your choice\n");
		printf("1. Enter elements into the queue\n");
		printf("2. Remove an element from the queue\n");
		printf("3. Display the queue\n");
		printf("4. Exit the program\n");
		scanf("%d", &choice);

		switch(choice){
		
			case 1:{
				       int element_that_must_be_added_to_queue;
				       printf("Enter the element that must be added to queue: ");
				       scanf("%d", &element_that_must_be_added_to_queue);
				       enqueue(queue, element_that_must_be_added_to_queue);
				       break;
			       }
			case 2:{
			       		dequeue(queue);
					break;
			       }
			case 3:{
			          	display_queue(queue);
					break;
			       }
			case 4:{
				        exit(0);
			       }
			default:{
					printf("Enter a valid choice.\n");
					break;
				}
	
		}
	}

}
