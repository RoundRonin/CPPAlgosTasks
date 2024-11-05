// #include <climits>
// #include <cmath>
// #include <iostream>
// class ChairPairs {
//    private:
//     const static int HASH_TABLE_SIZE = 100003;

//     struct Entry {
//         int key;
//         int count;
//         Entry* next;
//     };

//     Entry* hashTable[HASH_TABLE_SIZE] = {nullptr};

//     int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

//     void insert(int key) {
//         int index = hashFunction(key);
//         Entry* entry = hashTable[index];
//         while (entry != nullptr) {
//             if (entry->key == key) {
//                 entry->count++;
//                 return;
//             }
//             entry = entry->next;
//         }
//         Entry* newEntry = new Entry;
//         newEntry->key = key;
//         newEntry->count = 1;
//         newEntry->next = hashTable[index];
//         hashTable[index] = newEntry;
//     }

//     int search(int key) {
//         int index = hashFunction(key);
//         Entry* entry = hashTable[index];
//         while (entry != nullptr) {
//             if (entry->key == key) {
//                 return entry->count;
//             }
//             entry = entry->next;
//         }
//         return 0;
//     }

//    public:
//     int findPairs(int N, int* S) {
//         int count = 0;

//         for (int i = 0; i < N; i++) {
//             int diff = S[i] - i;
//             count += search(diff);
//             insert(diff);
//         }

//         return count;
//     }
// };
// class HashTable {
//     int MULTIPLIER = 2;
//     int HASH_TABLE_SIZE;

//     struct Entry {
//         bool isEmpty = true;
//         int value;
//         int count;
//     };
//     Entry* hashTable;

//     int hashFunction(int key) {
//         key = (key >> 16) ^ key;
//         key = (key >> 8) ^ key;
//         key = (key >> 6) ^ key;
//         key = (key >> 16) ^ key;
//         key = (key >> 2) ^ key;
//         return key < 0 ? -key : key;
//     }
//     // int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

//     int probe(int index, int step, int iter) {
//         return (index + step * iter) % HASH_TABLE_SIZE;
//     }

//    public:
//     HashTable(int size) {
//         HASH_TABLE_SIZE = MULTIPLIER * size + 10;
//         hashTable = new Entry[HASH_TABLE_SIZE];
//         for (int i = 0; i < HASH_TABLE_SIZE; i++) {
//             hashTable[i] = {true, 0, 0};
//         }
//     }

//     void Insert(int key) {
//         int index = hashFunction(key);

//         int iter = 0;
//         Entry place = hashTable[probe(index, iter, iter)];
//         while (!place.isEmpty) {
//             if (place.value == key) {
//                 place.count++;
//                 return;
//             }
//             iter++;

//             place = hashTable[probe(index, iter, iter)];
//         }
//         hashTable[probe(index, iter, iter)].value = key;
//         hashTable[probe(index, iter, iter)].isEmpty = false;
//         hashTable[probe(index, iter, iter)].count = 1;
//     }

//     int Search(int key) {
//         int index = hashFunction(key);

//         int iter = 0;
//         Entry place = hashTable[probe(index, iter, iter)];
//         while (!place.isEmpty) {
//             if (place.value == key) return place.count;
//             iter++;

//             place = hashTable[probe(index, iter, iter)];
//         }
//         return -1;
//     }

//     int findPairs(int N, int* S) {
//         int count = 0;
//         for (int i = 0; i < N; i++) {
//             int diff = S[i] - i;
//             if (Search(diff) != -1) {  // Check if found
//                 count++;
//             }
//             Insert(diff);
//         }
//         return count;
//     }
// };

#include <climits>
#include <iostream>

// Hash table with hash table
class HashTableInner {
   private:
    int delim = 10;
    int HASH_TABLE_SIZE;

    struct Entry {
        int key;
        int count;
        Entry* next;
    };

    Entry** hashTable;

    int hashFunction(int key) { return abs(key) % HASH_TABLE_SIZE; }

   public:
    HashTableInner(int size) {
        HASH_TABLE_SIZE = size / delim + 10;
        hashTable = new Entry*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
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

class HashTable {
   private:
    int delim = 10;
    int HASH_TABLE_SIZE;
    HashTableInner** hashTable;

    int hashOne(int key) { return abs(key) % HASH_TABLE_SIZE; }

    void insert(int key) {
        int index = hashOne(key);
        if (hashTable[index] == nullptr) {
            hashTable[index] = new HashTableInner(HASH_TABLE_SIZE);
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
    HashTable(int size) {
        HASH_TABLE_SIZE = size / delim + 10;
        hashTable = new HashTableInner*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            hashTable[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            delete hashTable[i];
        }

        delete hashTable;
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

int logic() {
    int N;
    std::cin >> N;
    int* S = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> S[i];
    }

    HashTable cp(N);
    int result = cp.findPairs(N, S);

    std::cout << result << '\n';

    delete[] S;

    return 0;
}
// int logic() {
//     int N;
//     std::cin >> N;
//     int* S = new int[N];
//     for (int i = 0; i < N; i++) {
//         std::cin >> S[i];
//     }

//     HashTable set(N);
//     // ChairPairs set;
//     int result = set.findPairs(N, S);

//     std::cout << result << '\n';

//     delete[] S;

//     return 0;
// }