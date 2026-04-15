#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    struct Node* firstChild;
    struct Node* nextSibling;
} Node;

Node* createNode(char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}


Node* findNode(Node* root, char* name) {
    if (root == NULL) return NULL;

    if (strcmp(root->name, name) == 0)
        return root;

    Node* found = findNode(root->firstChild, name);
    if (found != NULL)
        return found;

    return findNode(root->nextSibling, name);
}


void addChild(Node* parent, char* name) {
    if (parent == NULL) {
        printf("Parent not found!\n");
        return;
    }

    Node* newNode = createNode(name);

    if (parent->firstChild == NULL) {
        parent->firstChild = newNode;
    } else {
        Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = newNode;
    }

    printf("Directory '%s' added under '%s'.\n", name, parent->name);
}

void displayTree(Node* root, int depth) {
    if (root == NULL) return;

    for (int i = 0; i < depth; i++)
        printf("  |--");

    printf("%s\n", root->name);

    displayTree(root->firstChild, depth + 1);
    displayTree(root->nextSibling, depth);
}

int main() {
    Node* root = NULL;
    int choice;
    char parentName[50], childName[50];

    while (1) {
        printf("\n--- File System Menu ---");
        printf("\n1. Create Root");
        printf("\n2. Insert a child");
        printf("\n3. Display");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root != NULL) {
                    printf("Root already exists!\n");
                } else {
                    printf("Enter root name: ");
                    scanf("%s", childName);
                    root = createNode(childName);
                    printf("Root directory '%s' created.\n", childName);
                }
                break;

            case 2:
                if (root == NULL) {
                    printf("Create root first!\n");
                    break;
                }

                printf("Enter parent directory: ");
                scanf("%s", parentName);

                Node* parent = findNode(root, parentName);

                if (parent == NULL) {
                    printf("Parent directory not found!\n");
                } else {
                    printf("Enter child directory: ");
                    scanf("%s", childName);
                    addChild(parent, childName);
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("Directory is empty!\n");
                } else {
                    printf("\nDirectory Structure:\n");
                    displayTree(root, 0);
                }
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
