
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    char name[30];
    struct Node *left, *right;
};

int comparisons = 0;

struct Node* create(int id, char name[]) {
    struct Node *n = malloc(sizeof(struct Node));
    n->id = id;
    strcpy(n->name, name);
    n->left = n->right = NULL;
    return n;
}

struct Node* insert(struct Node *root, int id, char name[]) {
    if (root == NULL)
        return create(id, name);

    if (id < root->id)
        root->left = insert(root->left, id, name);
    else if (id > root->id)
        root->right = insert(root->right, id, name);

    return root;
}

struct Node* search(struct Node *root, int id) {
    while (root != NULL) {
        comparisons++;
        if (id == root->id)
            return root;
        root = (id < root->id) ? root->left : root->right;
    }
    return NULL;
}

void inorder(struct Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d - %s\n", root->id, root->name);
        inorder(root->right);
    }
}

int height(struct Node *root) {
    if (!root) return 0;
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

int main() {
    struct Node *root = NULL;

    int ids[] = {
        115,108,124,103,111,120,128,101,105,109,
        113,118,122,126,130,102,104,106,110,112,
        114,117,119,121,123,125,127,129,107,116
    };

    char *names[] = {
        "Aarav","Ananya","Rahul","Priya","Arjun",
        "Neha","Rohan","Sneha","Kiran","Meera",
        "Vikram","Diya","Aditya","Isha","Varun",
        "Riya","Kabir","Pooja","Dev","Aditi",
        "Nikhil","Tara","Ishan","Maya","Kavya",
        "Aman","Sana","Ravi","Naina","Om"
    };

    for (int i = 0; i < 30; i++)
        root = insert(root, ids[i], names[i]);

    printf("STUDENT RECORDS (BST)\n");
    inorder(root);

    comparisons = 0;
    struct Node *result = search(root, 115);
    printf("\nSuccessful Search: ");
    if (result)
        printf("%d - %s", result->id, result->name);
    printf("\nComparisons: %d\n", comparisons);

    comparisons = 0;
    result = search(root, 999);
    printf("\nUnsuccessful Search: ");
    printf("%s", result ? "Found" : "Not Found");
    printf("\nComparisons: %d\n", comparisons);

    root = insert(root, 131, "Purnima");
    printf("\nAfter Insertion: 131 - Purnima\n");

    printf("BST Height: %d\n", height(root));

    return 0;
}






