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

void findDepthAndParent(struct TreeNode* node, int x, int y, int depth, struct TreeNode* parent, 
                        int* xDepth, int* yDepth, struct TreeNode** xParent, struct TreeNode** yParent) {
    if (node == NULL) return;
    
    if (node->val == x) {
        *xParent = parent;
        *xDepth = depth;
    } 

    else if (node->val == y) {
        *yParent = parent;
        *yDepth = depth;
    }
    
    findDepthAndParent(node->left, x, y, depth + 1, node, xDepth, yDepth, xParent, yParent);
    findDepthAndParent(node->right, x, y, depth + 1, node, xDepth, yDepth, xParent, yParent);
}

bool isCousins(struct TreeNode* root, int x, int y) {
    int xDepth = -1, yDepth = -1;
    struct TreeNode *xParent = NULL, *yParent = NULL;

    findDepthAndParent(root, x, y, 0, NULL, &xDepth, &yDepth, &xParent, &yParent);
    
    // Verificăm condiția de "verișori":
    // 1. Sunt la aceeași adâncime
    // 2. Nu au același părinte
    // 3. Să ne asigurăm că am găsit nodurile (părintele să nu fie NULL pentru rădăcină)
    return (xDepth == yDepth) && (xParent != yParent) && (xParent != NULL) && (yParent != NULL);
}

int main() {
    printf("Construire arbore\n");
    struct TreeNode* root = buildTree();

    int valX, valY;
    printf("\nIntrodu prima valoare (Nod X): ");
    scanf("%d", &valX);
    printf("Introdu a doua valoare (Nod Y): ");
    scanf("%d", &valY);

    if (isCousins(root, valX, valY)) {
        printf("Nodurile %d si %d SUNT verisori.\n", valX, valY);
    } else {
        printf("Nodurile %d si %d NU sunt verisori.\n", valX, valY);
    }

    return 0;
}