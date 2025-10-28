# CSPC32: Assignment 2 - Task #2a (Social Media Platform ADT)

Hi! This project implements the core **Social Media Platform ADT** in C, built entirely on **singly linked lists and pointers** as required for my Task #2a of the Data Structures assignment. It handles posts, comments, and includes the full implementation for replies.

## Project Structure (Keeping it Modular)


| Component | Files | What it Does |
| :--- | :--- | :--- |
| **Data Models** | `post.h/c`, `comment.h/c`, `reply.h/c` | Defines the actual data structures and implements their essential `create` and memory **cleanup** functions. |
| **Core Logic** | `platform.h`, `platform.c` | Holds the global state (`platform_instance`), manages the linked list of posts, and handles complex operations like navigation (`nextPost`, `previousPost`) and deletion. |
| **Interface** | `main.c` | Our simple command-line interface that parses user input and calls the appropriate functions from `platform.c`. |
| **Build** | `Makefile` | Automates the compilation process. |

## How to Build and Run 🚀

Assuming you have `gcc` installed, you can build and run the project from your terminal:

1.  **Compile the Project:**
    ```bash
    make
    ```
2.  **Start the Program:**
    ```bash
    ./social_platform
    ```
3.  **Use It:** Enter commands like those in the Sample I/O (e.g., `add post user1 caption1`).

***

## 4. Features Implemented (Command Reference)

Once the program is running, the following commands are available through the command-line interface:

| Category | Command Syntax | Description |
| :--- | :--- | :--- |
| **Setup** | `create_platform` | Initializes the global platform instance. |
| **Posts** | `add post <username> <caption_text>` | Creates a new post and adds it to the list (becomes the most recent). |
| | `view_post <n>` | Displays the **$n^{th}$ recent post** and sets it as the `lastViewedPost`. |
| | `delete post <n>` | Deletes the **$n^{th}$ recent post** and all its associated comments/replies. |
| **Navigation** | `current_post` | Displays the current `lastViewedPost`. |
| | `next_post` | Views the post posted **just before** the `lastViewedPost`. |
| | `previous_post` | Views the post posted **just after** the `lastViewedPost`. |
| **Comments** | `add comment <user> <content>` | Adds a comment to the current `lastViewedPost`. |
| | `view_all.comments` or `view_comments` | Displays all comments (and replies) for the current `lastViewedPost`. |
| | `delete comment <n>` | Deletes the **$n^{th}$ recent comment** from the current post. |
| **Replies (Bonus)** | `add reply <user> <content> <n>` | Adds a reply to the **$n^{th}$ recent comment** on the current post. |
| | `delete reply <n> <m>` | Deletes the **$m^{th}$ recent reply** from the **$n^{th}$ recent comment**. |

***

## 5. Design Notes and Key Assumptions 💡

We made conscious decisions regarding performance and data integrity:

* **LATEST at HEAD Strategy:** All primary lists (`posts`, `comments`, `replies`) are implemented using **head insertion**. This strategy ensures that **adding a new element is an $O(1)$ constant-time operation**, regardless of how large the list grows.
* **String Safety:** The helper function **`safe_strdup`** is used everywhere to **deeply copy** strings onto the heap. This prevents memory errors like **dangling pointers** when input buffers are overwritten.

***

