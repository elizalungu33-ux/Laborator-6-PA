//in cadrul acestui exercitiu am folosit tehnica post-order
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

struct TreeNode* findNode(struct TreeNode* node, int target) {
    if (node == NULL) return NULL;
    if (node->val == target) return node;
    
    struct TreeNode* leftSearch = findNode(node->left, target);
    if (leftSearch != NULL) return leftSearch; 
    
    return findNode(node->right, target); 
}

void visit(struct TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->val);
    }
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
   
    if (root == NULL || root == p || root == q) {
        return root;
    }
    
    struct TreeNode* leftSearch = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* rightSearch = lowestCommonAncestor(root->right, p, q);

    if (leftSearch != NULL && rightSearch != NULL) {
        return root;
    }
    
    return (leftSearch != NULL) ? leftSearch : rightSearch;
}

// Traversare Post-order (Stânga, Dreapta, Rădăcină)
void postOrderTraversal(struct TreeNode* node) {
    if (node != NULL) {
        postOrderTraversal(node->left);  // 1. Subarbore stânga
        postOrderTraversal(node->right); // 2. Subarbore dreapta
        visit(node);                     // 3. Vizitare nod
    }
}

int main() {
    printf("Construire arbore\n");
    struct TreeNode* root = buildTree();

    printf("\nTraversare Post-order: ");
    postOrderTraversal(root);
    printf("\n\n");

    int valP, valQ;
    printf("Introdu prima valoare pentru cautare: ");
    scanf("%d", &valP);
    printf("Introdu a doua valoare pentru cautare: ");
    scanf("%d", &valQ);

    struct TreeNode* p = findNode(root, valP);
    struct TreeNode* q = findNode(root, valQ);

    if (p == NULL || q == NULL) {
        printf("Unul sau ambele noduri nu exista in arbore!\n");
    } else {
        struct TreeNode* lca = lowestCommonAncestor(root, p, q);
        if (lca != NULL) {
            printf("Cel mai apropiat stramos comun pentru %d si %d este: %d\n", p->val, q->val, lca->val);
        }
    }

    return 0;
}