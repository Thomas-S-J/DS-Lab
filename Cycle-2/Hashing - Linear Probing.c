#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

/* 
 * Question:
 * Write a C program to insert a set of keys into
 * a hash table of size m = 13 using the division
 * method and the collision resolution technique
 * as linear probing.
 */

int *hash_table;
int TABLE_SIZE = 13;
int n_elements;
int enter_element();

int hashcode(int element){

	return element % TABLE_SIZE;
}

void rehash(){

	/*
	 * As the name suggests, rehashing means hashing again.
	 * Basically, when the load factor increases to more than 
	 * its pre-defined value (here 1), the complexity increases.
	 * So to overcome this, the size of the array is increased
	 * (doubled) and all the values are hashed again and stored
	 * in the new double sized array to maintain a low load factor
	 * and low complexity.
	 */

	TABLE_SIZE *= 2;
	int *old_hash_table = hash_table;
	hash_table = malloc(sizeof(int)*TABLE_SIZE);
	memset(hash_table, -1, sizeof(int)*TABLE_SIZE);
	
	/*
	 * Rehashing all the elements in the old table to their new
	 * positions in the newly alllocated table. We need to recalculate
	 * all the key-value pairs, and add the new values in the table. 
	 */

	for(int i = 0; old_hash_table[i]; i++){

		enter_element(old_hash_table[i]);
	}

	// Finally release the old hash table
	free(old_hash_table);
}

int enter_element(int key){

	/* 
	 * Before inserting a new element into the hash
	 * table, we check if the hash table is full or
	 * not. If yes, we first rehash and then enter
	 * the new element.
	 */

	if(n_elements == TABLE_SIZE){
		n_elements = 0;
		rehash();
	}

	/*
	 * To insert an element into the hash table, we
	 * give the element to be entered (called key) and
	 * a hash function determines at which index the
	 * element must be stored.
	 */
	
	if(key < 0)
		return 1;

	int value = hashcode(key);

	/*
	 * We are asked to resolve collisions using 'linear probing'.
	 * In this method, if there is a collision at the selected index
	 * value, we try to insert our element at the next available free
	 * space in the array.
	 */

	while(hash_table[value] != -1 && hash_table[value] != INT_MIN){
		value = (value+1)%TABLE_SIZE;
	}
	hash_table[value] = key;
	n_elements++;

	return 1;
}

int search_element(){

	unsigned int key;
	printf("Enter the element to be searched: ");
	scanf("%d", &key);

	/*
	 * This is the crux of hashing.
	 * The whole point of hashing in the first place was to
	 * make look-up faster. Ideally the time complexity involved for
	 * searching any element should be O(1). However in practical 
	 * scenarios, this rarely ever happens.
	 * Most of the time, some amount of looping is done, but its
	 * defnitely better than going through the whole array from front
	 * to end.
	 */

	int flag = 0;
	int start_index = hashcode(key);

	/*
	 * The exact manner of searching for an element in the hash table
	 * will vary depending on the type of collison-resolution.
	 *
	 * Here we have used 'linear probing'. So all we need to do is search
	 * from the index given to us by the hash function until the first
	 * empty space.
	 * NOTE: In this program, an empty array element will either have -1 or 
	 * INT_MIN. But when searching is concerned, we will search until the first 
	 * array element containing -1 is encountered. This is because if the array 
	 * element is -1, it would imply that the array element has never been written
	 * on.
	 */

        int current_index = start_index;
	int count = 0;

        do{
                if(hash_table[current_index] == key){
                        flag = 1;
			printf("The element has been found at index %d.\n", current_index);
                        break;
                }
		current_index = (current_index+1) % TABLE_SIZE;
		count++;

        }while(current_index != start_index && hash_table[current_index] != -1 && count < TABLE_SIZE);

        if(flag == 0){

                printf("The element is not present in the hash table.\n");
        }

	return 1;
}

int delete_element(){

	unsigned int key;
        printf("Enter the element to be deleted: ");
        scanf("%d", &key);

	/*
	 * Deleting an element in the hash table is not as straight-forward
	 * as overwriting that element as -1. This is because when we delete,
	 * we also need to remember that this process is going to create an
	 * empty space in the hash table, and this should not interfere with
	 * searching or inserting.
	 *
	 * What do I mean by that ??
	 *
	 * Think of it this way:-
	 * If I overwrite an element as -1 and consider that as deleting, lets
	 * not forget, that now I have created an empty space in a cluster. This
	 * will mess up the search function, because empty space divided, what
	 * was initially a single cluster, into two seperate clusters...
	 *
	 * To solve this problem, we overwrite a deleted element with another value,
	 * which is not -1. I have used the macro INT_MIN which is defined in <limits.h>.
	 * As the name suggests, it stores the minimum value an int variable can store.
	 */

        int flag = 0;
        int index = hashcode(key);

        while(hash_table[index] && hash_table[index] != -1){
                if(hash_table[index] == key){

                        flag = 1;
                        break;
                }
                index = (index+1)%TABLE_SIZE;
        }
        if(flag == 1){

		hash_table[index] = INT_MIN;
		n_elements--;
        }else{
	
		printf("The given element does not exist in the hash table.\n");
	}
        return 1;

}

int display_hash_table(){

	for(int i = 0; i < TABLE_SIZE; i++){
	
		printf("INDEX %d --->", i);
		//An element is considered empty if it contains -1 or INT_MIN.
		if(hash_table[i] == -1 || hash_table[i] == INT_MIN){
		
			printf(" EMPTY\n");
		}else{
		
			printf("%d\n", hash_table[i]);
		}
	}

	return 1;
}

int terminate(){

	free(hash_table);
	printf("Good bye....\nExiting the program....\n");
	return 0;
}

static void init(){

	n_elements = 0;
	hash_table = malloc(sizeof(int)*TABLE_SIZE);
	memset(hash_table, -1, sizeof(int)*TABLE_SIZE);
	return;
}

int frontend(){

	int choice;
	printf("**********MENU**********:\n");
	printf("1. Enter an element into the hash table.\n");
	printf("2. Search for an element.\n");
	printf("3. Delete an element.\n");
	printf("4. Display the hash table.\n");
	printf("5. Exit the program.\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	enum{
	
		ENTER = 1,
		SEARCH,
		DELETE,
		DISPLAY,
		EXIT,
	};

	int retval;
	switch(choice){
	
		case ENTER:{
				   unsigned int key;
				   printf("Enter the element that must be stored: ");
				   scanf("%d", &key);
				   retval = enter_element(key);
				   break;
			   }
		case SEARCH:{
				  retval = search_element();
				  break;
			    }
		case DELETE:{
				  retval = delete_element();
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

	while(frontend())
		;

	return 0;
}
