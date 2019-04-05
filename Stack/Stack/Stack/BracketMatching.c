//
//  BracketMatching.c
//  Stack
//
//  Created by 彭迪 on 26/2/19.
//  Copyright © 2019 pd-mac. All rights reserved.
//

#include <stdio.h>
#include "Stack.h"

// check whether expression
int bracketMatching(char string[], int size){
    int i;
    for(i = 0; i < size; i++){
        if(string[i] == '(' || string[i] == '[' || string[i] == '{'){
            StackPush(string[i]);
        }else if (string[i] == ')' || string[i] == ']' || string[i] == '}'){
            if(!StackIsEmpty()){
                char bracket = StackPop();
                if(match(bracket, string[i])){
                    continue;
                } else{
                    return 0;
                }
            } else{
                return 0;
            }
        }
    }
    if (StackIsEmpty()){
        return 1;
    } else{
        return 0;
    }
}

/*
int main() {
    StackInit();
    char expression[] = "void f(char a[], int n) {int i;for(i=0;i<n;i++) { a[i] = (a[i]*a[i])*(i+1); }};";
    int size = sizeof(expression) / sizeof(expression[0]);
    printf("%d\n", bracketMatching(expression, size));
}
 */
