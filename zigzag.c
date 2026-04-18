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

int maxZigZag = 0;

void dfs_simplu(struct TreeNode* node, int directie, int pasi) {
    if (node == NULL) {
        return;
    }

    if (pasi > maxZigZag) {
        maxZigZag = pasi;
    }

    if (directie == 0) {
        dfs_simplu(node->left, 1, 1);  
        dfs_simplu(node->right, 2, 1); 
    }

    else if (directie == 1) {
        
        dfs_simplu(node->right, 2, pasi + 1);
        dfs_simplu(node->left, 1, 1);
    }

    else if (directie == 2) {
        dfs_simplu(node->left, 1, pasi + 1);
        dfs_simplu(node->right, 2, 1);
    }
}

int longestZigZag(struct TreeNode* root) {
    maxZigZag = 0; 
    dfs_simplu(root, 0, 0);
    return maxZigZag;
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
    printf("Construire arbore\n");
    struct TreeNode* root = buildTree();

    int rezultat = longestZigZag(root);
    
    printf("\nCea mai lunga cale ZigZag din arbore este: %d\n", rezultat);

    return 0;
}