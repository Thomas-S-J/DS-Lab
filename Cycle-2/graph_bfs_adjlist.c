#include<stdio.h>
#include<stdlib.h>

struct vertex{

	int data;
	struct vertex *next;
};

struct vertex **adj_list = NULL; //adjacency list
int *visited = NULL; //to check if a node has been visited or not
int *queue = NULL; 
int FRONT = -1, REAR = -1;
int n_vertices = 0; //no of vertices

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

struct vertex* create_vertex(int data){

	struct vertex* new_vertex = malloc(sizeof(struct vertex));
	new_vertex->data = data;
	new_vertex->next = NULL;
	return new_vertex;
}

void create_graph(int vertices){

	n_vertices = vertices;
	adj_list = malloc(n_vertices*(sizeof(struct vertex*)));

	for(int i = 0; i < vertices; i++){
		adj_list[i] = NULL;
	}

	return;
}

void add_edge(int src, int dest){

	//add edge from src to dest
	struct vertex *new_vertex = create_vertex(dest);
	new_vertex->next = adj_list[src];
	adj_list[src] = new_vertex;

	// add edge from dest to src
	new_vertex = create_vertex(src);
	new_vertex->next = adj_list[dest];
	adj_list[dest] = new_vertex;

	return;
}

int print_graph(){

	if(adj_list == NULL){
		printf("The graph is empty\n");
	}

	for(int vertices = 0; vertices < n_vertices; vertices++){

		struct vertex *temp = adj_list[vertices];
		printf("Neighbours of vertex %d are:-\n", vertices);
		if(temp == NULL){
			printf("No neighbours");
		}
		while(temp){
			printf("%d\t", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}

	return 1;
}

int breadth_first_search(){

	if(adj_list == NULL){
		printf("The graph is empty\n");
		return 1;
	}

	visited = calloc(sizeof(int), n_vertices);
	queue = calloc(sizeof(int), n_vertices);
	enqueue(0);
	visited[0] = 1;

	while(!isEmpty()){
		int data = dequeue();
		printf("%d\t", data);
		
		struct vertex* neighbours = adj_list[data];
		while(neighbours != NULL){
			if(!visited[neighbours->data]){
				enqueue(neighbours->data);
				visited[neighbours->data] = 1;
			}
			neighbours = neighbours->next;
		}
	}

	printf("\n");

	return 1;
	
}

int insert(){

	printf("Enter the number of elements in the graph: ");
	int n_vertices;
	scanf("%d", &n_vertices);

	if(n_vertices <= 0){
		printf("Enter a valid size !\n");
		return 1;
	}
	create_graph(n_vertices);
	
	int data;
	printf("The nodes that have been created are: \n");
	for(int i = 0; i < n_vertices; i++){
		printf("%d\t", i);
	}
	printf("\n");

	char choice;
	printf("Now enter the neighbours of the nodes:-\n");
	for(int i = 0; i < n_vertices; i++){
		for(int j = i+1; j < n_vertices; j++){
			printf("Is %d a neighbour of %d [y/n] ? ", i, j);
			scanf(" %c", &choice);
			if(choice == 'y'){
				add_edge(i, j);
			}else{
				if(choice != 'n')
					printf("Invalid choice. Assuming not neighbour\n");
			}
		}
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

int main(){

	while(frontend())
		;

	return 1;
}
