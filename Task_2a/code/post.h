#ifndef POST_H  
#define POST_H

#include<stdbool.h>

typedef struct Comment Comment;
typedef struct List List;

struct List{
    void* head;
};

typedef struct Post
{
    char* username;
    char* caption;
    List comments;
    struct Post* next;

}Post;

Post* createPost(char* username , char* caption);

#endif