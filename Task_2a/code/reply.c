#include "reply.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char* safe_strdup(const char* s);

void freeReplyData(Reply* reply){
    if (reply == NULL) return;
    
    free(reply->username);
    free(reply->content);
    free(reply);
}

Reply* createReply(char* username, char* content){
    Reply* newReply = (Reply*)malloc(sizeof(Reply));
    if (newReply == NULL) {
        printf("Failed to allocate memory for new Reply");
        return NULL;
    }

    newReply->username = safe_strdup(username);
    newReply->content = safe_strdup(content);

    if (newReply->username == NULL || newReply->content == NULL){
        free(newReply->username);
        free(newReply->content);
        free(newReply);
        return NULL;
    }

    newReply->next = NULL;

    return newReply;

}