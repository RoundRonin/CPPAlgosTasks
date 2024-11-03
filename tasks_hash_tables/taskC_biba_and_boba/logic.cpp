#include <cmath>
#include <iostream>

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

int logic() {
    int N;
    std::cin >> N;
    int* S = new int[N];
    for (int i = 0; i < N; i++) {
        std::cin >> S[i];
    }

    ChairPairs cp;
    int result = cp.findPairs(N, S);

    std::cout << result << '\n';

    delete[] S;

    return 0;
}