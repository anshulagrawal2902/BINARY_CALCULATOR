#include<stdio.h>
#include<string.h>
#include"InfixToPostfix.h"

int isValidInput(char* exp){
    int i = 0;
    int bracesCount = 0;

    //checking for valid bracket sequence
    while(i != strlen(exp)){
        if(exp[i] == '(') bracesCount++;
        else if(exp[i] == ')' && bracesCount>0) bracesCount--;
        else if(exp[i] == ')' && bracesCount==0) {
            return 0;
        }
        i++;
    }
    if(bracesCount !=0) return 0;

    //checking for valid operations
    i = 0;
    while(i != strlen(exp)){
        if(exp[i] != '+' && exp[i] != '-' && exp[i] != '*' && exp[i] != '/'
        && exp[i] != '.' &&  exp[i] != ' ' &&  exp[i] < '0' && exp[i] >'9'  ){
            return 0;
        }
        i++;
    }

    // checking for valid combination of operations and operands
    i = 0;
    int operationDetected = 1;
    int spaceDectected = 0;
    while(i != strlen(exp)){
        if(exp[i] >= '0' && exp[i] <= '9' && operationDetected == 1){
            while(exp[i] >= '0' && exp[i] <= '9' || exp[i] == '.') i++;
            operationDetected = 0;
            i--;
        }
        else if(exp[i] >= '0' && exp[i] <= '9' && operationDetected == 0) return 0;
        else if(exp[i] == '.');
        else if(exp[i] ==')' || exp[i] == '(');
        else if(exp[i] == ' ');
        else if(operationDetected == 1) return 0;
        else operationDetected = 1;

        i++;
    }

    return 1; // expression is valid
}









