#include "post.h"
#include "comment.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* safe_strdup(const char* s){
    if(!s) return NULL;
    char* d = (char*)malloc(strlen(s)+1);
    if(d == NULL){
        printf("Failed to allocate memory for string duplication ");
        return NULL;
    }
    strcpy(d, s);
    return d;
}

void freePostData(Post* post)
{
    if (post == NULL) return;

    free(post->username);
    free(post->caption);

    Comment* current_comment = (Comment*)post->comments.head;
    Comment* next_comment;

    while (current_comment != NULL) {
        next_comment = current_comment->next;
        
        free(current_comment->username);
        free(current_comment->content);
        free(current_comment); 
        
        current_comment = next_comment;
    }
}

Post* createPost(char* username, char* caption){
    Post* newPost = (Post* )malloc(sizeof(Post));
    if(newPost == NULL){
        printf("Failed to create new post");
        return NULL;
    }

    newPost->username = safe_strdup(username);
    newPost->caption = safe_strdup(caption);

    if(newPost->username == NULL || newPost->caption == NULL){
        free(newPost->username);
        free(newPost->caption);
        free(newPost);
        return NULL;
    }

    newPost->comments.head = NULL;
    newPost->next = NULL;

    return newPost;
}