//
//  main.c
//  AVLTree
//
//  Created by 彭迪 on 29/3/19.
//  Copyright © 2019 di. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define bool int
#define TRUE 1
#define FALSE 0
// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data type for avl tree nodes
typedef struct AVLTreeNode {
    int key; //key of this item
    int  value;  //value (int) of this item
    int height; //height of the subtree rooted at this node
    struct AVLTreeNode *parent; //pointer to parent
    struct AVLTreeNode *left; //pointer to left child
    struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
    int  size;      // count of items in avl tree
    AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
    AVLTreeNode *new;
    new = malloc(sizeof(AVLTreeNode));
    assert(new != NULL);
    new->key = k;
    new->value = v;
    new->height = 0; // height of this new node is set to 0
    new->left = NULL; // this node has no child
    new->right = NULL;
    new->parent = NULL; // no parent
    return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
    AVLTree *T;
    T = malloc(sizeof (AVLTree));
    assert (T != NULL);
    T->size = 0;
    T->root = NULL;
    return T;
}

AVLTreeNode *minNodeOfSubtree(AVLTreeNode *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

int getBalanceFactor(AVLTreeNode *node){
    if (node != NULL){
        if (node->left == NULL && node->right == NULL) {
            return 0;
        } else if (node->left == NULL){
            return (-1 * node->right->height);
        } else if (node->right == NULL){
            return node->left->height;
        } else{
            return node->left->height - node->right->height;
        }
    }
    return 0;
}

int maxHeight(int x, int y){
    if (x >= y){
        return x;
    }else{
        return y;
    }
}


int getHeight(AVLTreeNode *node){
    if (node->left == NULL && node->right != NULL){
        return node->height = node->right->height;
    } else if (node->right == NULL && node->left != NULL){
        return node->height = node->left->height;
    } else if (node->right != NULL && node->left != NULL){
        return node->height = maxHeight(node->left->height, node->right->height);
    } else{
        return 0;
    }
}

/*
        node                  x
        /                      \
       x           ->          node
        \                      /
         y                    y
             rightRotation
 every times of rotation needs to change the heights of x, y and node
 meanwhile, the parents of node needs to be changed
 */
AVLTreeNode *rightRotation(AVLTreeNode *node){
    AVLTreeNode *x_node = node->left;
    AVLTreeNode *y_node = x_node->right;
    
    x_node->parent = node->parent;
    node->parent = x_node;
    x_node->right = node;
    node->left = y_node;
    
    node->height = getHeight(node) + 1;
    x_node->height = getHeight(x_node) + 1;
    return x_node;
}

/*
      node                       y
        \                       /
         y          ->        node
        /                       \
       x                         x
               leftRotation
  every times of rotation needs to change the heights of x, y and node
 */
AVLTreeNode *leftRotation(AVLTreeNode *node){
    AVLTreeNode *y_node = node->right;
    AVLTreeNode *x_node = y_node->left;
    
    y_node->parent = node->parent;
    node->parent = y_node;
    y_node->left = node;
    node->right = x_node;
    
    node->height = getHeight(node) + 1;
    y_node->height = getHeight(y_node) + 1;
    return y_node;
}

// if tree is not balance, it should be adjusted until it is balance
AVLTreeNode *reBalance(AVLTreeNode *node, int insertKey, int insertValue){
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1 && ((insertKey < node->left->key)
                              || (insertKey == node->key && insertValue > node->value))){
        return rightRotation(node);
    } else if (balanceFactor < -1 && ((insertKey > node->right->key)
                                      || (insertKey == node->key && insertValue > node->value))){
        return leftRotation(node);
    } else if (balanceFactor > 1 && ((insertKey > node->left->key)
                                     || (insertKey == node->key && insertValue > node->value))){
        node->left = leftRotation(node->left);
        return rightRotation(node);
    } else if (balanceFactor < -1 && ((insertKey < node->right->key)
                                      || (insertKey == node->key && insertValue < node->value))){
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    return node;
}

// put your time complexity analysis of CreateAVLTree() here
// this function calls InsertNode()
// the time complexity of InsertNode() is O(logn)
// and CreateAVLTree() uses the while loop
// so the time complexity of InsertNode() is O(nlogn)
// n is the number of input
AVLTree *CreateAVLTree(const char *filename)
{
    // put your code here
    char str[128];
    AVLTree *avlTree = newAVLTree();
    int k, v;
    int j;
    if (strcmp(filename, "stdin") == 0){
        printf("please input the items of (k, v):");
        while (fgets(str,100,stdin)!=NULL){
            if (*str == '\n'){
                break;
            }
            if (2 == sscanf(str, "(%d, %d)", &k, &v)) {
                InsertNode(avlTree, k, v);
            }else{
                printf("Error input.\nplease input the correct items of (k, v):");
            }
        }
    } else{
        FILE *fp = fopen(filename, "r");
        if (fp == NULL){
            printf("There is no file found!\n");
            return 0;
        }
        while (fscanf(fp, "(%d, %d) ", &k, &v) != EOF){
            j = InsertNode(avlTree, k, v);
        }
        
    }
    return avlTree;
}

AVLTreeNode *CloneNode(AVLTreeNode *node){
    if (node == NULL){
        return node;
    }
    AVLTreeNode *temp = newAVLTreeNode(node->key, node->value);
    temp->height = node->height;
    temp->parent = node->parent;
    temp->right = CloneNode(node->right);
    temp->left = CloneNode(node->left);
    return temp;
}
// put your time complexity analysis for CloneAVLTree() here
// this function calls CloneNode()
// the time complexity of CloneNode() is O(n)
// so the time complexity of CloneAVLTree() is O(n)
// n is the size of T
AVLTree *CloneAVLTree(AVLTree *T)
{
    
    AVLTree *cloneTree = newAVLTree();
    // put your code here
    if (NULL != T)
        cloneTree->root = CloneNode(T->root);
    return cloneTree;
}

AVLTree *UnionNode(AVLTreeNode *node, AVLTree *resultTree){
    int j;
    if (node == NULL) {
        return resultTree;
    }
    j = InsertNode(resultTree, node->key, node->value);
    UnionNode(node->left, resultTree);
    UnionNode(node->right, resultTree);
    return resultTree;
}

// put your time complexity for ALVTreesUNion() here
// this function calls UnionNode()
// the time complexity of UnionNode() is nlogn
// the AVLTreesUnion() needs to call the UnionNode() twice
// so the time complexity of AVLTreesUnion is O((m+n)log(m+n))
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
    //put your code here
    AVLTree *resultTree = newAVLTree();
    UnionNode(T1->root, resultTree);
    UnionNode(T2->root, resultTree);
    return resultTree;
}

