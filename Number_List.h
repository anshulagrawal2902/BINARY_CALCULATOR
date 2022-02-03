#include<stdio.h>
#include<stdlib.h>
#define PLUS 1
#define MINUS -1
#define EQUAL 0
#define NUMBER1  1
#define NUMBER2 2

typedef struct NumberListNode{
    struct NumberListNode* prev;
    struct NumberListNode* next;
    int digit;
}NumberListNode;
typedef struct NumberListNode* NUMBER_LIST_NODE;

typedef struct NumberList{
    struct NumberListNode* head;
    struct NumberListNode* tail;
    int sign; //sign of number

}NumberList;
typedef struct NumberList* NUMBER_LIST;

void init_num(NUMBER_LIST *a){
    (*a) = (NUMBER_LIST)malloc(sizeof(NumberList));
    (*a)->sign = PLUS;
    (*a)->head = NULL;

    (*a)->tail = NULL;

    return;
}

void append(NUMBER_LIST a, char ch){
    if( (a)->head == NULL){
        NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
        newNumberListNode->prev = NULL;
        newNumberListNode->next = NULL;
        newNumberListNode->digit = ch - '0';
        (a)->head = newNumberListNode;
        (a)->tail = newNumberListNode;

    }
    else{
        NumberListNode* newNumberListNode = (NumberListNode*)malloc(sizeof(NumberListNode));
        newNumberListNode->next = NULL;
        newNumberListNode->digit = ch - '0';
        newNumberListNode->prev = (a)->tail;
        (a)->tail->next = newNumberListNode;
        (a)->tail = newNumberListNode;

    }
}

int getLengthOfNum(NUMBER_LIST a){
    int len = 0;
    NUMBER_LIST_NODE ptr = (a)->head;
    while(ptr != NULL){
        len++;
        ptr = ptr->next;
    }
    return len;
}

void addDigitAtStartOfNumberList(NUMBER_LIST num_list, int digit){
    NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
    newNumberListNode->prev = NULL;
    newNumberListNode->next = NULL;
    newNumberListNode->digit = digit;
    if((num_list->head) == NULL){
        num_list->head = newNumberListNode;
        num_list->tail = newNumberListNode;
    }
    else{
        newNumberListNode->next = num_list->head;
        num_list->head->prev = newNumberListNode;
        num_list->head = newNumberListNode;
    }
}

void addZeroesAtEnd(NUMBER_LIST a, int n){// adds n zeroes at end of number
    if( (a)->head == NULL ) {// if number was never initialized
        NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
        newNumberListNode->next = NULL;
         newNumberListNode->prev = NULL;
        (a)->head = newNumberListNode;
        (a)->tail = newNumberListNode;
        }
    while(n-- >0){
        NUMBER_LIST_NODE newNumberListNode = (NUMBER_LIST_NODE)malloc(sizeof(NumberListNode));
        newNumberListNode->digit = 0;
        newNumberListNode->next = NULL;
        newNumberListNode->prev = (a)->tail;
        (a)->tail->next = newNumberListNode;
        (a)->tail = newNumberListNode;
    }
}

void addZeroesAtStart(NUMBER_LIST num_list, int n){
    while (n-->0)
    {
        addDigitAtStartOfNumberList(num_list, 0);
    }

}

void makeNumberLengthsEqual(NUMBER_LIST num1, NUMBER_LIST num2){


    int num1Len = getLengthOfNum(num1);
    int num2Len = getLengthOfNum(num2);
    if(num1Len > num2Len) addZeroesAtStart(num2, (num1Len - num2Len));
    else if(num2Len > num1Len) addZeroesAtStart(num1, (num2Len - num1Len));
}

void removeInsignificantZeroes(NUMBER_LIST num_list){
    NUMBER_LIST_NODE a = num_list->head;
    if(a == NULL) return;
    while(a !=NULL && a->digit == 0 ){
        a = a->next;
    }
    num_list->head = a;
    if(a== NULL ) num_list->head = NULL;
    if(num_list->head != NULL)num_list->head->prev = NULL;
    if(getLengthOfNum(num_list) == 0) append(num_list, '0');
}

int getBiggerNumber(NUMBER_LIST num1, NUMBER_LIST num2){
    removeInsignificantZeroes(num1);
    removeInsignificantZeroes(num2);
    makeNumberLengthsEqual(num1, num2);
    NUMBER_LIST_NODE ptr1 = num1->head;
    NUMBER_LIST_NODE ptr2 = num2->head;
    while(ptr1!=NULL){
        if(ptr1->digit != ptr2->digit){
            if(ptr1->digit > ptr2->digit) return NUMBER1;
            else return NUMBER2;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return EQUAL;
}

void printNumber(NUMBER_LIST a){
    if(a == NULL) {
        printf("%s", "number is null");
        return;
    }
    if(a->head == NULL ) {
        printf("%s", "Number has no head");
        return;
    }
    removeInsignificantZeroes(a);
    NUMBER_LIST_NODE ptr = (a)->head;
    if(a->sign == MINUS) printf("%c", '-');
    if(ptr == NULL) {
        //printf("%d", 0);
        return;
    }
    while(ptr != NULL) {
        printf("%d", ptr->digit);
        ptr = ptr->next;
    }
}

void makeEachDigitLessThanTen(NUMBER_LIST num1){
    NUMBER_LIST_NODE ptr1 = num1->tail;
    int carry = 0;
    while(ptr1->prev != NULL){
        if(ptr1->digit > 9){
            carry = (ptr1->digit) / 10;
            ptr1->prev->digit += carry;
            ptr1->digit = (ptr1->digit) % 10;
        }
        ptr1 = ptr1->prev;
        carry = 0;
    }
    ptr1->digit += carry;
    if(ptr1->digit > 9){
        addDigitAtStartOfNumberList(num1, (ptr1->digit) / 10);
        ptr1->digit = (ptr1->digit)  % 10;
    }
}

int isZero(NUMBER_LIST num1){
    removeInsignificantZeroes(num1);
    NUMBER_LIST_NODE ptr = num1->head;
    while(ptr != NULL){
        if(ptr->digit > 0) return 0;
        ptr = ptr->next;
    }
    return 1;
}
