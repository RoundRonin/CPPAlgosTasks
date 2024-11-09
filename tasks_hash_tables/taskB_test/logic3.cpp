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
    int HASH_TABLE_SIZE;
    T** hashTable;

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
        Student() : IHashable{-1, true}, points(-1) {}
        Student(int value, int points)
            : IHashable{value, false}, points(points) {}
    };

    HashTable<Student> students;
    int totalScore;
    int numberOfStudents;

   public:
    Group(int groupId)
        : IHashable{groupId, false},
          students(100),
          totalScore(0),
          numberOfStudents(0) {}

    int GetAvarageScore() {
        return numberOfStudents == 0 ? 0 : totalScore / numberOfStudents;
    }

    void RemoveStudent(int isu) {
        Student* removedStudent = students.Remove(isu);
        if (removedStudent != nullptr) {
            totalScore -= removedStudent->points;
            numberOfStudents--;
        }
    }

    void AddStudent(int isu, int points) {
        Student* student = students.Search(isu);
        if (student) {
            RemoveStudent(student->value);
        }

        Student* newStudent = new Student(isu, points);
        students.Insert(newStudent);
        totalScore += points;
        numberOfStudents++;
    }

    int FindTopStudent() {
        int maxPoints = 0;
        for (int i = 0; i < students.HASH_TABLE_SIZE; i++) {
            if (students.hashTable[i] && !students.hashTable[i]->isEmpty &&
                students.hashTable[i]->points > maxPoints) {
                maxPoints = students.hashTable[i]->points;
            }
        }
        return maxPoints;
    }
};

class Uni {
    HashTable<Group>* groups;

    Group* addGroup(int groupId) {
        Group* newGroup = new Group(groupId);
        groups->Insert(newGroup);
        return newGroup;
    }

    struct GroupContainer {
        Group* group = nullptr;
        GroupContainer* prevGroup = nullptr;
    };

    GroupContainer* LastAdded = nullptr;

   public:
    Uni(int NumberOfGroups) { groups = new HashTable<Group>(NumberOfGroups); }

    // ~Uni() { delete groups; }

    Group* Find(int groupId) {
        Group* result = groups->Search(groupId);
        if (!result) {
            result = addGroup(groupId);
            if (!LastAdded)
                LastAdded = new GroupContainer{result, nullptr};
            else {
                LastAdded = new GroupContainer{result, LastAdded};
            }
        }
        return result;
    }

    void RemoveStudentFromAllGroups(int isu) {
        GroupContainer* current = LastAdded;
        while (current != nullptr) {
            current->group->RemoveStudent(isu);
            current = current->prevGroup;
        }
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
                uni.RemoveStudentFromAllGroups(isu);
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