#include <cmath>
#include <iostream>

class HashTableInner {
   private:
    int HASH_TABLE_SIZE = 100;

    struct Entry {
        int key;
        int count;
        Entry* next;
    };

    Entry** hashTable;

    int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

   public:
    HashTableInner(int size) : HASH_TABLE_SIZE(size) {
        hashTable = new Entry*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    ~HashTableInner() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            Entry* entry = hashTable[i];
            while (entry != nullptr) {
                Entry* next = entry->next;
                delete entry;
                entry = next;
            }
        }
        delete[] hashTable;
    }

    void insert(int key) {
        int index = hashFunction(key);
        Entry* entry = hashTable[index];
        while (entry != nullptr) {
            if (entry->key == key) {
                entry->count++;
                return;
            }
            entry = entry->next;
        }
        Entry* newEntry = new Entry;
        newEntry->key = key;
        newEntry->count = 1;
        newEntry->next = hashTable[index];
        hashTable[index] = newEntry;
    }

    int search(int key) {
        int index = hashFunction(key);
        Entry* entry = hashTable[index];
        while (entry != nullptr) {
            if (entry->key == key) {
                return entry->count;
            }
            entry = entry->next;
        }
        return 0;
    }
};

class HashTableOfHashTables {
   private:
    int HASH_TABLE_SIZE;
    HashTableInner** hashTable;

    int hashOne(int key) { return abs(key) % HASH_TABLE_SIZE; }

    struct HistoryNode {
        int value;
        HistoryNode* nextNode;
    };

    HistoryNode* FirstEntry;
    HistoryNode* LastEntry;
    int historySize;

    void updateHistory(int value) {
        HistoryNode* newNode = new HistoryNode{value, nullptr};
        if (FirstEntry == nullptr) {
            FirstEntry = LastEntry = newNode;
        } else {
            LastEntry->nextNode = newNode;
            LastEntry = newNode;
        }
        historySize++;
    }

   public:
    HashTableOfHashTables(int N) {
        HASH_TABLE_SIZE =
            1 + static_cast<int>(sqrt(static_cast<double>(N))) / 100;

        hashTable = new HashTableInner*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
        FirstEntry = LastEntry = nullptr;
        historySize = 0;
    }

    ~HashTableOfHashTables() {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            if (hashTable[i] != nullptr) {
                delete hashTable[i];
            }
        }
        delete[] hashTable;
    }

    void insert(int key) {
        int index = hashOne(key);
        if (hashTable[index] == nullptr) {
            hashTable[index] = new HashTableInner(HASH_TABLE_SIZE);
        }
        hashTable[index]->insert(key);

        updateHistory(key);
    }

    int search(int key) {
        int index = hashOne(key);
        if (hashTable[index] == nullptr) {
            return 0;  // Not found
        }
        return hashTable[index]->search(key);
    }

    bool operator==(HashTableOfHashTables& other) {
        HistoryNode* currentNode = FirstEntry;
        while (currentNode != nullptr) {
            if (!other.search(currentNode->value)) return false;
            currentNode = currentNode->nextNode;
        }
        return true;
    }
};

// AVL TREE

class AVLTree {
    struct TreeNode {
        int data;
        TreeNode *left, *right;
        int height;
        TreeNode(int val)
            : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    TreeNode* insert(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
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

   public:
    TreeNode* root = nullptr;

    void insert(int key) { root = insert(root, key); }
};

// Alternative with a good hash function
class HashTable {
   private:
    int HASH_TABLE_SIZE;

    struct Entry {
        int key;
        int count;
        Entry* next;
    };

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

    Entry** hashTable;

    // int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }
    int hashFunction(int key, uint16_t seed = 0) {
        uint16_t h = seed;
        h ^= static_cast<uint32_t>(key);
        h ^= h >> 13;
        h *= 0x85ebca6b;
        h ^= h >> 10;
        h *= 0xc2b2ae35;
        h ^= h >> 13;
        return (1 + abs(static_cast<int>(h))) % HASH_TABLE_SIZE;
    }

   public:
    HashTable(int size) : HASH_TABLE_SIZE(sqrt(size)) {
        hashTable = new Entry*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    void insert(int key) {
        int index = hashFunction(key);
        Entry* entry = hashTable[index];
        while (entry != nullptr) {
            if (entry->key == key) {
                entry->count++;
                return;
            }
            entry = entry->next;
        }
        Entry* newEntry = new Entry;
        newEntry->key = key;
        newEntry->count = 1;
        newEntry->next = hashTable[index];
        hashTable[index] = newEntry;

        updateHistory(key);
    }

    int search(int key) {
        int index = hashFunction(key);
        Entry* entry = hashTable[index];
        while (entry != nullptr) {
            if (entry->key == key) {
                return entry->count;
            }
            entry = entry->next;
        }
        return -1;
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