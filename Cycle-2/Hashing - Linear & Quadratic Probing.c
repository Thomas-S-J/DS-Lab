#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Question:
 *
 * Given a natural language text, store each 
 * words in a hash table of size m = 26 using 
 * the mod function. Find the number of key 
 * comparisons for a successful search, if 
 * the collision resolution technique used is-
 * 1) Linear probing
 * 2) Quadratic probing
 */

/*
 * This program creates two hash tables:-
 * The first one implements insertion with linear probing,
 * and the second one implements insertion with quadratic
 * probing.
 *
 * Throughout the program, all operations such as insertion,
 * searching etc are done for both hash tables with the same
 * given input.
 */

char **hash_table_l;
char **hash_table_q;
int TABLE_SIZE_l = 26;
int TABLE_SIZE_q = 26;
int n_elements_l;
int n_elements_q;

void enter_linear(char *word);
void enter_quadratic(char *word);

int hashcode(char* word, int TABLE_SIZE){

	/*
	 * This function reads a word, performs some operations
	 * on it, and returns the hash code (which is an int value),
	 * for the given input.
	 */

	int len = strlen(word);
	int ascii_ch1 = 0xFF&word[0];
	int ascii_ch2 = 0xFF&word[len-1];
	int hash_value = (ascii_ch1 * ascii_ch2)%TABLE_SIZE;

        return(hash_value);
}

void rehash_l(){

	/*
	 * As the name suggests, rehashing means hashing again.
	 * Basically, when the load factor increases to more than
	 * its pre-defined value (here 1), the complexity increases.
	 * So to overcome this, the size of the array is increased
	 * (doubled) and all the values are hashed again and stored
	 * in the new double sized array to maintain a low load factor
	 * and low complexity.
	 */

	TABLE_SIZE_l *= 2;
	char **old_hash_table = hash_table_l;
	hash_table_l = malloc(sizeof(char*)*TABLE_SIZE_l);
	for(int i = 0; i < TABLE_SIZE_l; i++){
		hash_table_l[i] = NULL;
	}

	/*
	 * Rehashing all the elements in the old table to their new
	 * positions in the newly alllocated table. We need to recalculate
	 * all the key-value pairs, and add the new values in the table.
	 */

	for(int i = 0; i < TABLE_SIZE_l/2; i++){

		if(old_hash_table[i] != NULL)
			enter_linear(old_hash_table[i]);
	}

	// Finally release the old hash table
	free(old_hash_table);
}

void enter_linear(char *word){

	/*
	 * This function takes a word as input and inserts
	 * it into the hash table using linear probing.
	 */

	/* 
	 * Before inserting a new element into the hash
	 * table, we check if the hash table is full or
	 * not. If yes, we first rehash and then enter
	 * the new element.
	 */
	
	if(n_elements_l == TABLE_SIZE_l){
		n_elements_l = 0;
		rehash_l();
	}

	/*
	 * To insert an element into the hash table, we
	 * give the element to be entered (called key) and
	 * a hash function determines at which index the
	 * element must be stored.
	 */

	int value = hashcode(word, TABLE_SIZE_l);

	/*
	 * We are asked to resolve collisions using 'linear probing'.
	 * In this method, if there is a collision at the selected index
	 * value, we try to insert our element at the next available free
	 * space in the array.
	 */

	while(hash_table_l[value] != NULL){
		value = (value+1)%TABLE_SIZE_l;
	}
	hash_table_l[value] = word;
	n_elements_l++;

}

void rehash_q(){

	/*
	 * This function is used to rehash the table which uses quadratic
	 * probing. It works the exact same way as the linear rehashing
	 * function does, the only difference being that this function
	 * calls the function to insert using quadratic probing after
	 * doubling the table size.
	 *
	 * The logic of both functions is exactly same.
	 */

	TABLE_SIZE_q *= 2;
	
	char **old_hash_table = hash_table_q;
	hash_table_q = malloc(sizeof(char*)*TABLE_SIZE_q);
	for(int i = 0; i < TABLE_SIZE_q; i++){
		hash_table_q[i] = NULL;
	}

	/*
	 * Going to enter the elements into the new table using
	 * quadratic probing as the collision resolution technique.
	 */

	for(int i = 0; i < TABLE_SIZE_q/2; i++){

		if(old_hash_table[i] != NULL)
			enter_quadratic(old_hash_table[i]);
	}
	
	//finally delete the old table
	free(old_hash_table);
}

void enter_quadratic(char *word){

	/*
	 * This function inserts an element into the hash table
	 * using 'quadratic probing' as the collision resolution
	 * technique.
	 */

	/*
	 * As usual, we first check if the hash table requires
	 * rehashing. Here too, we have opted for rehashing if
	 * the hash table is full. 
	 */

	if(n_elements_q == TABLE_SIZE_q){
		n_elements_q = 0;
		rehash_q();
	}

	/*
	 * Finding the hash value for the given word
	 */

	int value = hashcode(word, TABLE_SIZE_q);

	/*
	 * Here, we will attempt to perform collision resolution
	 * using 'quadratic probing'. In this method, we try to 
	 * insert the element at the (hash_value + i^2)th index 
	 * (i varies from 0, 1, 2 ... to TABLE_SIZE -1).
	 *
	 * The biggest advantage to quadratic probing over linear
	 * probing is that it does not form primary clusters. This
	 * distributes the key values more uniformly in the hash table,
	 * improving the searching and insertion.
	 */

	int current_index = value;
	int flag = 0;
	for(int count = 0; count < TABLE_SIZE_q; count++){
		
		current_index = (current_index + (count*count))%TABLE_SIZE_q;
		
		if(hash_table_q[current_index] == NULL){
			hash_table_q[current_index] = word;
			flag = 1;
			break;
		}
	}
	if(flag == 1){
		n_elements_q++;
	}else{
		printf("The element could not be added into the array.\n");
	}

}

