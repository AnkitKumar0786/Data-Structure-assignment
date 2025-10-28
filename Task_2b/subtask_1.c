#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;


TreeNode* createTreeNode(int value){
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}




typedef struct QueueNode{
    TreeNode* treeNode;
    struct QueueNode* next;
}QueueNode;


typedef struct Queue{
    struct QueueNode* front;
    struct QueueNode* rear;
}Queue;

Queue* createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isEmpty(Queue* q){
    return (q->front == NULL);
}

void push(Queue* q, TreeNode* treeNode){
    if(treeNode == NULL) return;
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = treeNode;
    temp->next = NULL;

    if(isEmpty(q)){
        q->front = temp;
        q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

void pop(Queue* q){
    if(isEmpty(q)) return;
    QueueNode* temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
    free(temp);
}

TreeNode* front(Queue* q){
    if(isEmpty(q)) return NULL;
    return q->front->treeNode;
}



// constructing tree
TreeNode* BuildTree(int arr[], int n) {
    if(n == 0 || arr[0] == 0) 
        return NULL;

    TreeNode* root = createTreeNode(1);
    Queue* q = createQueue();
    push(q, root);
    int i = 1;

    while(!isEmpty(q) && i<n){
        TreeNode* curr = front(q);
        pop(q);
    
        if(i < n){   //left child
            if(arr[i] == 1){
                curr->left = createTreeNode(1);
                push(q, curr->left);
            }
            i++;
        }
        
        if(i < n){   // right child
            if(arr[i] == 1){
                curr->right = createTreeNode(1);
                push(q, curr->right);
            }
            i++;
        }
    }
    return root;
}


//Minimum Phones (DFS approach)
int phones = 0;

int dfs(TreeNode* root){
    if(root == NULL) return 2; // Null nodes are considered covered

    int left = dfs(root->left);
    int right = dfs(root->right);

    if(left == 0 || right == 0){
        phones++;
        return 1; // this node has a phone
    }
    if(left == 1 || right == 1){
        return 2; // this node is covered
    }
    return 0; // this node needs a phone
}

int minPhones(TreeNode* root){
    phones = 0;
    
    if(dfs(root)== 0) phones++;
    return phones;
}


int main(){
    int n;
    scanf("%d", &n);

    int level_order[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &level_order[i]);
    }

    TreeNode* root = BuildTree(level_order, n);
    int m = minPhones(root);
    printf("%d\n", m);

    return 0;
}


// Input:
// 9
// 1 1 0 1 0 1 0 0 1
// Output:
// 2
