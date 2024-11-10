#include <iostream>
#include <string>

class CuckooHashing {
    const std::string EMPTY = "";
    const int COUNTER_MAX = 100;

    struct Entry {
        std::string value = "";
        int count = 0;
    };

    int Size;
    Entry *Table;

    int HASH_VAR1 = 7;
    int HASH_VAR2 = 5;

    int hash1(const std::string &key) {
        unsigned int hash = 5381;
        for (char ch : key) hash = ((hash << 5) + hash) + ch;
        // hash = hash >> HASH_VAR1;
        return hash % Size;
    }

    int hash2(const std::string &key) {
        unsigned int hash = 0;
        for (char ch : key) hash = ch + (hash << 6) + (hash << 16) - hash;
        // hash = hash >> HASH_VAR2;
        return hash % Size;
    }

    void put(Entry entry) {
        int index1 = hash1(entry.value);
        int index2 = hash2(entry.value);

        if (Table[index1].value == EMPTY) {
            Table[index1] = entry;
            return;
        } else if (Table[index1].value == entry.value) {
            Table[index1].count++;
            return;
        } else if (Table[index2].value == EMPTY) {
            Table[index2] = entry;
            return;
        } else if (Table[index2].value == entry.value) {
            Table[index2].count++;
        }

        Entry temp = entry;
        int index = index1;
        int counter = 0;
        Entry displaced;

        while (counter <= COUNTER_MAX) {
            int altIndex = (index == hash1(temp.value)) ? hash2(temp.value)
                                                        : hash1(temp.value);

            if (Table[altIndex].value == EMPTY) {
                Table[altIndex] = entry;
                return;
            } else if (Table[altIndex].value == temp.value) {
                Table[altIndex].count++;
                return;
            }

            // Swap and continue
            displaced = Table[altIndex];
            Table[altIndex] = temp;
            temp = displaced;
            index = altIndex;
            counter++;
        }

        // If we exit the loop, a rehash is needed
        rehash();
    }

   public:
    CuckooHashing(int size) : Size(size) {
        Table = new Entry[Size];
        for (int i = 0; i < Size; i++) {
            Table[i] = Entry{EMPTY, 0};
        }
    }

    ~CuckooHashing() { delete[] Table; }

    void insert(const std::string &key) { put({key, 1}); }

    int contains(const std::string &key) {
        int index1 = hash1(key);
        int index2 = hash2(key);

        if (Table[index1].value == key)
            return Table[index1].count;
        else if (Table[index2].value == key)
            return Table[index2].count;
        return 0;
    }

    void rehash() {
        Entry *oldTable = Table;

        int oldSize = Size;
        Size = 2 * oldSize;
        Table = new Entry[Size];

        // HASH_VAR1 = (HASH_VAR1 + 1) % 16;
        // HASH_VAR2 = (HASH_VAR2 + 1) % 16;

        Entry entry;
        for (int i = 0; i < oldSize; i++) {
            entry = oldTable[i];
            if (entry.value != EMPTY) put(entry);
        }

        delete[] oldTable;
    }
};

int logic() {
    int n;
    std::cin >> n;

    std::string submissions[3][n];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) std::cin >> submissions[i][j];

    CuckooHashing table(12 * n);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) table.insert(submissions[i][j]);

    int points[3] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            int count = table.contains(submissions[i][j]);
            if (count == 1)
                points[i] += 3;
            else if (count == 2)
                points[i] += 1;
        }
    }

    std::cout << points[0] << " " << points[1] << " " << points[2] << '\n';
    return 0;
}

int logic(std::istream &in) {
    int n;
    in >> n;

    std::string submissions[3][n];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) in >> submissions[i][j];

    CuckooHashing table(12 * n);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) table.insert(submissions[i][j]);

    int points[3] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            int count = table.contains(submissions[i][j]);
            if (count == 1)
                points[i] += 3;
            else if (count == 2)
                points[i] += 1;
        }
    }

    std::cout << points[0] << " " << points[1] << " " << points[2] << '\n';
    return 0;
}