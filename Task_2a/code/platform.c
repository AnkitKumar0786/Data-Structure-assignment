#include "platform.h"
#include "reply.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Platform platform_instance ={ .posts = {NULL}, .lastViewedPost = NULL };

extern Post* createPost(char* username, char* caption);
extern Comment* createComment(char* username, char* content);
extern void freePostData(Post* post);
extern void freeCommentData(Comment* comment);



static Post* getNthPost(int n){
    if(n <= 0) return NULL;

    Post* current = (Post*)platform_instance.posts.head;
    for(int i = 1; i<n && current!= NULL; i++) {
        current = current->next;
    }
    return current;
}


static Comment* getNthComment(Post* post, int n){
    if(n <= 0 || post == NULL) return NULL;

    Comment* current = (Comment* )post->comments.head;
    for(int i=1; i<n && current != NULL; i++) {
        current = current->next;
    }
    return current;
}


Platform* createPlatform(){
    return &platform_instance; // single one only
}

    bool addPost(char* username, char* caption) {
    Post* newPost = createPost(username, caption);
    if(newPost == NULL) return false;

    newPost->next = (Post* )platform_instance.posts.head;
    platform_instance.posts.head = newPost;

    platform_instance.lastViewedPost = newPost;
    return true;
}


bool deletePost(int n){
    if(n<= 0 || platform_instance.posts.head == NULL) return false;

    Post* head = (Post*)platform_instance.posts.head;
    Post* to_delete = NULL;

    if(n == 1){ // head 
        to_delete = head;
        platform_instance.posts.head = head->next;
    }
    else{
        Post* current = head;
        for(int i=1; i< n - 1 && current != NULL; i++){
            current = current->next;
        }
        if(current == NULL || current->next == NULL){
            return false;    // n is out of bounds
        }
        to_delete = current->next;
        current->next = to_delete->next;
    }

    if(to_delete != NULL){
        if (to_delete == platform_instance.lastViewedPost){
            platform_instance.lastViewedPost = (Post* )platform_instance.posts.head;
        }
        freePostData(to_delete);
        free(to_delete);
        return true;
    }
    return false;
}


Post* viewPost(int n){
    Post* post = getNthPost(n);
    if(post != NULL) {
        platform_instance.lastViewedPost = post;
    }
    return post;
}

Post* currPost(){
    return platform_instance.lastViewedPost;
}

Post* nextPost(){
    Post* current = platform_instance.lastViewedPost;
    if(current == NULL) return NULL; 

    Post* next_post = current->next;

    if(next_post == NULL){
        return current; 
    }

    platform_instance.lastViewedPost = next_post;
    return next_post;
}

Post* previousPost(){
    Post* current = platform_instance.lastViewedPost;
    Post* head = (Post* )platform_instance.posts.head;
    if(current == NULL) return NULL;

    if(current == head){
        return current;
    }

    Post* previous_post = head;
    while(previous_post!= NULL && previous_post->next != current){
        previous_post = previous_post->next;
    }

    if(previous_post != NULL){
        platform_instance.lastViewedPost = previous_post;
        return previous_post;
    }
    return NULL; // Error case
}

bool addComment(char* username, char* content){

    Post* post = platform_instance.lastViewedPost;
    if (post == NULL) return false;

    Comment* newComment = createComment(username, content);
    if (newComment == NULL) return false;

    newComment->next = (Comment*)post->comments.head;
    post->comments.head = newComment;
    return true;
}

bool deleteComment(int n){
    Post* post = platform_instance.lastViewedPost;
    if(post == NULL || n <= 0) return false;

    Comment* head = (Comment*)post->comments.head;
    Comment* to_delete = NULL;

    if(n == 1){     // Deleting the head 
        to_delete = head;
        post->comments.head = head->next;
    } 
    else 
    {
        Comment* current = head;
        for (int i = 1; i < n - 1 && current != NULL; i++) {
            current = current->next;
        }
        if (current == NULL || current->next == NULL) {
            return false; 
        }
        to_delete = current->next;
        current->next = to_delete->next;
    }

    if(to_delete != NULL){
        free(to_delete->username);
        free(to_delete->content);
        free(to_delete);
        return true;
    }
    return false;
}

Comment* viewComments(){
    Post* post = platform_instance.lastViewedPost;
    if(post == NULL) return NULL;

    return (Comment* )post->comments.head;
}

bool addReply(char* username, char* content, int n){

    Post* post = platform_instance.lastViewedPost;
    Comment* comment= getNthComment(post, n);
    if(comment == NULL) return false;

    Reply* newReply= createReply(username, content);
    if(newReply == NULL) return false;

    newReply->next = (Reply* )comment->replies.head;
    comment->replies.head = newReply;

    return true; 
}

bool deleteReply(int n, int m){
    Post* post = platform_instance.lastViewedPost;
    Comment* comment = getNthComment(post, n);
    if(comment == NULL) return false;

    Reply* head = (Reply*)comment->replies.head;
    Reply* to_delete = NULL;
    Reply* current = head;

    if(m ==1){
        to_delete = head;
        comment->replies.head = head->next;
    }
    else{
        for(int i = 1; i < m - 1 && current != NULL; i++){
            current = current->next;
        }
        if(current == NULL || current->next == NULL){
            return false;
        }
        to_delete = current->next;
        current->next = to_delete->next;
    }

    if(to_delete != NULL){
        freeReplyData(to_delete);
        free(to_delete);
        return true;
    }
    return false; 
}