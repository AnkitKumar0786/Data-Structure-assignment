#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

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
    QueueNode* front;
    QueueNode* rear;
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




//Build tree
TreeNode* BuildTree(int arr[], int n){
    if(n == 0 || arr[0] == 0) return NULL;

    TreeNode* root = createTreeNode(1);
    Queue* q = createQueue();
    push(q, root);
    int i = 1;

    while(!isEmpty(q) && i < n){
        TreeNode* curr = front(q);
        pop(q);

        if(i < n){  // left child
            if(arr[i] == 1){
                curr->left = createTreeNode(1);
                push(q, curr->left);
            }
            i++;
        }
        
        if(i < n){     // right child
            if(arr[i] == 1){
                curr->right = createTreeNode(1);
                push(q, curr->right);
            }
            i++;
        }
    }
    return root;
}

// Phones calculations
int phones = 0;

int dfs(TreeNode* root){
    if(root == NULL) return 2;

    int left = dfs(root->left);
    int right = dfs(root->right);

    if(left == 0 || right == 0){
        phones++;
        return 1;
    }

    if(left == 1 || right == 1){
        return 2;
    }

    return 0;
}

int minPhones(TreeNode* root){
    phones = 0;
    if(dfs(root) == 0) phones++;
    return phones;
}


void generatePrimes(int limit, int *primes, int m){

    bool *isprime = (bool* )malloc((limit+1)*sizeof(bool));
    for(int i=0; i<=limit; i++) isprime[i]=true;
    isprime[0]=isprime[1]=false;

    for(int i=2; i*i<=limit; i++){
        if(isprime[i]){
            for(int j=i*i;j<=limit;j+=i){
                isprime[j]=false;
            }
        }
    }

    int count=0;
    for(int i=2; i<=limit && count<m; i++){
        if(isprime[i]){
            primes[count++]=i;
        }
    }
    free(isprime);
}

// Count pairs outside [l, r] 
long long countPairsOutsideRange(int *primes, int m, int l, int r){

    long long count=0;
    for(int i=0; i<m; i++){
        for(int j=i+1; j<m; j++){
            int x = primes[i] ^primes[j];
            if(x<l || x>r) count++;
        }
    }
    return count;
}

int main(){
    int n;
    scanf("%d",&n);
    int *level_order = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        scanf("%d",&level_order[i]);
    }

    int l,r;
    scanf("%d %d",&l,&r);

    TreeNode* root = BuildTree(level_order, n);
    int m = minPhones(root);

    // Generate first m primes
    int *primes = (int*)malloc(m*sizeof(int));
    generatePrimes(4000000, primes, m);

    long long x = countPairsOutsideRange(primes, m, l, r);

    printf("%d\n%lld\n", m, x);

    free(level_order);
    free(primes);

    return 0;
}


// Input:
// 23
// 1 1 1 1 1 0 1 1 0 0 1 0 0 0 1 1 1 1 1 0 1 1
// 7 13

// Output:
// 5
// 6
