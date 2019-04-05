//
//  sample_pointer.c
//  Stack
//
//  Created by 彭迪 on 26/2/19.
//  Copyright © 2019 pd-mac. All rights reserved.
//

#include <stdio.h>
void swap(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

int main(){
    /*
    int *prt1, *prt2;
    int i = 10, j = 20;
    
    prt1 = &i;
    prt2 = &j;
    printf("%d, %d\n", *prt1, *prt2);
    
    *prt1 = *prt1 + *prt2;
    prt2 = prt1;
    printf("%d \n", *prt2);
    *prt2 = 2 * (*prt2);
    printf("Val = %d\n", *prt1 + *prt2);
    return 0;
     */
    /*
    int *p; int *q;
    int a[5];
    int x = 10, y;
    p = &x;
    printf("%d \n", *p); // 10
    *p = 20;
    printf("%d \n", x); // 20
    y = *p;
    printf("%d \n", y); // 20
    p = &a[2];
    printf("%d \n", *p); // 0
    q = p;
    printf("%d \n", *q); // 0
    return 0;
    */
    
    /*
    int a = 5, b = 7;
    swap(a, b);
    printf("a = %d, b = %d\n", a, b);
    return 0;
     */
    
    /*
    int a[6];
    int *p = &a[0];
    while (p <= &a[5]) {
        printf("%2d ", *p);
        p++; // just move the site of array a[6]
    }
     */
    int a[6] = {1,2,3,4,5,6};
    int *p;
    p = &a[0];
    p = p+2;
    printf("%d \n", *p); // 3 (which means *p is a[2])
    
}
