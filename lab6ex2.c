//in cadrul acestui ex am folosit tehnica in-order

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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
    printf("Introdu valoarea (sau -1 pentru gol/NULL): ");
    scanf("%d", &val);

    if (val == -1) return NULL;

    struct TreeNode* root = createNode(val);
    
    printf("Pt copilul STANG al lui %d -> ", val);
    root->left = buildTree();
    
    printf("Pt copilul DREPT al lui %d -> ", val);
    root->right = buildTree();

    return root;
}

void visit(struct TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->val);
    }
}

bool isValidBSTHelper(struct TreeNode* node, long min, long max) {
    if (node == NULL) return true; 
    
    if (node->val <= min || node->val >= max) return false;
    
    return isValidBSTHelper(node->left, min, node->val) && 
           isValidBSTHelper(node->right, node->val, max);
}

bool isValidBST(struct TreeNode* root) {
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
}

// Traversare In-order (Stânga, Rădăcină, Dreapta)
void inOrderTraversal(struct TreeNode* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);  // 1. Parcurgere subarbore stânga
        visit(node);                   // 2. Vizitare nod
        inOrderTraversal(node->right); // 3. Parcurgere subarbore dreapta
    }
}

int main() {
    printf("Construire arbore\n");
    struct TreeNode* root = buildTree();
    printf("Traversare In-order (daca e BST, numerele vor fi in ordine crescatoare): ");
    inOrderTraversal(root);
    printf("\n");

    if (isValidBST(root)) {
        printf("Arborele ESTE un Binary Search Tree valid.\n");
    } else {
        printf("Arborele NU este un Binary Search Tree.\n");
    }

    return 0;
}