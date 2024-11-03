#include <climits>
#include <cmath>
#include <iostream>

class HashTable {
    int EMPTY = INT32_MIN;
    int delim = 1;

    int hashFunction(int key) {
        key = (key >> 16) ^ key;
        key = (key >> 8) ^ key;
        key = (key >> 6) ^ key;
        key = (key >> 16) ^ key;
        key = (key >> 2) ^ key;
        return key < 0 ? -key : key;
    }

    int probe(int index, int step, int iter) {
        return (index + step * iter) % HASH_TABLE_SIZE;
    }

   public:
    int HASH_TABLE_SIZE;
    int* hashTable;

    HashTable(int size) {
        HASH_TABLE_SIZE = 2 * size + 10;
        hashTable = new int[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            hashTable[i] = EMPTY;
        }
    }

    void Insert(int key) {
        int index = hashFunction(key);

        int iter = 0;
        int place = hashTable[probe(index, iter, iter)];
        while (place != EMPTY && iter != HASH_TABLE_SIZE * 4 * delim) {
            if (place == key) return;
            iter++;

            place = hashTable[probe(index, iter, iter)];
        }
        hashTable[probe(index, iter, iter)] = key;
    }

    bool Search(int key) {
        int index = hashFunction(key);

        int iter = 0;
        int place = hashTable[probe(index, iter, iter)];
        while (place != EMPTY) {
            if (place == key) return true;
            iter++;

            place = hashTable[probe(index, iter, iter)];
        }
        return false;
    }

    bool operator==(HashTable& other) {
        int value = 0;
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            value = hashTable[i];
            if (value == EMPTY) continue;
            if (!other.Search(value)) return false;
        }

        for (int i = 0; i < other.HASH_TABLE_SIZE; i++) {
            value = other.hashTable[i];
            if (value == EMPTY) continue;
            if (!Search(value)) return false;
        }

        return true;
    }
};

int logic() {
    int n;
    std::cin >> n;
    HashTable set1(n), set2(n);
    int element;

    for (int i = 0; i < n; ++i) {
        std::cin >> element;
        set1.Insert(element);
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> element;
        set2.Insert(element);
    }

    if (set1 == set2) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}