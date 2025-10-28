#include "comment.h"
#include "reply.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


extern char* safe_strdup(const char* s);
extern void freeReplyData(Reply* reply);

void freeCommentData(Comment* comment){
    if (comment == NULL) return;

    free(comment->username);
    free(comment->content);

    Reply* current_reply = (Reply*)comment->replies.head;
    Reply* next_reply;

    while(current_reply!= NULL){
        next_reply = current_reply->next;
        freeReplyData(current_reply);
        
        current_reply = next_reply;
    }
    free(comment);
}

Comment* createComment(char* username, char* content){
    Comment* newComment= (Comment*)malloc(sizeof(Comment));

    if(newComment == NULL){
        printf("Failed to allocate memory to newcomment");
        return NULL;
    }

    newComment->username = safe_strdup(username);
    newComment->content = safe_strdup(content);

    if (newComment->username == NULL || newComment->content == NULL){
        free(newComment->username);
        free(newComment->content);
        free(newComment);
        return NULL;
    }

    return newComment;
}