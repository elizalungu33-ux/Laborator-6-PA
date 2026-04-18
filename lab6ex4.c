#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void serializeHelper(struct TreeNode* root, char* str) {
    if (root == NULL) {
        strcat(str, "X,");
        return;
    }
    char buf[20];
    sprintf(buf, "%d,", root->val);
    strcat(str, buf);
    
    serializeHelper(root->left, str);
    serializeHelper(root->right, str);
}

char* serialize(struct TreeNode* root) {
    char* str = (char*)malloc(1000 * sizeof(char));
    str[0] = '\0'; 
    serializeHelper(root, str);
    return str;
}

struct TreeNode* deserializeHelper(char** data) {
    if (**data == '\0') return NULL; 
    char* comma = strchr(*data, ',');
    if (!comma) return NULL;
    *comma = '\0'; 
    
    char* token = *data;
    *data = comma + 1; 

    if (strcmp(token, "X") == 0) return NULL;
    
    struct TreeNode* node = createNode(atoi(token));
    node->left = deserializeHelper(data);
    node->right = deserializeHelper(data);
    return node;
}

struct TreeNode* deserialize(char* data) {
    char* ptr = data; 
    return deserializeHelper(&ptr);
}

// Afișare In-order
void inOrderTraversal(struct TreeNode* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->val);
        inOrderTraversal(node->right);
    }
}

int main() {
    printf("Construire arbore\n");
    struct TreeNode* root = buildTree();

    // 1. Arbore -> String
    char* serializedString = serialize(root);
    printf("\n-> Arbore serializat (transformat in text): %s\n", serializedString);

    // 2. String -> Arbore
    struct TreeNode* newRoot = deserialize(serializedString);
    
    printf("\n-> Traversare In-order a arborelui reconstruit: ");
    inOrderTraversal(newRoot);
    printf("\n");
    return 0;
}