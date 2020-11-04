#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

struct symbol_info{

	char symbol;
	int precedence;
	char associativity;
};

struct symbol_info prec_array[] = {

	{'+',0,'L'},
	{'-',0,'L'},
	{'*',1,'L'},
	{'/',1,'L'},
	{'%',1,'L'},
	{'^',2,'R'},
};

bool isOperator(char symbol){

	for(int i = 0; i < 6; i++){
	
		if(prec_array[i].symbol == symbol){
			return true;
		}
	}
	return false;
}

/*
 * This function is used to compare the precedences of the given two
 * symbols. It returns:
 * true: if the imcoming symbol has higher precedence than the symbol in the stack
 * false: if the top operator in the stack has higher precedence.
 * This function essentially deals with the rules involved in determining the 
 * precedence of two operators.
 */
bool isGreaterPrecedence(char incoming_symbol, char top_operator_in_stack){

	/*
	 * If the top operator in stack is a left parenthesis,
	 * then there is no need to check for precedence...no
	 * matter what the incoming operator is, it must be pushed 
	 * into the stack. So we return true.
	 */
	if(top_operator_in_stack == '('){
		return true;
	}
	int index1, index2;
	for(int i = 0; i < 6; i++){
		/* 
		 * Trying to identify the incoming operator symbol 
		 * and the operator at the top of the stack symbol
		 */
		if(incoming_symbol == prec_array[i].symbol){
			index1 = i;
		}
		if(top_operator_in_stack == prec_array[i].symbol){
			index2 = i;
		}
	}
	
	
	 /*
	  * We've figured out what both the symbols are...now we compare their precedence.
	  * index1 is the position of the incoming symbols precedence data, and index2 is
	  * the position where the precedence data of the top element (which is an operator) 
	  * in the stack is located.
	  * There are essentially three cases:-
	  * 1) Incoming operator has GREATER precedence than the top element in stack
	  * 2) Incoming operator has LESSER precedence than the element in the top of the stack
	  * 3) Both the operators have equal precedence.
	  */
	if(prec_array[index1].precedence > prec_array[index2].precedence){
		/*
		 * Very straight-forward... the incoming operator has a higher precedence
		 * than the operator in the top of the stack. We can go ahead and push the
		 * incoming symbol into the stack. We return 'true' to signal the same.
		 */
		return true;
	}
	else if(prec_array[index1].precedence < prec_array[index2].precedence){
		/*
		 * The operator in the top of the stack has a higher precedence
		 * than the one that is incoming...we return false to signal the
		 * same.
		 */
		return false;
	}
	else if(prec_array[index1].precedence == prec_array[index2].precedence){
		/*
		 * Turns out, both the operators have the same precedence.
		 * Like for example:- '+' & '-' have the same precedence values.
		 * If thats the case, we need to check the associativity. If the 
		 * associativity is LEFT to RIGHT, then we pop the element in the top
		 * of the stack. If its RIGHT to LEFT, then we can push the incoming
		 * symbol into the stack.
		 */
		if(prec_array[index1].associativity == 'R'){
			return true;
		}
		else{
			return false;
		}
	}

	/*
	 * As far as I know, control never reaches here, so the return
	 * statement is actually redundant...but the C language requires
	 * us to give a return value for the function
	 */
	return false;
}

