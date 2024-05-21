#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

int height(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

AVLNode* createNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode* insertNode(AVLNode* node, int data) {
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

AVLNode* searchNode(AVLNode* root, int data, int* comparisons) {
    (*comparisons)++;
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->left, data, comparisons);
    return searchNode(root->right, data, comparisons);
}

int main() {
    AVLNode* root = NULL;
    root = insertNode(root, 50);
    root = insertNode(root, 60);
    root = insertNode(root, 70);
    root = insertNode(root, 72);
    root = insertNode(root, 73);
    root = insertNode(root, 75);
    root = insertNode(root, 78);
    root = insertNode(root, 80);
    root = insertNode(root, 90);

    printf("****** AVL 트리 출력 **************\n");
    inorder(root);
    printf("\n");

    int comparisons = 0;
    AVLNode* foundNode;

    foundNode = searchNode(root, 70, &comparisons);
    printf("AVL 트리에서 70 탐색: %d번째에 탐색 성공\n", comparisons);

    comparisons = 0;
    foundNode = searchNode(root, 72, &comparisons);
    printf("AVL 트리에서 72 탐색: %d번째에 탐색 성공\n", comparisons);

    comparisons = 0;
    foundNode = searchNode(root, 76, &comparisons);
    if (foundNode != NULL)
        printf("AVL 트리에서 76 탐색: %d번째에 탐색 성공\n", comparisons);
    else
        printf("AVL 트리에서 76 탐색: %d번째에 탐색 실패! 찾는 키가 없습니다!\n", comparisons);

    return 0;
}
