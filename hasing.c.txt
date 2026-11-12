#include <stdio.h>
#include <string.h>

#define SIZE 50

struct Student {
    int id;
    char name[30];
    int used;
};

struct Student table[SIZE];
int collisions = 0, comparisons = 0;

int hash(int id) {
    return id % 10;
}

void insert(int id, char name[]) {
    int i = hash(id);

    while (table[i].used) {
        if (table[i].id == id) return;
        collisions++;
        i = (i + 1) % SIZE;
    }

    table[i].id = id;
    strcpy(table[i].name, name);
    table[i].used = 1;
}

struct Student* search(int id) {
    int i = hash(id), count = 0;
    comparisons = 0;

    while (table[i].used && count < SIZE) {
        comparisons++;
        if (table[i].id == id)
            return &table[i];

        i = (i + 1) % SIZE;
        count++;
    }
    return NULL;
}

void display() {
    printf("STUDENT RECORDS (HASHING)\n");
    for (int i = 0; i < SIZE; i++)
        if (table[i].used)
            printf("Index %d: %d - %s\n",
                   i, table[i].id, table[i].name);
}

int main() {
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
        insert(ids[i], names[i]);

    display();

    printf("\nCollisions: %d\n", collisions);

    struct Student *s = search(115);
    printf("\nSuccessful Search: ");
    if (s) printf("%d - %s", s->id, s->name);
    printf("\nComparisons: %d\n", comparisons);

    s = search(999);
    printf("\nUnsuccessful Search: ");
    printf("%s", s ? "Found" : "Not Found");
    printf("\nComparisons: %d\n", comparisons);

    insert(131, "Purnima");
    printf("\nAfter Insertion: 131 - Purnima\n");
    printf("Total Collisions: %d\n", collisions);

    return 0;
}