char* convert_to_postfix(char *infix_expression){

	char* postfix_string = malloc(sizeof(char)*64);
	char* stack = malloc(sizeof(char)*64);
	int TOP_STACK = -1;
	int belay = 0;
	for(int i = 0; infix_expression[i]; i++){

		/*Basically every character we read from the infix expression is either
		 * 1) a left parenthesis or,
		 * 2) an operator or,
		 * 3) a right parenthesis or,
		 * 4) an operand.
		 * Each individual case is dealt with below
		 */
		char current_symbol = infix_expression[i];
		if(current_symbol == '('){

			/*Case 1: The character we read from the infix operator was a left parenthesis.
			 *Action: Simply push this symbol ('(') into stack. There are no conditions to check.
			 */
			++TOP_STACK;
			stack[TOP_STACK] = current_symbol;
		} else if(current_symbol == ')') {
		
			/* Case 3: The incoming symbol is the right parenthesis.
			 * This means we pop from the stack and add the poppped 
			 * elements into the postfix string until we enounter the
			 * left parenthesis in the stack. Then we also pop the left 
			 * parenthesis, because it must not remain in the stack.
			 */
			while(stack[TOP_STACK] != '('){
			
				int data = stack[TOP_STACK];
				stack[TOP_STACK] = '\0';
				TOP_STACK--;
				postfix_string[belay] = data;
				belay++;
			}
			//dont forget to remove the left parenthesis.
			stack[TOP_STACK] = '\0';
			TOP_STACK--;
		} else if(isOperator(current_symbol)) {
			
			/*Case 2: The character is an operator. This is kinda tricky.
			 * We need to check if the incoming operator (ie the operator
			 * we just read from the infix expression), has a higher precedence
			 * than the operator that is already present in the top of the 
			 * stack. Our final job is to make sure that the operator is pushed 
			 * into the stack.
			 */
			while(true){
				if(TOP_STACK == -1){
					/*
					 * The stack is empty. This simplifies things. We dont
					 * have to go comparing precedences...directly push the
					 * incoming element into the stack, and get out of the
					 * loop using break
					 */
					++TOP_STACK;
					stack[TOP_STACK] = current_symbol;
					break;
				}else{
					/*
					 * The stack isnt empty. We need to compare the precedence
					 * of the incoming symbol with the one already present at the
					 * top of the stack
					 */
					if(isGreaterPrecedence(current_symbol, stack[TOP_STACK])){
					
							/*
							 * The isGreaterPrecedence() function has determined
							 * that our incoming symbol has greater precedence than
							 * the one already present at the top of the stack.
							 * We just go ahead and push the incoming element into
							 * the top of the stack, and break out of the loop.
							 */
							++TOP_STACK;
							stack[TOP_STACK] = current_symbol;
							break;
						}else{
							/*
							 * The isGreaterPrecedence() function has determined that the
							 * incoming symbol either has a lower precedence or that the
							 * precedence is same, but the associativity is left to right.
							 * At any rate, we need to pop elements from the stack and add it
							 * into the postfix string, until the element at the top 
							 * of the stack has a lower precedence (or equal precedence, but
							 * associativity is right to left), following which the
							 * incoming element will be added to our stack.
							 * */
							int data = stack[TOP_STACK];
							stack[TOP_STACK] = '\0';
							TOP_STACK--;
							postfix_string[belay] = data;
							belay++;
						}
					}	
			}
		} else {
			/* Case 4: The incoming symbol is an operand. Dealing with
			 * this is fairly straight-forward. We just add the operand
			 * into the postfix string. Theres no need to check for any
			 * conditions
			 */
			postfix_string[belay] = current_symbol;
			belay++;
		}
		//End of for loop. Now we go take the next symbol.
	}
	/*
	 * By now, we have finished reading from the infix expression
	 * If there are any elements remaining in the stack, it should
	 * be popped out until the stack is empty. The popped elements
	 * are added into the postfix string
	 */
	while(TOP_STACK != -1){
	
		int data = stack[TOP_STACK];
		stack[TOP_STACK] = '\0';
		TOP_STACK--;
		postfix_string[belay] = data;
		belay++;
	}

	return postfix_string;
}

void main(){

	printf("Enter an infix expression: ");
	char* input_infix_expression = malloc(sizeof(char)*64);
	scanf("%s", input_infix_expression);

	char *postfix_form = convert_to_postfix(input_infix_expression);
	printf("The given expression in postfix form is: %s\n", postfix_form);
}
