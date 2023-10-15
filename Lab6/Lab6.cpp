#include <stdio.h>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}
// Функция для получения максимума из двух чисел
int max(int a, int b) {
    return (a > b) ? a : b;
}
// Функция для создания нового узла в AVL-дереве
Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}
// Функция для выполнения правого поворота поддерева с корнем в узле y
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Выполнение поворота
    x->right = y;
    y->left = T2;

    // Обновление высоты узлов
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Новый корень поддерева
    return x;
}
// Функция для выполнения левого поворота поддерева с корнем в узле x
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Выполнение поворота
    y->left = x;
    x->right = T2;

    // Обновление высоты узлов
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Новый корень поддерева
    return y;
}
// Функция для получения баланса узла
int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
Node* Balanced(Node* tree, int key) {
    // Шаг 3: Получение фактора баланса текущего узла
    int balance = getBalance(tree);

    // Шаг 4: Если текущий узел несбалансирован, есть четыре случая

    // Левый-левый случай
    if (balance > 1 && key < tree->left->key)
        return rotateRight(tree);

    // Правый-правый случай
    if (balance < -1 && key > tree->right->key)
        return rotateLeft(tree);

    // Лево-правый случай
    if (balance > 1 && key > tree->left->key) {
        tree->left = rotateLeft(tree->left);
        return rotateRight(tree);
    }

    // Право-левый случай
    if (balance < -1 && key < tree->right->key) {
        tree->right = rotateRight(tree->right);
        return rotateLeft(tree);
    }

    // Возвращаем корень поддерева (без изменений, если он сбалансирован)
    return tree;
}
// Функция для вставки ключа в AVL - дерево
Node * insert(Node * root, int key) {
    // Шаг 1: Выполнение стандартной вставки BST
    if (root == nullptr)
        return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // Дубликаты ключей не разрешены

    // Шаг 2: Обновление высоты текущего узла
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Шаг 3: Получение фактора баланса текущего узла
    int balance = getBalance(root);

    // Шаг 4: Если текущий узел несбалансирован, есть четыре случая

    // Левый-левый случай
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // Правый-правый случай
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // Лево-правый случай
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Право-левый случай
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    // Возвращаем корень поддерева (без изменений, если он сбалансирован)
    return Balanced(root, key);
}

void PrintPoly(Node* root) {
    if (!root) {
        printf("_");
        return;
    }

    printf("(%d", root->key);
    printf(" ");
    PrintPoly(root->left);
    printf(" ");
    PrintPoly(root->right);
    printf(") ");
}
void Print(Node * root) {
    if (!root) return;
    printf("%d ", root->key);
}


int main()
{
    system("chcp 1251 > null");
    Node* root = createNode(78);
    root = insert(root, 1);
    root = insert(root, 1);
    PrintPoly(root);
    return 0;

}