int enter_element(){

	/*
	 * This function reads a string, splits it, and
	 * calls upon enter_linear() & enter_quadratic()
	 * to do the actual insertion the elements into
	 * their respective tables.
	 */

	char *sentence = malloc(sizeof(char)*1024);

	printf("Enter the string to be hashed: ");
	scanf("%[^\n]", sentence);
	printf("You entered: %s\n", sentence);

	/*
	 * Splitting the string (sentence) into individual 
	 * words... The basic concept is that a word is
	 * seperated (or delimited) by a space.
	 * 
	 * We will pass each word into the functions to
	 * insert it into the linear and quadratic hash
	 * tables.
	 */

	char *word = strtok(sentence, " ");
	while(word != NULL){
		
		enter_linear(word);
		enter_quadratic(word);
		word = strtok(NULL, " ");
	}

	return 1;
}

int search_linear(char *word){

	int flag = 0;
	int start_index = hashcode(word, TABLE_SIZE_l);
	int count = 1;
	int current_index = start_index;

	do{
		if(hash_table_l[current_index] && strcmp(hash_table_l[current_index], word) == 0){
			flag = 1;
			return count;
		}
		count++;
		current_index = (current_index+1) % TABLE_SIZE_l;
	}while(current_index != start_index && hash_table_l[current_index] != NULL);

	return 0;
}

int search_quadratic(char *word){

	int flag = 0;
	int start_index = hashcode(word, TABLE_SIZE_q);
	int count = 1;
	int current_index = start_index;

	/*
	 * Searching is done by comparing the word the user has entered,
	 * with the item in the (hash value + i^2)th location repeatedly
	 * until either i reaches TABLE_SIZE-1 or we hit an empty space.
	 * (i is a number starting from 0, 1, 2 ... to TABLE_SIZE -1)
	 */

	do{
	
		if(hash_table_q[current_index] && strcmp(hash_table_q[current_index], word) == 0){
			flag = 1;
			return count;
		}
		count++;
		current_index = (start_index + (count*count)) % TABLE_SIZE_q;
	}while(count <= TABLE_SIZE_q && hash_table_q[current_index] != NULL);

	return 0;
}

int search_element(){
	
	/*
	 * This function calls search_linear() and search_quadratic(),
	 * who return the number of comparisons each made in trying
	 * to search for the element in their hash tables.
	 */
	char *word = malloc(sizeof(char)*64);
	printf("Enter the word that must be searched: \n");
	scanf("%s", word);
	printf("Searching: %s\n", word);

	//Calling the functions.
	
	int comparisons1 = search_linear(word);
	int comparisons2 = search_quadratic(word);

	//We've got the results from both functions. Now just display it.

	if(comparisons1 == 0){
		printf("The word wasnt found in the linear probing table.\n");
	}
	else{
		printf("Searching when using linear probing took %d comparisons to search.\n", comparisons1);
	}
	if(comparisons2 == 0){
		printf("The word wasnt found in the quadratic probing table.\n");
	}
	else{
		printf("Searching when using quadratic probing took %d comparisons to search.\n", comparisons2);
	}

	printf("The difference in comparisons is %d\n", comparisons1 - comparisons2);

	return 1;
}

int display_hash_table(){

	printf("Hash table with linear probing:-\n");
	for(int i = 0; i < TABLE_SIZE_l; i++){
	
		printf("INDEX %d --->", i);
		//An element is considered empty if it contains NULL
		if(hash_table_l[i] == NULL){
		
			printf(" EMPTY\n");
		}else{
		
			printf(" %s\n", hash_table_l[i]);
		}
	}

	printf("Hash table with quadratic probing:-\n");
	for(int i = 0; i < TABLE_SIZE_q; i++){

		printf("INDEX %d --->", i);
		if(hash_table_q[i] == NULL){

			printf(" EMPTY\n");
		}else{

			printf(" %s\n", hash_table_q[i]);
		}
	}

	return 1;
}

int terminate(){

	free(hash_table_l);
	free(hash_table_q);
	printf("Good bye....\nExiting the program....\n");
	return 0;
}

void init(){
	
	//Create and initialise hash table for linear probing
	n_elements_l = 0;
	hash_table_l = malloc(sizeof(char*)*TABLE_SIZE_l);
	for(int i = 0; i < TABLE_SIZE_l; i++){
		hash_table_l[i] = NULL;
	}
	
	//Create and initialise hash table for quadratic probing
	n_elements_q = 0;
	hash_table_q = malloc(sizeof(char*)*TABLE_SIZE_q);
	for(int i = 0; i < TABLE_SIZE_q; i++){
		hash_table_q[i] = NULL;
	}

	return;
}

int frontend(){

	int choice;
	printf("   **********MENU**********\n");
	printf("1. Enter an element into the hash table.\n");
	printf("2. Search for an element.\n");
	printf("3. Display the hash table.\n");
	printf("4. Exit the program.\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);
	while(getchar() != '\n'); // Flush till end of line

	enum{
	
		ENTER = 1,
		SEARCH,
		DISPLAY,
		EXIT,
	};

	int retval;
	switch(choice){
	
		case ENTER:{
				   retval = enter_element();
				   break;
			   }
		case SEARCH:{
				  retval = search_element();
				  break;
			    }
		case DISPLAY:{
				  retval = display_hash_table();
				  break;
			     }
		case EXIT:{
				  retval = terminate();
				  break;
			  }
		default:{
			
				printf("Enter a valid option.\n");
				retval = 1;
				break;
			}

	}

	return retval;
}

int main(int argc, char *argv[]){

	init();

	while(frontend());

	return 0;
}
