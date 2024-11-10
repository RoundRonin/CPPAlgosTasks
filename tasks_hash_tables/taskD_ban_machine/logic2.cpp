#include <iostream>
#include <string>

using namespace std;

class CuckooHashTable {
    struct Entry {
        string key;
        int count;
        bool occupied;

        Entry() : key(""), count(0), occupied(false) {}
        Entry(const string &key, int count, bool occupied)
            : key(key), count(count), occupied(occupied) {}
    };

    Entry *table1;
    Entry *table2;
    int size;

    int hash1(const string &key) {
        unsigned int hash = 5381;
        for (char ch : key) hash = ((hash << 5) + hash) + ch;
        return hash % size;
    }

    int hash2(const string &key) {
        unsigned int hash = 0;
        for (char ch : key) hash = ch + (hash << 6) + (hash << 16) - hash;
        return hash % size;
    }

    void placeInTable(Entry &entry, int tableNumber, int count = 0) {
        if (count >= size) {
            rehash();
            placeInTable(entry, 1);
            return;
        }

        if (tableNumber == 1) {
            int index = hash1(entry.key);
            if (!table1[index].occupied) {
                table1[index] = entry;
                table1[index].occupied = true;
            } else {
                Entry temp = table1[index];
                table1[index] = entry;
                placeInTable(temp, 2, count + 1);
            }
        } else {
            int index = hash2(entry.key);
            if (!table2[index].occupied) {
                table2[index] = entry;
                table2[index].occupied = true;
            } else {
                Entry temp = table2[index];
                table2[index] = entry;
                placeInTable(temp, 1, count + 1);
            }
        }
    }

    void rehash() {
        Entry *oldTable1 = table1;
        Entry *oldTable2 = table2;
        size *= 2;
        table1 = new Entry[size];
        table2 = new Entry[size];
        for (int i = 0; i < size / 2; ++i) {
            if (oldTable1[i].occupied) placeInTable(oldTable1[i], 1);
            if (oldTable2[i].occupied) placeInTable(oldTable2[i], 1);
        }
        delete[] oldTable1;
        delete[] oldTable2;
    }

   public:
    CuckooHashTable(int size) : size(size) {
        table1 = new Entry[size];
        table2 = new Entry[size];
    }

    ~CuckooHashTable() {
        delete[] table1;
        delete[] table2;
    }

    void insert(const string &key) {
        Entry entry{key, 1, true};
        placeInTable(entry, 1);
    }

    int count(const string &key) {
        int index1 = hash1(key);
        if (table1[index1].occupied && table1[index1].key == key)
            return table1[index1].count;
        int index2 = hash2(key);
        if (table2[index2].occupied && table2[index2].key == key)
            return table2[index2].count;
        return 0;
    }

    void increment(const string &key) {
        int index1 = hash1(key);
        if (table1[index1].occupied && table1[index1].key == key) {
            table1[index1].count++;
            return;
        }
        int index2 = hash2(key);
        if (table2[index2].occupied && table2[index2].key == key) {
            table2[index2].count++;
            return;
        }
        Entry newEntry(key, 1, true);
        placeInTable(newEntry, 1);
    }
};

int logic() {
    int n;
    cin >> n;

    string submissions[3][n];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) cin >> submissions[i][j];

    CuckooHashTable table(12 * n);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) table.increment(submissions[i][j]);

    int points[3] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            int count = table.count(submissions[i][j]);
            if (count == 1)
                points[i] += 3;
            else if (count == 2)
                points[i] += 1;
        }
    }

    cout << points[0] << " " << points[1] << " " << points[2] << '\n';
    return 0;
}

int logic(std::istream &in) {
    int n;
    in >> n;

    string submissions[3][n];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) in >> submissions[i][j];

    CuckooHashTable table(12 * n);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j) table.increment(submissions[i][j]);

    int points[3] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            int count = table.count(submissions[i][j]);
            if (count == 1)
                points[i] += 3;
            else if (count == 2)
                points[i] += 1;
        }
    }

    cout << points[0] << " " << points[1] << " " << points[2] << '\n';
    return 0;
}