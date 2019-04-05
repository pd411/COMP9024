//
//  Stack.h
//  Stack
//
//  Created by pd-mac on 10/12/18.
//  Copyright © 2018 pd-mac. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#define MAXITEMS 100

void StackInit();   // set up empty stack
int StackIsEmpty(); // check whether stack is empty
void StackPush(char);   // insert char on top of stack
char StackPop();    // remove char from top of stack

#endif /* Stack_h */
