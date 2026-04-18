//in cadrul acestui ex am utilizat tehnica pre-order

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* buildTree() {
    int val;
    printf("Introdu valoarea nodului (sau -1 pentru a lasa gol/NULL): ");
    scanf("%d", &val);

    if (val == -1) {
        return NULL;
    }

    struct TreeNode* root = createNode(val);

    printf("Pentru copilul STANG al lui %d -> ", val);
    root->left = buildTree();

    printf("Pentru copilul DREPT al lui %d -> ", val);
    root->right = buildTree();

    return root;
}

void visit(struct TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->val);
    }
}

int max_val(int a, int b) {
    return (a > b) ? a : b;
}

int checkHeight(struct TreeNode* node) {

    if (node == NULL) return 0; 
    
    int leftHeight = checkHeight(node->left);
    if (leftHeight == -1) return -1; 
    
    // Verificăm subarborele drept
    int rightHeight = checkHeight(node->right);
    if (rightHeight == -1) return -1; 
    
    if (abs(leftHeight - rightHeight) > 1) return -1;
    
    return max_val(leftHeight, rightHeight) + 1;
}

bool isBalanced(struct TreeNode* root) {
    return checkHeight(root) != -1;
}

// Traversare Pre-order
void preOrderTraversal(struct TreeNode* node) {
    if (node != NULL) {
        visit(node);                    // 1. Se vizitează nodul curent
        preOrderTraversal(node->left);  // 2. Se parcurge subarborele stâng
        preOrderTraversal(node->right); // 3. Se parcurge subarborele drept
    }
}

int main() {
    printf("Construirea arborelui binar\n");
    printf("Introduceti o valoare intreaga pentru nod, sau -1 daca nodul nu exista.\n\n");
    
    struct TreeNode* root = buildTree();
    printf("Traversare Pre-order: ");
    preOrderTraversal(root);
    printf("\n");

    if (isBalanced(root)) {
        printf("Arborele ESTE echilibrat (diferenta max de nivel intre subarbori este 1).\n");
    } else {
        printf("Arborele NU este echilibrat.\n");
    }

    return 0;
}