AVLTree *IntersectionNode(AVLTreeNode *node1, AVLTreeNode *node2, AVLTree *resultTree){
    int j;
    if (node1 == NULL || node2 == NULL){
        return resultTree;
    }
    if ((node1->key < node2->key) || ((node1->key == node2->key) && (node1->value < node2->value))) {
        IntersectionNode(node1, node2->left, resultTree);
        IntersectionNode(node1->right, node2, resultTree);
    } else if((node1->key > node2->key) || ((node1->key == node2->key) && (node1->value > node2->value))){
        IntersectionNode(node1->left, node2, resultTree);
        IntersectionNode(node1, node2->right, resultTree);
    } else if(node1->key == node2->key && node1->value == node2->value){
        j = InsertNode(resultTree, node1->key, node1->value);
        IntersectionNode(node1->left, node2->left, resultTree);
        IntersectionNode(node1->right, node2->right, resultTree);
    }
    return resultTree;
}

// put your time complexity for ALVTreesIntersection() here
// this function calls IntersectionNode()
// the time complexity of IntersectionNode() is O(m+n+klogk)
// m is the size of T1, n is the size of T2, k is the intersection of m and n
// so the time complexity of AVLTreesIntersection is O(m+n+klogk)
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
{
    //put your code here
    AVLTree *intersTree = newAVLTree();
    IntersectionNode(T2->root, T1->root, intersTree);
    return intersTree;
}

