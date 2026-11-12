#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id, height;
    char name[30];
    struct Node *left, *right;
};

int comparisons = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(struct Node *n) {
    return n ? n->height : 0;
}

struct Node* create(int id, char name[]) {
    struct Node *n = malloc(sizeof(struct Node));
    n->id = id;
    strcpy(n->name, name);
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

int balance(struct Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;
    x->right = y;
    y->left = t;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;
    y->left = x;
    x->right = t;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

struct Node* insert(struct Node *root, int id, char name[]) {
    if (!root) return create(id, name);

    if (id < root->id)
        root->left = insert(root->left, id, name);
    else if (id > root->id)
        root->right = insert(root->right, id, name);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && id < root->left->id)
        return rightRotate(root);

    if (b < -1 && id > root->right->id)
        return leftRotate(root);

    if (b > 1 && id > root->left->id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && id < root->right->id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* search(struct Node *root, int id) {
    while (root) {
        comparisons++;
        if (id == root->id) return root;
        root = id < root->id ? root->left : root->right;
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

    printf("STUDENT RECORDS (AVL TREE)\n");
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
    printf("AVL Tree Height: %d\n", height(root));

    return 0;
}
