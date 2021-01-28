#include<stdio.h>
#include<stdlib.h>

int **adj_arr = NULL;
int n_vertices = 0;
int *queue = NULL;
int FRONT = -1, REAR  = -1;
int *visited = NULL;

int isEmpty(){

	if(FRONT == -1){
		return 1;
	}
	return 0;
}

void enqueue(int data){

	if(REAR == n_vertices-1){
		return;
	}

	if(FRONT == -1){
		FRONT++;
	}
	REAR++;
	queue[REAR] = data;
	return;
}

int dequeue(){

	if(FRONT == -1){
		return -1;
	}

	int data;
	data = queue[FRONT];
	if(FRONT == REAR){
		FRONT = -1;
		REAR = -1;
	}else{
		FRONT++;
	}
	return data;
}

int insert(){

	printf("Enter the number of nodes: ");
	scanf("%d", &n_vertices);

	if(n_vertices <= 0){
		printf("Enter a valid size !\n");
		return 1;
	}

	adj_arr = malloc(sizeof(int*)*n_vertices);
	queue = calloc(sizeof(int), n_vertices);
	visited = calloc(sizeof(int), n_vertices);

	printf("The nodes that have been created are:-\n");
	for(int i = 0; i < n_vertices; i++){
		printf("%d\t", i);
		adj_arr[i] = calloc(sizeof(int),n_vertices);
	}
	printf("\n");

	char is_neighbour;
	printf("Enter the neighbours of the nodes:- \n");
	for(int i = 0; i < n_vertices; i++){
		for(int j = i+1; j < n_vertices; j++){
			printf("Is %d a neighbour of %d [y/n] ? ", i, j);
			scanf(" %c", &is_neighbour);
			if(is_neighbour == 'y'){
				adj_arr[i][j] = 1;
				adj_arr[j][i] = 1;
			}
		}
	}
}

int breadth_first_search(){

	if(adj_arr == NULL){
		printf("The graph is empty\n");
		return 1;
	}

	//starting traversal from 0
	//pushing 0 into queue and marking it as read
	enqueue(0);
	visited[0] = 1;

	while(!isEmpty()){
		int data = dequeue();
		printf("%d\t", data);
		for(int i = 0; i < n_vertices; i++){
				if(adj_arr[data][i] != 0 && !visited[i]){
					enqueue(i);
					visited[i] = 1;
				}
		}
	}
	printf("\n");
	return 1;
}

int print_graph(){

	if(adj_arr == NULL){
		printf("The graph is empty\n");
	}

	for(int i = 0; i < n_vertices; i++){
		printf("The neighbours of %d are:-\n", i);

		for(int j = 0; j < n_vertices; j++){
			if(adj_arr[i][j] != 0){
				printf("%d\t", j);
			}
		}

		printf("\n");
	}

	return 1;
}

int frontend(){

	printf("******* MENU *******\n");
	printf("1. Insert elements\n");
	printf("2. Breadth first search\n");
	printf("3. Display the graph\n");
	printf("4. Exit the program\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);

	int retval = 0;

	switch(choice){
		case 1:
			retval = insert();
			return retval;
			;
		case 2:
			retval = breadth_first_search();
			return retval;
		case 3:
			retval = print_graph();
			return retval;
		case 4:
			retval = 0;
			return retval;
		default:
			printf("Enter a valid input !\n");
			return 1;
	}
	return 1;
}

int main(int argc, char* argv[]){

	while(frontend())
		;

	return 1;
}
