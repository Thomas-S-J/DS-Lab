#include<stdio.h>
#include<stdlib.h>

//This structure is used to store the number of rows and columns associated with a matrix.
struct dimensions
{
	int rows;
	int columns;
};

//This function takes the address to a dimensions structure and writes into it the number of rows and columns the user wants.
//Since this function works call by reference no return is needed. Required values are written into the address pointed.
void
get_dimensions(struct dimensions *array)
{
	printf("Enter the value of rows: ");
	scanf("%d",&(array->rows));
	printf("Enter the number of columns: ");
	scanf("%d",&(array->columns));
}

//This function takes in the number of rows and columns and creates an empty array for us.
//It returns the base address of the created array.
int**
create_array(int rows, int columns)
{
	int** arr = (int**)malloc(sizeof(int)*rows);
	for(int i = 0;i < rows;i++){
		arr[i] = (int*)malloc(sizeof(int)*columns);
	}
	return arr;
}

//This function takes in the base address of the array and populates it.
//Since it writes directly into memory, it doesnt return any value.
void
fill_array(int **arr, int rows, int columns)
{

	printf("Enter the elements of array: \n");
	for(int i = 0;i < rows;i++){
		for(int j = 0;j < columns;j++){
			scanf("%d", &arr[i][j]);
		}
		printf("Row %d over\n",(i+1));
}
}

//This function takes in the base address of the array, the number of rows and columns and prints out the elements of the array.
//Since all it does is print elements, it does not return any values
void
display_array(int **arr, int rows, int columns)
{

	printf("The array is: \n");
	for(int i = 0;i < rows;i++){
		for(int j = 0;j < columns;j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

//This function takes in the base address of a normal 2D array and converts it into its sparse form
//It returns the base address of the newly created sparse array.
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

	int **sparse_array = malloc(sizeof(int *)*(count+1));
        sparse_array[0] = malloc(sizeof(int)*3);
	sparse_array[0][0] = arr.rows;
	sparse_array[0][1] = arr.columns;
	sparse_array[0][2] = count;
	int position = 1;
	//we need to start writing from index 1 onwards because the index 0 row is used to store the original array's metadata
	//we write all our data into arr[position]
	for(int i = 0;i < arr.rows;i++){
		for(int j = 0;j < arr.columns;j++){
			if(array[i][j] != 0){
				sparse_array[position] = malloc(sizeof(int)*3);
				sparse_array[position][0] = i;
				sparse_array[position][1] = j;
				sparse_array[position][2] = array[i][j];
				position++;
			}
		}
	}
	return sparse_array;
}

//This function takes in a sparse array and gets its transpose in sparse form
//It returns the transpose of the asked sparse array
int**
transpose_of_sparse_array(int** sparse_array)
{
	
	int rows = sparse_array[0][2];
	int** transpose_array = malloc(sizeof(int*)*(rows+1));
	transpose_array[0] = malloc(sizeof(int)*3);
	transpose_array[0][0] = sparse_array[0][1];
	transpose_array[0][1] = sparse_array[0][0];
	transpose_array[0][2] = sparse_array[0][2];
	for(int i = 1;i <= rows;i++){
		transpose_array[i] = malloc(sizeof(int)*3);
		transpose_array[i][0] = sparse_array[i][1];
		transpose_array[i][1] = sparse_array[i][0];
		transpose_array[i][2] = sparse_array[i][2];
	}
	return transpose_array;
}

//This function rebuilds the real array from its sparse form
//It returns a pointer to the base address of the array
int**
build_real_array(int** sparse_array)
{
	int rows = sparse_array[0][0];
	int columns = sparse_array[0][1];
	int non_zero_elements = sparse_array[0][2];

	int** arr = calloc(sizeof(int*),rows);
	for(int i = 0;i < rows;i++){
		arr[i] = calloc(sizeof(int),columns);
	}

	int write_row;
	int write_column;
	int write_value;
	for(int i = 1; i <= non_zero_elements; i++){
		write_row = sparse_array[i][0];
		write_column = sparse_array[i][1];
		write_value = sparse_array[i][2];
		arr[write_row][write_column] = write_value;
	}
	return arr;
}

//This function takes in the base address of a sparse array and displays it.
//Since it is only used to display, it returns no value.
void
display_sparse_array(int** sparse_array)
{
	
	int r = sparse_array[0][0];
	int c = sparse_array[0][1];
	int no_of_elements = sparse_array[0][2];
	for(int i = 0;i <= no_of_elements;i++){
		for(int j = 0;j < 3;j++){
			printf("%d ",sparse_array[i][j]);
		}
		printf("\n");
	}
}



int 
main(int argc, char* argv[])
{
	//Create and fill array

	//getting dimensions of the array
	struct dimensions array;
	get_dimensions(&array);
	//Declaring array 
	int **arr = create_array(array.rows,array.columns);
	fill_array(arr,array.rows,array.columns);
	display_array(arr,array.rows,array.columns);
	
	//Finished creating array
	
	//Converting a given array into its sparse form
	int **sparse_array = array_to_sparse(arr,array);
	
	//Displaying the sparse array
	printf("The sparse form of the given array is:\n");
	display_sparse_array(sparse_array);

	printf("The sparse form of the transpose of the given array is:\n");
	int** transpose_sparse = transpose_of_sparse_array(sparse_array);
	display_sparse_array(transpose_sparse);

	int** recreated_array = build_real_array(transpose_sparse);
	display_array(recreated_array,array.columns,array.rows);
	return 0;
}
