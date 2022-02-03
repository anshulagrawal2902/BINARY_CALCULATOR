#include<stdio.h>
#include"TakingInput.h"



int main(){

    printf("--Binary Number Calculator, DSA MINI PROJECT (BC)--\n");
    printf("||Anshul Agrawal , 112003006 , Div 1, S1 Batch||\n\n");
    printf("The operations that can be performed are '+' '-' '/' '*'.\n");
    printf("This calculator will run only once.\nEnter your expression now: \n");

    char userInput[2000];
    gets(userInput);

    char* inputInfix = userInput;

    if(isValidInput(inputInfix) == 0){
        printf("---------CHECK INPUT EXPRESSION-------------");
        return 0;
    }

    STACK stack;
    init_stack(&stack);
    stack = getPostfixStack(inputInfix);
    NUMBER_LIST solution = evaluatePostfixStack(stack);
    printNumber(solution);


    return 0;
}



