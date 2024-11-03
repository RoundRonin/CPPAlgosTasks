#include <cmath>
#include <iostream>

// Hash table with hash table
class HashTableInner {
   private:
    const static int HASH_TABLE_SIZE = 100003;

    struct Entry {
        int key;
        int count;
        Entry* next;
    };

    Entry* hashTable[HASH_TABLE_SIZE] = {nullptr};

    int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

   public:
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
    const static int HASH_TABLE_SIZE = 100007;
    HashTableInner* hashTable[HASH_TABLE_SIZE] = {nullptr};

    int hashOne(int key) { return abs(key) % HASH_TABLE_SIZE; }

    void insert(int key) {
        int index = hashOne(key);
        if (hashTable[index] == nullptr) {
            hashTable[index] = new HashTableInner();
            // std::cout << "Initialized HashTableInner at index " << index
            //           << std::endl;
        }
        hashTable[index]->insert(key);
    }

    int search(int key) {
        int index = hashOne(key);
        if (hashTable[index] == nullptr) {
            return 0;  // Not found
        }
        return hashTable[index]->search(key);
    }

   public:
    ~HashTableOfHashTables() {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            delete hashTable[i];
        }
    }

    int findPairs(int N, int* S) {
        int count = 0;
        for (int i = 0; i < N; i++) {
            int diff = S[i] - i;
            count += search(diff);
            insert(diff);
        }
        return count;
    }
};

// Probing with a second hash
class HashTable {
   private:
    const static int HASH_TABLE_SIZE = 100007;
    int hashTable[HASH_TABLE_SIZE];

    int hashOne(int key) { return abs(key) % HASH_TABLE_SIZE; }
    int hashTwo(int key) {
        return 1 + HASH_TABLE_SIZE - (key % (HASH_TABLE_SIZE - 1));
    }
    // int hashTwo(int key) { return 1 + (key % (HASH_TABLE_SIZE - 1));
    // }

    int probingCalculation(int index, int probingIndex, int iteration) {
        return (index + probingIndex * iteration) % HASH_TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashOne(key);
        int probingIndex = hashTwo(key);
        int insertionIndex = index;

        for (int i = 0; i < HASH_TABLE_SIZE * 3; i++) {
            insertionIndex = probingCalculation(index, probingIndex, i);
            if (hashTable[insertionIndex] == INT32_MIN) {
                hashTable[insertionIndex] = key;
                break;
            }
        }
    }

    int search(int key) {
        int index = hashOne(key);
        int probingIndex = hashTwo(key);
        int checkIndex = index;

        for (int i = 0; i < HASH_TABLE_SIZE * 3; i++) {
            checkIndex = probingCalculation(index, probingIndex, i);
            if (hashTable[checkIndex] == INT32_MIN) {
                return 0;  // Key not found
            }
            if (hashTable[checkIndex] == key) {
                return hashTable[checkIndex];  // Key found
            }
        }
        return 0;
    }

   public:
    HashTable() {
        // Insurting values corresponding to none values
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            hashTable[i] = INT32_MIN;
        }
    };

    int findPairs(int N, int* S) {
        int count = 0;

        for (int i = 0; i < N; i++) {
            int diff = S[i] - i;
            count += search(diff);
            insert(diff);
        }

        return count;
    }
};

class ChairPairs {
   private:
    const static int HASH_TABLE_SIZE = 100003;

    struct Entry {
        int key;
        int count;
        Entry* next;
    };

    Entry* hashTable[HASH_TABLE_SIZE] = {nullptr};

    int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

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

   public:
    int findPairs(int N, int* S) {
        int count = 0;

        for (int i = 0; i < N; i++) {
            int diff = S[i] - i;
            count += search(diff);
            insert(diff);
        }

        return count;
    }
};