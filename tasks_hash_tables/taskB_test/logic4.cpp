#include <climits>
#include <cmath>
#include <iostream>

template <typename T>
class HashTable {
   protected:
    // ********************************************
    // This is a hash table that uses a linked list
    // ********************************************

    struct Entry {
        int key = 0;
        Entry* next = nullptr;
        T* item;

        Entry(int key, T* item) : key(key), item(item) {};
    };

    int TABLE_SIZE;
    Entry** hashTable;

    int hash(int key) {
        key = (key >> 16) ^ key;
        key = (key >> 8) ^ key;
        key = (key >> 6) ^ key;
        key = (key >> 16) ^ key;
        key = (key >> 2) ^ key;
        return (key < 0 ? -key : key) % TABLE_SIZE;
    }

    // int hash(int key) { return key % TABLE_SIZE; }

    Entry* insert(Entry* entry) {
        int idx = hash(entry->key);
        Entry* current = hashTable[idx];

        if (current == nullptr) {
            hashTable[idx] = entry;
        } else {
            Entry* prev = nullptr;
            while (current != nullptr) {
                if (current->key == entry->key) return nullptr;
                prev = current;
                current = current->next;
            }
            prev->next = entry;
        }
        return entry;
    }

    Entry* search(int key) {
        int idx = hash(key);
        Entry* current = hashTable[idx];

        while (current != nullptr) {
            if (current->key == key) return current;
            current = current->next;
        }
        return nullptr;
    }

    Entry* remove(int key) {
        int idx = hash(key);
        Entry* current = hashTable[idx];
        Entry* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    hashTable[idx] = current->next;
                } else {
                    prev->next = current->next;
                }
                return current;
            }
            prev = current;
            current = current->next;
        }
        return nullptr;
    }

   public:
    HashTable(int size, int k) : TABLE_SIZE(size / k + k + 10) {
        hashTable = new Entry*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            hashTable[i] = nullptr;
        }
    }
};

struct Student {
    int points = 0;
};

class Group : HashTable<Student> {
    int numberOfStudents = 0;
    int totalScore = 0;

   public:
    Group(int size, int k) : HashTable(100000, k) {}

    int GetAvarageScore() {
        return numberOfStudents == 0 ? 0 : totalScore / numberOfStudents;
    }

    void RemoveStudent(int isu) {
        Entry* removedStudent = remove(isu);
        if (removedStudent) {
            totalScore -= removedStudent->item->points;
            numberOfStudents--;
        }
    }

    void AddStudent(int isu, int points) {
        RemoveStudent(isu);

        Entry* newEntry = new Entry(isu, new Student{points});
        Entry* insertedEntry = insert(newEntry);
        if (insertedEntry) {
            totalScore += insertedEntry->item->points;
            numberOfStudents++;
        }
    }

    int FindTopStudent() {
        int maxPoints = 0;
        int currentPoints = 0;

        for (int i = 0; i < TABLE_SIZE; i++) {
            Entry* current = hashTable[i];
            while (current) {
                currentPoints = current->item->points;
                if (currentPoints > maxPoints) {
                    maxPoints = currentPoints;
                }

                current = current->next;
            }
        }
        return maxPoints;
    }
};

class University : HashTable<Group> {
    int GROUP_SIZE;

   public:
    University(int size, int GROUP_SIZE, int k)
        : HashTable(size, k), GROUP_SIZE(GROUP_SIZE) {}

    Group* Find(int groupNumber) {
        Entry* result = search(groupNumber);
        if (!result) {
            Entry* newEntry =
                new Entry(groupNumber, new Group(GROUP_SIZE, 200));
            result = insert(newEntry);
        }
        return result->item;
    }
};

int logic() {
    int M, Q;
    std::cin >> M >> Q;
    University uni = University(M, Q, 1000);

    char message;
    int group = 0;
    int isu = 0;
    int points = 0;

    for (int i = 0; i < Q; i++) {
        std::cin >> message;
        switch (message) {
            case 'a': {
                std::cin >> group;
                if (group < 0) group = 0;
                std::cout << uni.Find(group)->GetAvarageScore() << '\n';
                break;
            }
            case '-': {
                std::cin >> group >> isu;
                if (group < 0) group = 0;
                if (isu < 0) isu = 0;
                uni.Find(group)->RemoveStudent(isu);
                break;
            }
            case '+': {
                std::cin >> group >> isu >> points;
                if (group < 0) group = 0;
                if (isu < 0) isu = 0;
                if (points < 0) points = 0;
                uni.Find(group)->AddStudent(isu, points);
                break;
            }
            case 'm': {
                std::cin >> group;
                if (group < 0) group = 0;
                std::cout << uni.Find(group)->FindTopStudent() << '\n';
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
int logic(std::istream& in) {
    int M, Q;
    in >> M >> Q;
    University uni = University(M, Q, 10);

    char message;
    int group = 0;
    int isu = 0;
    int points = 0;

    for (int i = 0; i < Q; i++) {
        in >> message;
        switch (message) {
            case 'a': {
                in >> group;
                if (group < 0) group = 0;
                std::cout << uni.Find(group)->GetAvarageScore() << '\n';
                break;
            }
            case '-': {
                in >> group >> isu;
                if (group < 0) group = 0;
                if (isu < 0) isu = 0;
                uni.Find(group)->RemoveStudent(isu);
                break;
            }
            case '+': {
                in >> group >> isu >> points;
                if (group < 0) group = 0;
                if (isu < 0) isu = 0;
                if (points < 0) points = 0;
                uni.Find(group)->AddStudent(isu, points);
                break;
            }
            case 'm': {
                in >> group;
                if (group < 0) group = 0;
                std::cout << uni.Find(group)->FindTopStudent() << '\n';
                break;
            }
            default:
                break;
        }
    }
    return 0;
}