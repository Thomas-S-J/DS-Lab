#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int FRONT = -1, REAR = -1, SIZE;

bool isFull(){

	if((REAR+1)%SIZE == FRONT)
		return true;

	return false;
}

bool isEmpty(){

	if(FRONT == -1 && REAR == -1)
		return true;

	return false;
}

void enqueue_front(int *deque, int element){

	if(isFull()){
	
		printf("Queue is full.\n");
	}else{
		if(isEmpty()){
		
			FRONT = 0;
			REAR = 0;
			deque[FRONT] = element;
		}else{
		
			FRONT = (FRONT+SIZE-1)%SIZE;
			deque[FRONT] = element;
		}

	}
}

void enqueue_rear(int *deque, int element){

	if(isFull()){
	
		printf("Queue is full.\n");
	}else{
	
		if(isEmpty()){
		
			FRONT = 0;
			REAR = 0;
		}else{
			REAR = (REAR+1)%SIZE;
		}
		deque[REAR] = element;
	}
}

void deque_front(int *deque){

	if(isEmpty()){
	
		printf("Queue is empty.\n");
	}else{
		
		int deleted_element = deque[FRONT];
		if(FRONT == REAR){
		
			FRONT = -1;
			REAR = -1;
		}else{
		
			FRONT = (FRONT+1)%SIZE;
		}

		printf("The deleted element is %d.\n", deleted_element);

	}
}

void deque_rear(int *deque){

	if(isEmpty()){
	
		printf("Queue is empty.\n");
	}else{
	
		int deleted_element = deque[REAR];
		if(FRONT == REAR){
		
			FRONT = -1;
			REAR = -1;
		}else{
		
			REAR = (REAR+SIZE-1)%SIZE;
		}
		printf("The deleted element is %d", deleted_element);
	}
}

void display_queue(int *deque){

	if(isEmpty()){
	
		printf("The queue is empty.\n");
	}else{
	
		for(int i = FRONT; i != REAR; i = (i+1)%SIZE){
		
			printf("%d\t", deque[i]);
		}
		printf("%d\n", deque[REAR]);
	}
}

int main(int argc, char *argv[]){

	int choice, element;
	int *deque = malloc(sizeof(int)*64);
	printf("Enter the size of the deque to be implemented: ");
	scanf("%d", &SIZE);

	do{
		printf("-----MENU-----\n");
		printf("1. Enqueue at the front of the queue\n");
		printf("2. Enqueue at the end of the queue\n");
		printf("3. Dequeue at the front of the queue\n");
		printf("4. Dequeue at the end of the queue\n");
		printf("5. Display the queue\n");
		printf("6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
	
		switch(choice){
		
			case 1:{
				       printf("Enter the element that must be inserted to queue: ");
				       scanf("%d", &element);
				       enqueue_front(deque, element);
				       break;
			       }
			case 2:{
				       printf("Enter the element that must be inserted to queue: ");
				       scanf("%d", &element);
				       enqueue_rear(deque, element);
				       break;
			       }
			case 3:{
				       deque_front(deque);
				       break;
			       }
			case 4:{
				       deque_rear(deque);
				       break;
			       }
			case 5:{
				       display_queue(deque);
				       break;
			       }
			case 6:{
				       printf("Goodbye...\n");
				       exit(0);
			       }
			default:{
				
					printf("Enter a valid input.\n");
				}
	
		}
	}
	while(true);

	return 0;
}
