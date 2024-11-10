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
   public:
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

class MaxHeap {
    Student** heap;
    int capacity;
    int size;
    HashTable<int>* positions;  // Hash table to store heap positions

    void heapifyUp(int index) {
        while (index > 0 &&
               heap[(index - 1) / 2]->points < heap[index]->points) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            positions->insert(new typename HashTable<int>::Entry(
                heap[index]->points, new int(index)));
            positions->insert(new typename HashTable<int>::Entry(
                heap[(index - 1) / 2]->points, new int((index - 1) / 2)));
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        while ((2 * index + 1) < size) {
            int maxIndex = 2 * index + 1;
            if ((maxIndex + 1) < size &&
                heap[maxIndex + 1]->points > heap[maxIndex]->points) {
                maxIndex++;
            }
            if (heap[index]->points > heap[maxIndex]->points) {
                break;
            }
            std::swap(heap[index], heap[maxIndex]);
            positions->insert(new typename HashTable<int>::Entry(
                heap[index]->points, new int(index)));
            positions->insert(new typename HashTable<int>::Entry(
                heap[maxIndex]->points, new int(maxIndex)));
            index = maxIndex;
        }
    }

   public:
    MaxHeap(int capacity) : capacity(capacity), size(0) {
        heap = new Student*[capacity];
        positions = new HashTable<int>(capacity);
    }

    ~MaxHeap() {
        delete[] heap;
        delete positions;
    }

    void insert(Student* student) {
        if (size == capacity) {
            throw std::overflow_error("MaxHeap is full");
        }
        heap[size] = student;
        positions->insert(
            new typename HashTable<int>::Entry(student->points, new int(size)));
        heapifyUp(size);
        size++;
    }

    void remove(Student* student) {
        typename HashTable<int>::Entry* posEntry =
            positions->search(student->points);
        if (!posEntry) {
            return;
        }
        int pos = *(posEntry->item);
        positions->remove(student->points);
        std::swap(heap[pos], heap[size - 1]);
        size--;
        if (pos < size) {
            positions->insert(new typename HashTable<int>::Entry(
                heap[pos]->points, new int(pos)));
            positions->remove(heap[size]->points);
            heapifyDown(pos);
        } else {
            positions->remove(heap[size]->points);
        }
    }

    Student* getTopStudent() { return size > 0 ? heap[0] : nullptr; }

    void clear() { size = 0; }
};

class Group : public HashTable<Student> {
    int numberOfStudents;
    int totalScore;
    MaxHeap maxHeap;

   public:
    Group(int size)
        : HashTable(size), numberOfStudents(0), totalScore(0), maxHeap(size) {}

    int GetAverageScore() {
        return numberOfStudents == 0 ? 0 : totalScore / numberOfStudents;
    }

    void RemoveStudent(int isu) {
        Entry* removedStudent = remove(isu);
        if (removedStudent) {
            totalScore -= removedStudent->item->points;
            numberOfStudents--;

            maxHeap.remove(removedStudent->item);
            delete removedStudent->item;
            delete removedStudent;
        }
    }

    void AddStudent(int isu, int points) {
        RemoveStudent(isu);

        Student* newStudent = new Student{points};
        Entry* newEntry = new Entry(isu, newStudent);
        Entry* insertedEntry = insert(newEntry);
        if (insertedEntry) {
            totalScore += insertedEntry->item->points;
            numberOfStudents++;

            maxHeap.insert(insertedEntry->item);
        }
    }

    int FindTopStudent() {
        Student* topStudent = maxHeap.getTopStudent();
        return topStudent ? topStudent->points : 0;
    }
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
            Entry* newEntry = new Entry(groupNumber, new Group(GROUP_SIZE));
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