AVLTreeNode *addNode(AVLTreeNode *node, int k, int v, bool *isInsert){
    if (k == node->key && v == node->value){
        *isInsert = FALSE;
        return node;
    }
    if (!(*isInsert)) {
        return node;
    }
    if ((k < node->key) || ((k == node->key)&&(v < node->value))){
        if (node->left != NULL){
            node->left = addNode(node->left, k, v, isInsert);
        } else{
            node->left = newAVLTreeNode(k, v);
            node->left->height = 1;
            node->height = getHeight(node) + 1;
            node->left->parent = node;
            return node;
        }
    } else if((k > node->key) || ((k == node->key)&&(v > node->value))){
        if (node->right != NULL){
            node->right = addNode(node->right, k, v, isInsert);
        } else{
            node->right = newAVLTreeNode(k, v);
            node->right->height = 1;
            node->height = getHeight(node) + 1;
            node->right->parent = node;
            return node;
        }
    }
    
    node->height = getHeight(node) + 1;
    // check the balance factor of tree from root
    node = reBalance(node, k, v);
    return node;
}

// put the time complexity analysis for InsertNode() here
// this function calls addNode()
// the time complexity of addNode() is O(logn)
// so the time complexity of InsertNode is O(logn)
// n is the size of T
int InsertNode(AVLTree *T, int k, int v)
{
    bool isInsert = TRUE;
    //put your code here
    if (T->root == NULL){
        T->root = newAVLTreeNode(k, v);
        T->root->height++;
    } else{
        T->root = addNode(T->root, k, v, &isInsert);
        if (!isInsert) {
            return 0;
        }
    }
    T->size++;
    return 1;
}

AVLTreeNode *delete(AVLTreeNode *node, int k, int v, bool *isRemove){
    if (!isRemove) {
        return node;
    }
    // if node is not in tree
    if (node == NULL){
        *isRemove = FALSE;
        return node;
    }
    if ((k > node->key) || (k == node->key && v > node->value)) {
        node->right = delete(node->right, k, v, isRemove);
    } else if ((k < node->key) || (k == node->key && v < node->key)){
        node->right = delete(node->left, k, v, isRemove);
    }
    else{
        // if the node only has one side child
        if (node->left == NULL || node->right == NULL) {
            AVLTreeNode *tempNode = NULL;
            // check which side has node, and store the node in tempNode
            if (NULL == node->left) {
                tempNode = node->right;
            } else{
                tempNode = node->left;
            }
            
            if (tempNode == NULL) {
                node = NULL;
            } else{
                node = tempNode;
            }
        } else{
            // if the node has two side children
            // find the min node of sub tree in right side to change the root node
            AVLTreeNode *tempNode = minNodeOfSubtree(node->right);
            node->key = tempNode->key;
            node->value = tempNode->value;
            node->right = delete(node->right, tempNode->key, tempNode->value, isRemove);
        }
    }

    // adjust the height of the node
    if (node != NULL) {
        node->height = 1 + getHeight(node);
    }
    
    // rebalance
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        node = rightRotation(node);
    if (balanceFactor < -1 && getBalanceFactor(node) <= 0)
        node = leftRotation(node);
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = leftRotation(node->left);
        node = rightRotation(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rightRotation(node->right);
        node = leftRotation(node);
    }
    return node;
}

// put your time complexity for DeleteNode() here
// this function calls delete()
// the time complexity of delete() is O(logn)
// so the time complexity of DeleteNode() is O(logn)
int DeleteNode(AVLTree *T, int k, int v)
{
    // put your code here
    bool isRemove = TRUE;
    if (T->root == NULL){
        return 0;
    }
    T->root = delete(T->root, k, v, &isRemove);
    if (!isRemove) {
        return 0;
    }
    T->size--;
    return 1;
}

