#ifndef COMMENT_H
#define COMMENT_H

#include<stdbool.h>
#include "post.h"  // (for list defination)

typedef struct Reply Reply;

typedef struct Comment{
    char* username;
    char* content;
    List replies;
    struct Comment* next;
}Comment;

Comment* createComment(char* username, char* content);
void freeCommentData(Comment* comment);

#endif