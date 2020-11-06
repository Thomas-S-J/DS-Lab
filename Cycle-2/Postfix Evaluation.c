#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>

char operator_array[] = {'+','-','*','/','%','^'};

bool isOperator(char symbol){

	/* 
	 * Here we compare the input symbol with a
	 * predefined set of symbols from the operator_array[].
	 */
	for(int i = 0;i < 6;i++){
	
		if(symbol == operator_array[i]){
			return true;
		}
	}
	return false;
}

char perform_operation(int operand1, int operand2, char operator){

	/*
	 * TODO:Any better way of doing this? I wasn't getting
	 * any other way of doing it..
	 */
	switch(operator){
		case '+':return operand2+operand1;
		case '-':return operand2-operand1;
		case '*':return operand2*operand1;
		case '/':return operand2/operand1;
		case '%':return operand2%operand1;
		case '^':return operand2^operand1;
	}
	return '\0';
}

int evaluate_postfix_expression(char *postfix_expression){

	//stack will only store operands which are integer values
	int *stack = malloc(sizeof(int)*64);
	int TOP_STACK = -1;

	for(int i = 0; postfix_expression[i]; i++){
	
		/*
		 * Essentially every character we read from the postfix expression
		 * is either an operator, an operand, or a space. Hence the postfix 
		 * expression is a character array (as it has to store symbols like 
		 * '+', '*' etc), but the result of the evaluation is an integer...
		 * so we store the stack (which stores only operands and the result 
		 * of evaluation at different stages) as an integer array.
		 */
		char current_symbol = postfix_expression[i];
		if(current_symbol == ' '){
			continue;
		}else if(isOperator(current_symbol)){
		
			/*
			 * So, the character that we read is an operator. The steps
			 * to deal with an operator are:-
			 * 1) POP two operands from the top of the stack
			 * 2) Use the operator on the operands we got in step 1 and evaluate
			 * 3) PUSH the evaluated result into the stack.  
			 */
			int operand1 = stack[TOP_STACK];
			TOP_STACK--;
			int operand2 = stack[TOP_STACK];
			TOP_STACK--;
			int result = perform_operation(operand1, operand2, current_symbol);
			++TOP_STACK;
			stack[TOP_STACK] = result;
		}else{
		
			/*
			 * Ok, the character that we read is an operand. We can directly
			 * PUSH the operand into the stack.
			 */
			int actual_number = 0;
			if(isdigit(current_symbol)){
				do{
					actual_number = actual_number*10 + (current_symbol-'0');
					if(postfix_expression[++i])
						current_symbol = postfix_expression[i];
				}while(isdigit(postfix_expression[i]));
			}
			TOP_STACK++;
			stack[TOP_STACK] = actual_number;
		}
	}
	/*
	 * When control reaches here, the postfix expression has
	 * been fully evaluated. At this point, only one element
	 * will remain in the stack, and that is TOP element in the
	 * stack. We need return this element.
	 */
	return stack[TOP_STACK];
}

void main(int argc, char* argv[]){

	/*
	 * First we read the postfix expression to be evaluated. This
	 * expression will contain a combination ofdigits and operators,
	 * and hence is read into the program as a character array.
	 */
	char *postfix_str = malloc(sizeof(char)*64);
	printf("Enter a postfix expression: ");
	scanf("%63[^\n]%*1[\n]", postfix_str);

	/*
	 * The result after evaluating a postfix expression is a single
	 * integer value. This is stored in evaluated_postfix_string
	 */
	int evaluated_postfix_expression;
	evaluated_postfix_expression = evaluate_postfix_expression(postfix_str);
	printf("%d\n", evaluated_postfix_expression);

}
