/*
 * 11th October 2020 <Author: S J Thomas>
 * Program to add two sparse arrays
 * This program takes in two arrays, converts it into its sparse form and adds them
 */

#include<stdio.h>
#include<stdlib.h>

//Each array will have its own dimensions structure to store its dimensions
struct dimensions
{
	int rows;
	int columns;
};

//This functions writes the dimensions of the array into its dimension structure
void
get_dimensions(struct dimensions *array)
{
	printf("Enter the value of rows: ");
	scanf("%d",&(array->rows));
	printf("Enter the number of columns: ");
	scanf("%d",&(array->columns));
}

//This function will create an array of required size (as specified in struct dimensions)
int**
create_array(struct dimensions array)
{
	int** arr = malloc(sizeof(int*)*array.rows);
	for(int i = 0;i < array.rows;i++){
		arr[i] = malloc(sizeof(int)*array.columns);
	}
	return arr;
}

//This function will populate the given array
void
fill_array(int **arr, struct dimensions array)
{

	printf("Enter the elements of array: \n");
	for(int i = 0;i < array.rows;i++){
		printf("Enter row %d\n",(i+1));
		for(int j = 0;j < array.columns;j++){
			scanf("%d", &arr[i][j]);
		}
		printf("Row %d over\n",(i+1));
	}
}

//This function is used to display the given array on screen
void
display_array(int **arr, struct dimensions array)
{

	printf("The elements of the array: \n");
	for(int i = 0;i < array.rows;i++){
		for(int j = 0;j < array.columns;j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

//This function converts the given array into its sparse form
int**
array_to_sparse(int **array, struct dimensions arr)
{
	
	int count = 0;
	for(int i = 0;i < arr.rows;i++){
		for(int j = 0;j < arr.columns;j++){
			if(array[i][j] != 0){
				count++;
			}	
		}
	}

	int **sparse_array = malloc(sizeof(int*)*(count+1));
        sparse_array[0] = malloc(sizeof(int)*3);
	sparse_array[0][0] = arr.rows;
	sparse_array[0][1] = arr.columns;
	sparse_array[0][2] = count;
	int position = 1;
	//we need to start writing from index 1 onwards because the index 0 row is used to store the original array's metadata
	for(int i = 0;i < arr.rows;i++){
		for(int j = 0;j < arr.columns;j++){
			if(array[i][j] != 0){
				sparse_array[position] = malloc(sizeof(int)*3);
				sparse_array[position][0] = i+1;
				sparse_array[position][1] = j+1;
				sparse_array[position][2] = array[i][j];
				position++;
			}
		}
	}
	return sparse_array;
}

void
display_sparse_array(int** sparse_array)
{
	
	int rows = sparse_array[0][0];
	int columns = sparse_array[0][1];
	int no_of_elements = sparse_array[0][2];
	for(int i = 0;i <= no_of_elements;i++){
		for(int j = 0;j < 3;j++){
			printf("%d ",sparse_array[i][j]);
		}
		printf("\n");
	}
}
//This function takes in two 1-D arrays of size 3 and compares the value it stores
// This function will return NULL if both arrays are exactly same (first and second elements only)
int* 
findLesser(int array1[3], int array2[3])
{
	if(array1[0] < array2[0]){
		return array1;
	}
	else if(array2[0] < array1[0]){
		return array2;
	}
	else{
		if(array1[1] < array2[1]){
			return array1;
		}
		else if(array2[1] < array1[1]){
			return array2;
		}
	}
	return NULL;
}

int**
add_sparse_arrays(int** array1, int** array2)
{

	int** sum_array = malloc(sizeof(int*)*(array1[0][2]+array2[0][2]+1));
	int belay1 = 1, belay2 = 1,sum_belay = 1;
	sum_array[0] = malloc(sizeof(int)*3);
	sum_array[0][0] = array1[0][0];
	sum_array[0][1] = array1[0][1];

	while(belay1 <= array1[0][2] || belay2 <= array2[0][2]){
		int* write_head = findLesser(array1[belay1], array2[belay2]);
		sum_array[sum_belay] = malloc(sizeof(int)*3);
		if(write_head == NULL){
			sum_array[sum_belay][0] = array1[belay1][0];
			sum_array[sum_belay][1] = array1[belay1][1];
			sum_array[sum_belay][2] = array1[belay1][2] + array2[belay2][2];
			belay1++;
			belay2++;
		}
		else{
			sum_array[sum_belay][0] = write_head[0];
			sum_array[sum_belay][1] = write_head[1];
			sum_array[sum_belay][2] = write_head[2];
			if(write_head == *array1){
				belay1++;
			}
			else{
				belay2++;
			}
		}
		sum_belay++;
	}
	sum_array[0][2] = sum_belay-1;
	sum_array = realloc(sum_array,sum_belay*sizeof(int*));
	return sum_array;
}


int 
main(int argc, char* argv[])
{
	//Create and populate array 1
	struct dimensions array1;
	get_dimensions(&array1);
	int **arr1 = create_array(array1);
	fill_array(arr1,array1);
	display_array(arr1,array1);
	

	//Create and populate array 2
	struct dimensions array2;
	get_dimensions(&array2);
	int **arr2 = create_array(array2);
	fill_array(arr2,array2);
	display_array(arr2,array2);
	
	//Converting a given array into its sparse form
	int **sparse_array1 = array_to_sparse(arr1,array1);
	int **sparse_array2 = array_to_sparse(arr2,array2);
	
	//Displaying the sparse array
	display_sparse_array(sparse_array1);
	display_sparse_array(sparse_array2);

	printf("The sum of the two arrays is:\n");
	int **array_sum = add_sparse_arrays(sparse_array1, sparse_array2);
	display_sparse_array(array_sum);
	return 0;
}
