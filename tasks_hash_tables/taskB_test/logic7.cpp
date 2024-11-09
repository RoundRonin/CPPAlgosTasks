#include <cmath>
#include <iostream>

inline bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

inline int nextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

template <typename T>
class HashTable {
   protected:
    struct Entry {
        int key;
        T* item;
        Entry* next;

        Entry(int key, T* item) : key(key), item(item), next(nullptr) {}
    };

    int TABLE_SIZE;
    Entry** hashTable;

    int hash(int key) { return key % TABLE_SIZE; }

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
    HashTable(int size) {
        TABLE_SIZE = nextPrime(size / 10000);
        hashTable = new Entry*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            hashTable[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Entry* current = hashTable[i];
            while (current != nullptr) {
                Entry* next = current->next;
                delete current->item;
                delete current;
                current = next;
            }
        }
        delete[] hashTable;
    }
};

struct Student {
    int points = 0;
};

class Group {
    int numberOfStudents;
    int totalScore;
    struct Student {
        int isu = 0;
        int points = 0;
        Student* next = nullptr;
    };

    Student* topStudent = nullptr;
    Student* head;
    Student* tail;

    Student* search(int isu) {
        if (!head) return nullptr;
        Student* current = head;
        while (current) {
            if (current->isu == isu) return current;
            current = current->next;
        }
        return nullptr;
    }

    void setTopStudent(Student* student) {
        if (student) {
            totalScore += student->points;
            numberOfStudents++;
            if (!topStudent || student->points > topStudent->points) {
                topStudent = student;
            }
        }
    }

   public:
    Group() : numberOfStudents(0), totalScore(0) { head = tail = nullptr; }

    int GetAverageScore() {
        return numberOfStudents == 0 ? 0 : totalScore / numberOfStudents;
    }

    void RemoveStudent(int isu) {
        if (!head) return;

        Student* current = head;
        Student* prev = head;
        bool found = false;
        while (current) {
            if (current->isu == isu) {
                found = true;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found) return;
        if (current == tail) {
            tail = prev;
        }

        Student* toDelete = current;

        if (prev == current) {
            head = toDelete->next;
        } else {
            prev->next = toDelete->next;
        }

        // TODO check
        totalScore -= toDelete->points;
        numberOfStudents--;
        if (toDelete == topStudent) {
            topStudent = nullptr;
            current = head;
            while (current) {
                if (!topStudent || current->points > topStudent->points) {
                    topStudent = current;
                }
                current = current->next;
            }
        }

        delete toDelete;
        return;
    }

    void AddStudent(int isu, int points) {
        Student* newStudent = new Student{isu, points, nullptr};

        if (!head) {
            head = tail = newStudent;
            setTopStudent(newStudent);
            return;
        }

        Student* present = search(isu);
        if (present) return;

        tail->next = newStudent;
        tail = newStudent;

        setTopStudent(newStudent);

        return;
    }

    int FindTopStudent() { return topStudent ? topStudent->points : 0; }
};

class University : HashTable<Group> {
    int GROUP_SIZE;
    int k;

   public:
    University(int size, int GROUP_SIZE, int k)
        : HashTable(size), GROUP_SIZE(GROUP_SIZE), k(k) {}

    Group* Find(int groupNumber) {
        Entry* result = search(groupNumber);
        if (!result) {
            // Entry* newEntry = new Entry(groupNumber, new Group(GROUP_SIZE));
            Entry* newEntry = new Entry(groupNumber, new Group());
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
                std::cout << uni.Find(group)->GetAverageScore() << '\n';
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
                std::cout << uni.Find(group)->GetAverageScore() << '\n';
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