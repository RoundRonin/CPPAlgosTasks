#include <climits>
#include <cmath>
#include <iostream>

class IHashable {
   public:
    int value;
    bool isEmpty = true;
};

template <typename T>
class HashTable {
    static_assert(std::is_base_of<IHashable, T>::value,
                  "T must inherit from IHashable");
    int EMPTY = INT32_MIN;
    int delim = 1;
    int HASH_TABLE_SIZE;
    T** hashTable;

    int hashFunction(int key) {
        // key = (key >> 16) ^ key;
        // key = (key >> 8) ^ key;
        // key = (key >> 6) ^ key;
        // key = (key >> 16) ^ key;
        // key = (key >> 2) ^ key;
        // return key < 0 ? -key : key;
        return key % HASH_TABLE_SIZE;
    }

    int probe(int index, int step, int iter) {
        return (index + step * iter) % HASH_TABLE_SIZE;
    }

    int search(int key) {
        int index = hashFunction(key);

        int iter = 0;
        T* place = hashTable[probe(index, iter, iter)];
        while (place != nullptr && !place->isEmpty) {
            if (place->value == key) return probe(index, iter, iter);
            iter++;

            place = hashTable[probe(index, iter, iter)];
        }
        return -1;
    }

   public:
    HashTable(int size) {
        HASH_TABLE_SIZE = 2 * size + 10;
        hashTable = new T*[HASH_TABLE_SIZE];
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            hashTable[i] = nullptr;
        }
    }

    void Insert(T* entry) {
        int index = hashFunction(entry->value);
        int iter = 0;
        T* place = hashTable[probe(index, iter, iter)];
        while (place != nullptr && !place->isEmpty &&
               iter != HASH_TABLE_SIZE * 4 * delim) {
            if (place->value == entry->value) return;
            iter++;
            place = hashTable[probe(index, iter, iter)];
        }
        hashTable[probe(index, iter, iter)] = entry;
    }

    T* Search(int key) {
        int result = search(key);
        return result == -1 ? nullptr : hashTable[result];
    }

    T* Remove(int key) {
        int index = search(key);
        if (index == -1) return nullptr;

        T* removedEntry = hashTable[index];
        hashTable[index] = new T;  // Ensure new T is correctly initialized
        if (hashTable[index]) {
            hashTable[index]->isEmpty = true;
            hashTable[index]->value = EMPTY;
        }
        return removedEntry;
    }
};

class Group : public IHashable {
    struct Student : public IHashable {
        int points = 0;
        Student* previousTop = nullptr;
        Student* newTop = nullptr;

        Student() : IHashable{-1, true}, points(-1) {}

        Student(int value, int points)
            : IHashable{value, false}, points(points) {}
    };

    HashTable<Student>* students;
    Student* CurrentTop;
    int totalScore;
    int numberOfStudents;

   public:
    Group(int groupId)
        : IHashable{groupId, false}, totalScore(0), numberOfStudents(0) {
        students = new HashTable<Student>(100);
        CurrentTop = nullptr;
    }

    // ~Group() { delete students; }

    int GetAvarageScore() {
        return numberOfStudents == 0 ? 0 : totalScore / numberOfStudents;
    }

    void RemoveStudent(int isu) {
        Student* removedStudent = students->Remove(isu);
        if (removedStudent != nullptr) {
            totalScore -= removedStudent->points;
            numberOfStudents--;

            if (removedStudent->newTop != nullptr) {
                removedStudent->newTop->previousTop =
                    removedStudent->previousTop;
            } else {
                CurrentTop = removedStudent->previousTop;
            }
            if (removedStudent->previousTop != nullptr) {
                removedStudent->previousTop->newTop = removedStudent->newTop;
            }
            // delete removedStudent;
        }
    }

    void AddStudent(int isu, int points) {
        // Should check if the student is already present and remove the student
        // beforehand
        Student* student = students->Search(isu);
        if (student) {
            RemoveStudent(student->value);
        }

        Student* newStudent = new Student(isu, points);
        students->Insert(newStudent);
        totalScore += points;
        numberOfStudents++;

        if (CurrentTop == nullptr)
            CurrentTop = newStudent;
        else if (newStudent->points > CurrentTop->points) {
            newStudent->previousTop = CurrentTop;
            CurrentTop->newTop = newStudent;
            CurrentTop = newStudent;
        } else {
            Student* current = CurrentTop;
            while (current->previousTop != nullptr &&
                   current->points > newStudent->points) {
                current = current->previousTop;
            }
            if (current->previousTop == nullptr) {
                current->previousTop = newStudent;
            } else {
                current->newTop->previousTop = newStudent;
                current->previousTop->newTop = newStudent;
            }
        }
    }

    int FindTopStudent() {
        return CurrentTop != nullptr ? CurrentTop->points : -1;
    }
};

class Uni {
    HashTable<Group>* groups;

    Group* addGroup(int groupId) {
        Group* newGroup = new Group(groupId);
        groups->Insert(newGroup);
        return newGroup;
    }

   public:
    Uni(int NumberOfGroups) { groups = new HashTable<Group>(NumberOfGroups); }

    // ~Uni() { delete groups; }

    Group* Find(int groupId) {
        Group* result = groups->Search(groupId);
        if (!result) result = addGroup(groupId);
        return result;
    }
};

int logic() {
    int M, Q;
    std::cin >> M >> Q;
    Uni uni = Uni(M);

    char message;
    int group = 0;
    int isu = 0;
    int points = 0;

    for (int i = 0; i < Q; i++) {
        std::cin >> message;
        switch (message) {
            case 'a': {
                std::cin >> group;
                std::cout << uni.Find(group)->GetAvarageScore() << '\n';
                break;
            }
            case '-': {
                std::cin >> group >> isu;
                uni.Find(group)->RemoveStudent(isu);
                break;
            }
            case '+': {
                std::cin >> group >> isu >> points;
                uni.Find(group)->AddStudent(isu, points);
                break;
            }
            case 'm': {
                std::cin >> group;
                std::cout << uni.Find(group)->FindTopStudent() << '\n';
                break;
            }
            default:
                break;
        }
    }
    return 0;
}

void logic(std::istream& in) {
    int M, Q;
    in >> M >> Q;
    Uni uni = Uni(M);

    char message;
    int group = 0;
    int isu = 0;
    int points = 0;

    for (int i = 0; i < Q; i++) {
        in >> message;
        switch (message) {
            case 'a': {
                in >> group;
                std::cout << uni.Find(group)->GetAvarageScore() << '\n';
                break;
            }
            case '-': {
                in >> group >> isu;
                uni.Find(group)->RemoveStudent(isu);
                break;
            }
            case '+': {
                in >> group >> isu >> points;
                uni.Find(group)->AddStudent(isu, points);
                break;
            }
            case 'm': {
                in >> group;
                std::cout << uni.Find(group)->FindTopStudent() << '\n';
                break;
            }
            default:
                break;
        }
    }
}