AVLTreeNode *SearchNode(AVLTreeNode *node, int k, int v, int *isFind){
    // if node is not in tree then return node == NULL
    if (node == NULL){
        return node;
    }
    // if node is found, then return node
    if (*isFind) {
        return node;
    }
    if (node->key == k && node->value == v){
        *isFind = TRUE;
        return node;
    } else if((k < node->key) || (k == node->key && v < node->value)){
        return SearchNode(node->left, k, v, isFind);
    } else if((k > node->key) || (k == node->key && v > node->value)){
        return SearchNode(node->right, k, v, isFind);
    }
    return node;
}

// put your time complexity analysis for Search() here
// it calls the function of SearchNode()
// the time complexity of SearchNode() is O(logn)
// n is the size of T
// so the Search() is O(logn)
AVLTreeNode *Search(AVLTree *T, int k, int v)
{
    // put your code here
    int isFind = 0;
    AVLTreeNode *node = SearchNode(T->root, k, v, &isFind);
    return node;
}

void freeNode(AVLTreeNode *node){
    if (node != NULL) {
        freeNode(node->left);
        freeNode(node->right);
        free(node);
    }
}

// put your time complexity analysis for freeAVLTree() here
// it calls the function of freeNode()
// the time complexity of FreeAVLTree() is O(n)
// n is the size of T
void FreeAVLTree(AVLTree *T)
{
    // put your code here
    if (T != NULL) {
        freeNode(T->root);
        free(T);
    }
}

void inOrder(AVLTreeNode *node){
    if (node != NULL) {
        inOrder(node->left);
        printf("(%d,%d), %d\n", node->key, node->value, node->height - 1);
        inOrder(node->right);
    }
}

// put your time complexity analysis for PrintAVLTree() here
// it calls the function of inOrder()
// the time complexity of inOrder() is O(n)
// n is the size of T
void PrintAVLTree(AVLTree *T)
{
    // put your code here
    if (T == NULL){
        return;
    } else{
        inOrder(T->root);
    }
    printf("\n");
}

int main() //sample main for testing
{ int i,j;
    AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
    AVLTreeNode *node1;
    
    tree1=CreateAVLTree("stdin");
    PrintAVLTree(tree1);
    FreeAVLTree(tree1);
    //you need to create the text file file1.txt
    // to store a set of items without duplicate items
    tree2=CreateAVLTree("File1.txt");
    PrintAVLTree(tree2);
    tree3=CloneAVLTree(tree2);
    PrintAVLTree(tree3);
    FreeAVLTree(tree2);
    FreeAVLTree(tree3);
    //Create tree4
    tree4=newAVLTree();
    j=InsertNode(tree4, 10, 10);
    for (i=0; i<15; i++)
    {
        j=InsertNode(tree4, i, i);
         if (j==0) printf("(%d, %d) already exists\n", i, i);
    }
    PrintAVLTree(tree4);
    node1=Search(tree4,20,20);
    
    if (node1!=NULL)
        printf("key= %d value= %d\n",node1->key,node1->value);
    else
        printf("Key 20 does not exist\n");
    
    for (i=17; i>0; i--)
    {
        j=DeleteNode(tree4, i, i);
        if (j==0)
            printf("Key %d does not exist\n",i);
        PrintAVLTree(tree4);
    }
    FreeAVLTree(tree4);
    //Create tree5
    tree5=newAVLTree();
    j=InsertNode(tree5, 6, 25);
    j=InsertNode(tree5, 6, 10);
    j=InsertNode(tree5, 6, 12);
    j=InsertNode(tree5, 6, 20);
    j=InsertNode(tree5, 9, 25);
    j=InsertNode(tree5, 10, 25);
    PrintAVLTree(tree5);
    //Create tree6
    tree6=newAVLTree();
    j=InsertNode(tree6, 6, 25);
    j=InsertNode(tree6, 5, 10);
    j=InsertNode(tree6, 6, 12);
    j=InsertNode(tree6, 6, 20);
    j=InsertNode(tree6, 8, 35);
    j=InsertNode(tree6, 10, 25);
    PrintAVLTree(tree6);
    
    tree7=AVLTreesIntersection(tree5, tree6);
    tree8=AVLTreesUnion(tree5,tree6);
    PrintAVLTree(tree7);
    PrintAVLTree(tree8);
    
    return 0;
}
