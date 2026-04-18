//Realizați o funcție prin care să scrieți arborele ca într-o oglindă. (Mirror tree) 2P
//Realizați o funcție prin care să adunați toate valorile din arbore. 2P

#include <stdio.h>
#include <stdlib.h>
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

//functia de adunare
int sumTree(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    
    return node->val + sumTree(node->left) + sumTree(node->right);
}

//functia de oglindire
void mirrorTree(struct TreeNode* node) {

    if (node == NULL) {
        return;
    }
    
    struct TreeNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
    
    mirrorTree(node->left);
    mirrorTree(node->right);
}

void inOrderTraversal(struct TreeNode* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->val);
        inOrderTraversal(node->right);
    }
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

int main() {
    printf("=== Construire Arbore ===\n");
    struct TreeNode* root = buildTree();

    int sumaTotala = sumTree(root);
    printf("Suma tuturor valorilor din arbore este: %d\n", sumaTotala);

    printf("Arborele INAINTE de oglindire (Traversare In-order): ");
    inOrderTraversal(root);
    printf("\n");

    mirrorTree(root);
    
    printf("Arborele DUPA oglindire (Traversare In-order):   ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}


