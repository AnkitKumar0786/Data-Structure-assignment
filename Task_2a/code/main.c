#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to print comments and their replies
void printComments(Comment* head){
    Comment* currComment=head;
    
    if (currComment == NULL){
        printf("No comments available.\n");
        return;
    }

    while (currComment != NULL){
        // Print the comment details
        printf("%s %s\n", currComment->username, currComment->content);
        
        // Traverse and print replies 
        Reply* currReply = (Reply*)currComment->replies.head;
        while (currReply != NULL){
            printf(" %s %s\n", currReply->username, currReply->content); 
            currReply = currReply->next;
        }

        currComment = currComment->next;
    }
}


int main(){
    // The platform is a global instance, but we call the creation function 
    // for completeness and potential initialization logic.
    (void)createPlatform();

    char command[50];
    char firstArg[50], secondArg[50]; 
    int n, m; // Indices for post/comment/reply numbers

    while (scanf("%s", command) != EOF){
        
        // 1. Initial Command
        if (strcmp(command, "create_platform") == 0){
            (void)createPlatform();
        } 
        
        // 2. ADD Operations (post, comment, reply)
        else if (strcmp(command, "add") == 0){
            scanf("%s", firstArg);
            
            if (strcmp(firstArg, "post") == 0) {
                if (scanf("%s %s", firstArg, secondArg) == 2) { 
                    if (!addPost(firstArg, secondArg)) {
                        printf("can't add post\n");
                    }
                }
            } else if (strcmp(firstArg, "comment") == 0) {
                if (scanf("%s %s", firstArg, secondArg) == 2) {
                    if (!addComment(firstArg, secondArg)) {
                        printf("Cannot add comment because No post viewed/exists.\n");
                    }
                }
            } else if (strcmp(firstArg, "reply") == 0) {
                if (scanf("%s %s %d", firstArg, secondArg, &n) == 3) {
                    if (!addReply(firstArg, secondArg, n)) {
                        printf("Cannot add reply. Comment %d not found or no last viewed post.\n", n);
                    }
                }
            }
        } 
        
        // 3. VIEW/CURRENT Operations
        else if (strcmp(command, "view_post") == 0) {
            if (scanf("%d", &n) == 1) { 
                Post *post = viewPost(n);
                if (post) {
                    printf("%s %s\n", post->username, post->caption);
                } else {
                    printf("Post does not exist.\n"); 
                }
            }
        } else if (strcmp(command, "current_post") == 0) {
            Post *post = currPost();
            if (post) {
                printf("%s %s\n", post->username, post->caption);
            } else {
                printf("No post has been done yet.\n");
            }
        } else if (strcmp(command, "view_all.comments") == 0 || strcmp(command, "view_comments") == 0) {
            Comment* head = viewComments();
            printComments(head);
        }
        
        // 4. NAVIGATION Operations
        else if (strcmp(command, "next_post") == 0) {
            Post *post = nextPost();
            if (post) {
                printf("%s %s\n", post->username, post->caption);
            } 
            // Error output is handled internally by nextPost() if it returns NULL.
        } else if (strcmp(command, "previous_post") == 0) {
            Post *post = previousPost();
            if (post) {
                printf("%s %s\n", post->username, post->caption);
            }
            // Error output is handled internally by previousPost() if it returns NULL.
        }
        
        // 5. DELETE Operations (post, comment, reply)
        else if (strcmp(command, "delete") == 0) {
            scanf("%s", firstArg); 
            
            if (strcmp(firstArg, "post") == 0) {
                if (scanf("%d", &n) == 1) { 
                    if (!deletePost(n)) {
                        printf("Post %d does not exist or deletion failed.\n", n);
                    }
                }
            } else if (strcmp(firstArg, "comment") == 0) {
                if (scanf("%d", &n) == 1) {
                    if (!deleteComment(n)) {
                        printf("Comment %d does not exist on the last viewed post.\n", n);
                    }
                }
            } else if (strcmp(firstArg, "reply") == 0) { 
                if (scanf("%d %d", &n, &m) == 2) {
                    if (!deleteReply(n, m)) {
                        printf("Reply %d to comment %d does not exist.\n", m, n);
                    }
                }
            }
        }
        
        // 6. Unrecognized Command
        else {
            printf("Unrecognized command: %s\n", command);
        }
    }
    
    return 0;
}