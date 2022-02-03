#include<stdio.h>
#include<stdlib.h>
#include"Operations.h"
// #include"Number_List.h"

typedef struct stackNode{
    struct stackNode* next;
    NUMBER_LIST number;
}stackNode;
typedef struct stackNode* STACKNODE;

typedef struct stack{
    int size;
    struct stackNode* top;
}stack;
typedef struct stack* STACK;

void init_stack(STACK *stack){
    (*stack) = (STACK)malloc(sizeof(stack));
    (*stack)->size = 100;
    (*stack)->top = NULL;
}

int getStackSize(STACK stack){
    STACKNODE ptr = stack->top;
    int size = 0;
    while(ptr != NULL){
        size++;
        ptr = ptr->next;
    }
    return size;
}

int isEmpty(STACK stack){
    if(stack->top == NULL) return 1;
    else return 0;
}

int isFull(STACK stack){
    if(getStackSize(stack) == stack->size) return 1;
    else return 0;
}

void push(STACK stack, NUMBER_LIST num_list ){
    if(isFull(stack) == 1) {
        printf("%s", "Stack is Full");
        return;
    }
    else if(isEmpty(stack) == 1){
        STACKNODE newStackNode = (STACKNODE)malloc(sizeof(stackNode));
        newStackNode->next = NULL;
        newStackNode->number = num_list;
        (stack)->top = newStackNode;
        return;
    }
    else {
        STACKNODE newStackNode = (STACKNODE)malloc(sizeof(stackNode));
        newStackNode->number = num_list;
        newStackNode->next = (stack)->top;
        (stack)->top = newStackNode;
        return;
    }
}

void pop(STACK stack){
    if(isEmpty(stack)) return;
    if(stack->top->next == NULL) {
        stack->top = NULL;
        return;
    }
    stack->top = stack->top->next;
    return;
}

STACKNODE peek(STACK stack){
    if(isEmpty(stack)) return NULL;
    return stack->top;
}


