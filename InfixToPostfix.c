#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stack.h"

//mapping + operation to int = -1;
//mapping - operation to int = -2;
//mapping * operation to int = -3;
//mapping / operation to int = -4;
//mapping ( operation to int = -5;
//mapping ) operation to int = -6;
//mapping ^ operation to int = -7;

NUMBER_LIST resultOfOperation(int a, NUMBER_LIST num1, NUMBER_LIST num2){
    NUMBER_LIST result;
    init_num(&result);
    if(a == -1) result = addNumbers(num1, num2);
    else if(a == -2) result = subNumbers(num2, num1);
    else if(a == -3) result = multiplyNumbers(num1, num2);
    else if(a == -4) result = divideNumbers(num2, num1);
    else if(a == -7) result = getExponent(num2, num1);
    return result;
}

int precedence(char chr){
    if(chr == '+' || chr == '-') return 1;
    else if(chr == '*' || chr == '/') return 5;
    else if(chr == '^') return 9;
}

 char associativity(char a){
     char b;
     if(a == '+' || a=='-'){
         b = 'L';
     }
     else if( (a)== '*' || (a)=='/'){
         b =  'L';
     }
     else if((a) == '^'){
        b = 'R';
     }
     return b;
 }

char mapping(int digit){
    if(digit == -1) return '+';
    else if(digit == -2) return '-';
    else if(digit == -3) return '*';
    else if(digit == -4) return '/';
    else if(digit == -5) return '(';
    else if(digit == -6) return ')';
    else if(digit == -7) return '^';
}

int reverseMapping(char a){
    if(a == '+') return -1;
    else if(a == '-') return -2;
    else if(a == '*') return -3;
    else if(a == '/') return -4;
    else if(a == '(') return -5;
    else if(a == ')') return -6;
    else if(a == '^') return -7;
}


STACK getPostfixStack(char* infixExpr){
    STACK final_stack;
    STACK intermediate_stack;
    STACK reversed_final_stack;
    init_stack(&final_stack);
    init_stack(&intermediate_stack);
    init_stack(&reversed_final_stack);
    int i = 0;
    while(i < strlen(infixExpr)){
        if(infixExpr[i] >= '0' && infixExpr[i] <='9'){
            NUMBER_LIST newNumberList;
            init_num(&newNumberList);
            while(infixExpr[i] >= '0' && infixExpr[i] <='9'){
                append(newNumberList, infixExpr[i]);
                i++;
            }
            i--;
            push(final_stack, newNumberList);
        }
        else if(infixExpr[i] == ' ');

        else if(isEmpty(intermediate_stack) == 1 || peek(intermediate_stack)->number->head->digit == reverseMapping('(')) {
                NUMBER_LIST newNumberList;
                init_num(&newNumberList);
                NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
                newNumberListNode->next = NULL;
                newNumberListNode->digit = reverseMapping(infixExpr[i]);
                newNumberList->head = newNumberListNode;
                newNumberList->tail = newNumberListNode;
                push(intermediate_stack, newNumberList);
            }
        else if(infixExpr[i] == '('){
            NUMBER_LIST newNumberList;
            init_num(&newNumberList);
            NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
            newNumberListNode->next = NULL;
            newNumberListNode->digit = reverseMapping('(');
            newNumberList->head = newNumberListNode;
            newNumberList->tail = newNumberListNode;
            push(intermediate_stack, newNumberList);
            }
        else if(infixExpr[i] == ')'){
            while(peek(intermediate_stack)->number->head->digit != reverseMapping('(')){
                    push(final_stack , (peek(intermediate_stack))->number);
                    pop(intermediate_stack);
                }
                pop(intermediate_stack);
            }
        else if(precedence(mapping(peek(intermediate_stack)->number->head->digit)) < precedence(infixExpr[i])){
            NUMBER_LIST newNumberList;
            init_num(&newNumberList);
            NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
            newNumberListNode->digit = reverseMapping(infixExpr[i]);
            newNumberListNode->next = NULL;
            newNumberList->head = newNumberListNode;
            newNumberList->tail = newNumberListNode;
            push(intermediate_stack, newNumberList);
        }
        else if(precedence(mapping(peek(intermediate_stack)->number->head->digit)) > precedence(infixExpr[i])){
            push(final_stack, peek(intermediate_stack)->number);
            pop(intermediate_stack);
            i--;
        }
        else if(precedence(mapping(peek(intermediate_stack)->number->head->digit))== precedence(infixExpr[i])){
            NUMBER_LIST newNumberList;
            init_num(&newNumberList);
            NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
            newNumberListNode->digit = reverseMapping(infixExpr[i]);
            newNumberListNode->next = NULL;
            newNumberListNode->prev = NULL;
            if(associativity(infixExpr[i]) == 'L'){
                push(final_stack, (peek(intermediate_stack))->number);
                pop(intermediate_stack);
                newNumberList->head = newNumberListNode;
                newNumberList->tail = newNumberListNode;
                push(intermediate_stack, newNumberList);
            }
            else if(associativity(infixExpr[i])== 'R'){
                push(intermediate_stack, newNumberList);
            }
        }
        i++;
    }

     while(isEmpty(intermediate_stack) == 0){
         push(final_stack, peek(intermediate_stack)->number);
         pop(intermediate_stack);
     }

    while(isEmpty(final_stack) == 0){
        push(reversed_final_stack, peek(final_stack)->number);
        pop(final_stack);
    }

    return reversed_final_stack;
}

void printStack(STACK stack){
    stackNode* ptr = stack->top;
    while(ptr!=NULL){
        if(ptr->number->head->digit >= 0)
            printNumber(ptr->number);
        else printf("%c", mapping(ptr->number->head->digit));
        printf("%c", ' ');
        ptr = ptr->next;
    }
}

NUMBER_LIST evaluatePostfixStack(STACK postfix_stack){
    STACK ans_stack;
    init_stack(&ans_stack);
    while(isEmpty(postfix_stack) == 0){
        if(peek(postfix_stack)->number->head->digit < 0){
            NUMBER_LIST result;
            init_num(&result);
            NUMBER_LIST num_list1;
            init_num(&num_list1);
            NUMBER_LIST num_list2;
            init_num(&num_list2);
            num_list1 = peek(ans_stack)->number;
            pop(ans_stack);
            num_list2 = peek(ans_stack)->number;
            pop(ans_stack);
            result = resultOfOperation(peek(postfix_stack)->number->head->digit, num_list1, num_list2);
            push(ans_stack, result);
            pop(postfix_stack);
        }
        else{
            push(ans_stack, peek(postfix_stack)->number);
            pop(postfix_stack);
        }
    }
    return ans_stack->top->number;
}



