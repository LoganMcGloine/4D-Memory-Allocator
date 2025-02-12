#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//a 4 dimentional linked list
struct memory_block {
    char* data;
    struct memory_block* next;
    struct memory_block* prev;
    struct memory_block* up;
    struct memory_block* down;
};

#define MAX_QUEUE_SIZE 1000  // Adjust size as needed

void add_node(struct memory_block* node, char* data, int direction) {
    struct memory_block* new_node = (struct memory_block*)malloc(sizeof(struct memory_block));
    new_node->data = data;  // Make a copy of the string
    new_node->next = NULL;  
    new_node->prev = NULL;
    new_node->up = NULL;
    new_node->down = NULL;
    

    //add NewNode after node
    if (direction == 0) {
        new_node->prev = node;
        node->next = new_node;
    } else if (direction == 1) { //add NewNode before node
        node->prev = new_node;
        new_node->next = node;
    } else if (direction == 2) { //add NewNode above node
        node->up = new_node;
        new_node->down = new_node;
    } else if (direction == 3) { //add NewNode below node
        node->down = new_node;
        new_node->up = node;
    }
    printf("Node added successfully at memory address %p\n", new_node);
}

//a breadth first approach to adding a node to the list
void add_breadth_first(struct memory_block* head, char* data) {
    if (head == NULL) {
        return;
    }

    // Create a queue to store nodes
    struct memory_block* queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;
    
    // Add first node to queue
    queue[rear++] = head;
    
    // Process nodes in BFS order
    while (front < rear) {
        struct memory_block* current = queue[front++];
        
        // Check all directions for an empty slot
        if (current->next == NULL) {
            add_node(current, data, 0);
            return;
        } else {
            queue[rear++] = current->next;
        }
        
        if (current->prev == NULL) {
            add_node(current, data, 1);
            return;
        } else if (current->prev != head) {  // Avoid re-queuing head
            queue[rear++] = current->prev;
        }
        
        if (current->up == NULL) {
            add_node(current, data, 2);
            return;
        } else {
            queue[rear++] = current->up;
        }
        
        if (current->down == NULL) {
            add_node(current, data, 3);
            return;
        } else {
            queue[rear++] = current->down;
        }
        
        // Check if queue is full
        if (rear >= MAX_QUEUE_SIZE) {
            printf("Queue overflow - structure too large\n");
            return;
        }
    }
    
    // If we get here, no empty slots were found
    printf("No empty slots found in the structure\n");
}

//add a node to the end of the list
void add_node_end(struct memory_block* head, char* data) {
    //find the end of the list
    struct memory_block* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    //add the new node
    add_node(current, data, 0);
}

//add a node to the beginning of the list
void add_node_start(struct memory_block* head, char* data) {
    //find the start of the list
    struct memory_block* current = head;
    while (current->prev != NULL) {
        current = current->prev;
    }
    //add the new node
    add_node(current, data, 1);
}

void add_node_top(struct memory_block* head, char* data) {
    //find the top of the list
    struct memory_block* current = head;
    while (current->up != NULL) {
        current = current->up;
    }
    //add the new node
    add_node(current, data, 2);
}

void add_node_bottom(struct memory_block* head, char* data) {
    //find the bottom of the list
    struct memory_block* current = head;
    while (current->down != NULL) {
        current = current->down;
    }
    //add the new node
    add_node(current, data, 3);
}

struct memory_block* find_node_dfs(struct memory_block* head, char* data) {
    //a depth first search approach to searching for a node in a linked list

    //check if the list is empty
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }



    //check if the node is the head
    if (head->data != NULL && strcmp(head->data, data) == 0) {
        return head;
    }

    struct memory_block* queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;

    queue[rear++] = head;

    while (front < rear) { 
        struct memory_block* current = queue[front++];

        if (current->next->data == data) {
            return current->next;
        } else if (current->next != NULL) {
            queue[rear++] = current->next;
        }

        if (current->prev->data == data) {
            return current->prev;
        } else if (current->prev != NULL) {
            queue[rear++] = current->prev;
        }

        if (current->up->data == data) {
            return current->up;
        } else if (current->up != NULL) {
            queue[rear++] = current->up;
        }

        if (current->down->data == data) {
            return current->down;
        } else if (current->down != NULL) {
            queue[rear++] = current->down;
        }

        if (rear >= MAX_QUEUE_SIZE) {
            printf("Queue overflow - structure too large\n");
            return NULL;
        }
    }

    printf("Node not found\n");
    return NULL;
}

// Helper function to check if node was visited
static int was_visited(struct memory_block* node, struct memory_block** visited, int visited_count) {
    for (int i = 0; i < visited_count; i++) {
        if (visited[i] == node) return 1;
    }
    return 0;
}

void print_list_breadth_first(struct memory_block* head) {
    if (head == NULL) return;

    // Create queue for BFS
    struct memory_block* queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;

    // Create visited array to prevent cycles
    struct memory_block* visited[MAX_QUEUE_SIZE] = {NULL};
    int visited_count = 0;

    // Add first node
    queue[rear++] = head;
    visited[visited_count++] = head;

    while (front < rear) {
        struct memory_block* current = queue[front++];
        printf("%s\n", current->data);

        // Add unvisited neighbors to queue
        if (current->next && !was_visited(current->next, visited, visited_count)) {
            queue[rear++] = current->next;
            visited[visited_count++] = current->next;
        }
        if (current->prev && !was_visited(current->prev, visited, visited_count)) {
            queue[rear++] = current->prev;
            visited[visited_count++] = current->prev;
        }
        if (current->up && !was_visited(current->up, visited, visited_count)) {
            queue[rear++] = current->up;
            visited[visited_count++] = current->up;
        }
        if (current->down && !was_visited(current->down, visited, visited_count)) {
            queue[rear++] = current->down;
            visited[visited_count++] = current->down;
        }

        if (rear >= MAX_QUEUE_SIZE || visited_count >= MAX_QUEUE_SIZE) {
            printf("Queue or visited array is full\n");
            return;
        }
    }
}



