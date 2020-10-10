/*
 * October 11th 2020 <Author : Thomas S J>
 * Sparse Array Multiplication
 * Program to multiply two sparse arrays.
 * It takes in two ordinary arrays, converts them into the sparse form, and then multiplies them.
 * The output is the product of the two matrices in sparse form.
 */
#include<stdio.h>
#include<stdlib.h>

//Each ordinary matrix (2-D array) will have its own dimensions structure to store its dimensions
struct dimensions
{
	int rows;
	int columns;
};

//This function will take in the dimensions structure and write into it the value of the dimensions that the user wants
void
get_dimensions(struct dimensions *array)
{
	printf("Enter the value of rows: ");
	scanf("%d",&(array->rows));
	printf("Enter the number of columns: ");
	scanf("%d",&(array->columns));
}

//This function creates an empty 2-D array of the given dimensions and return its pointer
int**
create_array(struct dimensions array)
{
	int** arr = malloc(sizeof(int*)*(array.rows));
	for(int i = 0;i < (array.rows);i++){
		arr[i] = malloc(sizeof(int)*(array.columns));
	}
	return arr;
}

//This function will populate the given 2-D array
void
fill_array(int **arr, struct dimensions array)
{

	printf("Enter the elements of array: \n");
	for(int i = 0;i < array.rows;i++){
		printf("Enter %d row\n",(i+1));
		for(int j = 0;j < array.columns;j++){
			scanf("%d", &arr[i][j]);
		}
		printf("Row %d over\n",(i+1));
}
}

//This function displays the given array on the screen
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

//This function checks if the given two arrays are compatible for multiplication or not
void 
check_dimensions(struct dimensions array1, struct dimensions array2)
{
	//Basic condition for two arrays to be multiplied is that the number of columns of the first matrix must equal the number of rows of the second
	if(array1.columns != array2.rows){
		printf("The dimensions of the two matrices arent compatible for multiplication\n");
		exit(0);
	}
}

//This function returns the transposed form of the given array
int**
transpose_of_array(int **array, struct dimensions arr){
	
	int** transpose_array = malloc(sizeof(int*)*(arr.columns));

	for(int i = 0;i < arr.columns;i++){
		transpose_array[i] = malloc(sizeof(int)*(arr.rows));
			
	}

	for(int i = 0;i < arr.rows;i++){
		for(int j = 0;j < arr.columns;j++){
			transpose_array[j][i] = array[i][j]; 
		}
	}
	return transpose_array;
}

// This function converts an array into its sparse form
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

//This function is used to display the given sparse matrix
void
display_sparse_array(int** sparse_array){
	
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

//This function will take in a sparse array and return its real form (ie- in the traditional m*n form)
int**
build_real_array(int** sparse_array){
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
		arr[write_row-1][write_column-1] = write_value;
	}
	return arr;
}

int**
multiply(int** array1, int** array2)
{
	/*
	 *Our inputs are two sparse arrays which must be multiplied.
	 *The first one is a normal matrix in ts sparse form.
	 *The second is the transpose of the orginal array, converted into its sparse form.
	 *This makes the multiplication process slightly easier to do.
	 */
	int **product_sparse_array = malloc(sizeof(int*)*((array1[0][0])*(array2[0][1])));
	product_sparse_array[0] = malloc(sizeof(int)*3);
	product_sparse_array[0][0] = array1[0][0];
	product_sparse_array[0][1] = array2[0][1];
	
	int product_belay = 0;
	for(int i = 1;i <= array1[0][2];i++){
		for(int j = 1;j <= array2[0][2];j++){
			if(array1[i][1] == array2[j][1]){
				product_belay++;
				product_sparse_array[product_belay] = malloc(sizeof(int)*3);
				product_sparse_array[product_belay][0] = array1[i][0];
				product_sparse_array[product_belay][1] = array2[j][0];
				product_sparse_array[product_belay][2] = array1[i][2]*array2[j][2];
			}
		}
	}
	product_sparse_array[0][2] = product_belay;
	product_sparse_array = realloc(product_sparse_array, sizeof(int*)*(product_belay+1));
	return product_sparse_array;
}

int 
main(int argc, char* argv[])
{
	//Creating and populating array 1
	struct dimensions array1;
	get_dimensions(&array1);
	int **arr1 = create_array(array1);
	fill_array(arr1,array1);
	printf("The first array is:\n");
	display_array(arr1,array1);
	

	//Creating and populating array 2
	struct dimensions array2;
	get_dimensions(&array2);
	int **arr2 = create_array(array2);
	fill_array(arr2,array2);
	printf("The second array is:\n");
	display_array(arr2,array2);

	check_dimensions(array1, array2);
	
	//Converting a given array into its sparse form
	//For array 1, we can directly convert into sparse form
	//For array 2, we first find its transpose and then convert to sparse form 
	int **sparse_array1 = array_to_sparse(arr1, array1);
	int **transpose_of_array2 = transpose_of_array(arr2, array2);
	struct dimensions transpose_array2;
	transpose_array2.columns = array2.rows;
	transpose_array2.rows = array2.columns;
	int **sparse_array2 = array_to_sparse(arr2, array2);
	int **sparse_of_tranpose_of_array2 = array_to_sparse(transpose_of_array2,transpose_array2);
	//Both arrays have been converted to their sparse forms

	//Displaying the sparse array
	printf("The sparse form of the first array is :\n");
	display_sparse_array(sparse_array1);
	printf("The sparse form of the second array :\n");
	display_sparse_array(sparse_array2);
	
	//Finding product
	printf("The product of the two arrays in sparse form is:\n");
	int **product_array_in_sparse_form = multiply(sparse_array1, sparse_of_tranpose_of_array2);
	display_sparse_array(product_array_in_sparse_form);
	printf("The product array in its real form is:\n");
	int **product_array = build_real_array(product_array_in_sparse_form);
	struct dimensions product_array_dimensions;
	product_array_dimensions.rows = array1.rows;
	product_array_dimensions.columns = array2.columns;
	display_array(product_array, product_array_dimensions);
	return 0;
}
