#include <cmath>
#include <iostream>
#include <string>

// Hash table using AVL BST
class HashTable {
    struct TreeNode {
        int data;
        int counter = 1;
        TreeNode* left;
        TreeNode* right;
        int height;
        TreeNode(int val)
            : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    TreeNode* insertNode(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);

        if (key < node->data) {
            node->left = insertNode(node->left, key);
        } else if (key > node->data) {
            node->right = insertNode(node->right, key);
        } else {
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));
        return balance(node);
    }

    int height(TreeNode* node) { return node ? node->height : 0; }

    int getBalance(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    TreeNode* balance(TreeNode* node) {
        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* find(TreeNode* root, int data) {
        while (root) {
            if (data < root->data) {
                root = root->left;
            } else if (data > root->data) {
                root = root->right;
            } else {
                return root;
            }
        }
        return nullptr;
    }

    struct HistoryNode {
        int value;
        HistoryNode* nextNode;
    };

    HistoryNode* FirstEntry = nullptr;
    HistoryNode* LastEntry = nullptr;

    void updateHistory(int value) {
        HistoryNode* newNode = new HistoryNode{value, nullptr};
        if (FirstEntry == nullptr) {
            FirstEntry = LastEntry = newNode;
        } else {
            LastEntry->nextNode = newNode;
            LastEntry = newNode;
        }
    }

    int HASH_TABLE_SIZE;
    TreeNode** hashTable;

    int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

   public:
    HashTable(int size) : HASH_TABLE_SIZE(sqrt(size)) {
        hashTable = new TreeNode*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            deleteSubTree(hashTable[i]);
        }
        delete[] hashTable;
    }

    void deleteSubTree(TreeNode* root) {
        if (root == nullptr) return;
        deleteSubTree(root->left);
        deleteSubTree(root->right);
        delete root;
    }

    void insert(int key) {
        int index = hashFunction(key);
        hashTable[index] = insertNode(hashTable[index], key);
        updateHistory(key);
    }

    int search(int key) {
        int index = hashFunction(key);
        TreeNode* found = find(hashTable[index], key);
        return found ? found->data : -1;  // Sentinel value for not found
    }

    bool operator==(HashTable& other) {
        HistoryNode* currentNode = FirstEntry;
        while (currentNode != nullptr) {
            if (other.search(currentNode->value) == -1) return false;
            currentNode = currentNode->nextNode;
        }
        return true;
    }
};