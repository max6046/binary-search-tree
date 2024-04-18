#include <stdio.h>
#include <stdlib.h>

// Definition of a Node in the BST
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node with given data
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to search for a value in the in-order array
int search(int inOrder[], int inStart, int inEnd, int value) {
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to construct a BST from in-order and post-order arrays
Node* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int *postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    // Create a new node with the current element in post-order array
    int data = postOrder[*postIndex];
    Node *node = createNode(data);
    (*postIndex)--;

    // If the node has no children, return the node
    if (inStart == inEnd) {
        return node;
    }

    // Find the index of the current node's data in the in-order array
    int inIndex = search(inOrder, inStart, inEnd, data);

    // Recursively construct the right and left sub-trees
    node->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    node->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to perform breadth-first-search (BFS) traversal of the BST
void bfs_traversal(Node *root) {
    if (root == NULL) {
        return;
    }

    // Queue to hold nodes for BFS traversal
    Node *queue[100];
    int front = 0, rear = 0;

    // Enqueue the root node
    queue[rear++] = root;

    while (front < rear) {
        // Dequeue the front node
        Node *currentNode = queue[front++];

        // Print the data of the current node
        printf("%d ", currentNode->data);

        // Enqueue the left child if exists
        if (currentNode->left) {
            queue[rear++] = currentNode->left;
        }

        // Enqueue the right child if exists
        if (currentNode->right) {
            queue[rear++] = currentNode->right;
        }
    }

    printf("\n");
}

// Main function
int main() {
    // Given arrays and length
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int length = sizeof(inOrder) / sizeof(inOrder[0]);

    // Start postIndex at the end of the post-order array
    int postIndex = length - 1;

    // Construct the BST
    Node *root = bst_construct(inOrder, postOrder, 0, length - 1, &postIndex);

    // Perform BFS traversal and print the elements
    bfs_traversal(root);

    // Free the memory for the BST if desired
    // Freeing memory is important, but is not explicitly asked for in the question.

    return 0;
}

