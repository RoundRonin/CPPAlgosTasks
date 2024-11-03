#include <climits>
#include <cmath>
#include <iostream>

// Hash table with BST implementation
class HashTable {
    struct TreeNode {
        int data;
        TreeNode *left, *right;
        TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    TreeNode* insertNode(TreeNode* root, int data) {
        if (!root) {
            // std::cout << "Inserting " << data << std::endl;
            return new TreeNode(data);
        }
        if (data < root->data) {
            root->left = insertNode(root->left, data);
        } else if (data > root->data) {
            root->right = insertNode(root->right, data);
        } else {
            // std::cout << "Duplicate " << data << " not inserted" <<
            // std::endl;
        }
        return root;
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

    const static int HASH_TABLE_SIZE = 100003;
    TreeNode* hashTable[HASH_TABLE_SIZE] = {nullptr};

    int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

   public:
    void insert(int key) {
        int index = hashFunction(key);
        hashTable[index] = insertNode(hashTable[index], key);
    }

    int search(int key) {
        int index = hashFunction(key);
        TreeNode* found = find(hashTable[index], key);
        return found ? found->data : -1;  // Sentinel value for not found
    }

    int findPairs(int N, int* S) {
        int count = 0;
        for (int i = 0; i < N; i++) {
            int diff = S[i] - i;
            if (search(diff) != -1) {  // Check if found
                count++;
            }
            insert(diff);
        }
        return count;
    }
};

int logic() {
    int N;
    std::cin >> N;
    int* S = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> S[i];
    }

    HashTable ht;
    int result = ht.findPairs(N, S);

    std::cout << result << '\n';

    delete[] S;

    return 0;
}