void print_list_depth_first(struct memory_block* head) {
    static struct memory_block* visited[MAX_QUEUE_SIZE] = {NULL};
    static int visited_count = 0;
    
    // Reset visited array on first call
    if (head == NULL || was_visited(head, visited, visited_count)) {
        return;
    }
    
    // Mark current node as visited
    visited[visited_count++] = head;
    printf("%s\n", head->data);
    
    // Recursively visit all directions
    if (head->next) print_list_depth_first(head->next);
    if (head->prev) print_list_depth_first(head->prev);
    if (head->up) print_list_depth_first(head->up);
    if (head->down) print_list_depth_first(head->down);
    
    // Reset visited array when we're done with the root call
    if (visited_count == 1) {
        visited_count = 0;
    }
}

void print_list_next(struct memory_block* head) {
    struct memory_block* current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    printf("\n");
}

void print_list_previous(struct memory_block* head) {
    struct memory_block* current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->prev;
    }
    printf("\n");
}

void print_list_up(struct memory_block* head) {
    struct memory_block* current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->up;
    }
    printf("\n");
}

void print_list_down(struct memory_block* head) {
    struct memory_block* current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->down;
    }
    printf("\n");
}

void free_list(struct memory_block* head) {
     if (head == NULL) return;

    // Create queue for BFS
    struct memory_block* queue[MAX_QUEUE_SIZE];
    int front = 0;
    int rear = 0;

    // Create visited array to prevent cycles
    struct memory_block* visited[MAX_QUEUE_SIZE] = {NULL};
    int visited_count = 0;

    // Add first node
    queue[rear++] = head;
    visited[visited_count++] = head;

    while (front < rear) {
        struct memory_block* current = queue[front++];

        // Add unvisited neighbors to queue
        if (current->next && !was_visited(current->next, visited, visited_count)) {
            queue[rear++] = current->next;
            visited[visited_count++] = current->next;
        }
        if (current->prev && !was_visited(current->prev, visited, visited_count)) {
            queue[rear++] = current->prev;
            visited[visited_count++] = current->prev;
        }
        if (current->up && !was_visited(current->up, visited, visited_count)) {
            queue[rear++] = current->up;
            visited[visited_count++] = current->up;
        }
        if (current->down && !was_visited(current->down, visited, visited_count)) {
            queue[rear++] = current->down;
            visited[visited_count++] = current->down;
        }

        if (rear >= MAX_QUEUE_SIZE || visited_count >= MAX_QUEUE_SIZE) {
            printf("Queue or visited array is full\n");
            return;
        }
    }
    for (int i = 0; i < visited_count; i++) {
        printf("freeing %s\n", visited[i]->data);
        free(visited[i]);
    }
    printf("list freed\n");
}

void visualize_structure(struct memory_block* head) {
    if (head == NULL) return;
    
    printf("\nStructure Visualization:\n");
    printf("Legend: → (next), ← (prev), ↑ (up), ↓ (down)\n\n");
    
    struct memory_block* queue[MAX_QUEUE_SIZE];
    struct memory_block* visited[MAX_QUEUE_SIZE] = {NULL};
    int visited_count = 0;
    int front = 0, rear = 0;
    
    queue[rear++] = head;
    visited[visited_count++] = head;
    
    while (front < rear) {
        struct memory_block* current = queue[front++];
        printf("Node(%s): ", current->data);
        
        if (current->next && !was_visited(current->next, visited, visited_count)) {
            printf("→%s ", current->next->data);
            queue[rear++] = current->next;
            visited[visited_count++] = current->next;
        }
        if (current->prev && !was_visited(current->prev, visited, visited_count)) {
            printf("←%s ", current->prev->data);
            queue[rear++] = current->prev;
            visited[visited_count++] = current->prev;
        }
        if (current->up && !was_visited(current->up, visited, visited_count)) {
            printf("↑%s ", current->up->data);
            queue[rear++] = current->up;
            visited[visited_count++] = current->up;
        }
        if (current->down && !was_visited(current->down, visited, visited_count)) {
            printf("↓%s ", current->down->data);
            queue[rear++] = current->down;
            visited[visited_count++] = current->down;
        }
        printf("\n");
    }
}


int main() {
    // Create the head node
    struct memory_block* head = (struct memory_block*)malloc(sizeof(struct memory_block));
    head->data = "head";
    head->next = NULL;
    head->prev = NULL;
    head->up = NULL;
    head->down = NULL;

    // Add numbers as nodes
    char buffer[32];  // Buffer for converting integers to strings
    for (int i = 0; i < 10; i++) {
        snprintf(buffer, sizeof(buffer), "%d", i);  // Convert int to string
        add_breadth_first(head, strdup(buffer));    // Make a copy of the string
    }

    // Print the structure to verify
    // printf("\nPrinting breadth-first:\n");
    // print_list_breadth_first(head);

    printf("\nPrinting depth-first:\n");
    print_list_depth_first(head);

    free_list(head);
    return 0;
}