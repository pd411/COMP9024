//
//  Stack.c
//  Stack
//
//  Created by pd-mac on 10/12/18.
//  Copyright © 2018 pd-mac. All rights reserved.
//

#include "Stack.h"
#include <stdio.h>
#include <assert.h>

// define the Data Structure
typedef struct {
    char item[MAXITEMS];
    int top;
} stackRep;

// define the Data Object
static stackRep stackObject;

// set up empty stack
void StackInit(){
    stackObject.top = -1;
}

// check whether stack is empty
int StackIsEmpty(){
    return (stackObject.top < 0);
}

// insert char on top of stack
void StackPush(char ch){
    assert(stackObject.top < MAXITEMS - 1);
    stackObject.top++;
    int i = stackObject.top;
    stackObject.item[i] = ch;
}

// remove char from top of stack
char StackPop(){
    assert(stackObject.top > -1);
    int i = stackObject.top;
    char ch = stackObject.item[i];
    stackObject.top--;
    printf("%c\n", ch);
    return ch;
}

// check whether open bracket matches cloes bracket
int match(char open_bracket, char close_bracket){
    if(open_bracket == '(' && close_bracket == ')'){
        return 1;
    } else if (open_bracket == '[' && close_bracket == ']'){
        return 1;
    } else if (open_bracket == '{' && close_bracket == '}'){
        return 1;
    } else{
        return 0;
    }
    return 0;
}

