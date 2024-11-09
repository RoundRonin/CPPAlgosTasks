#include <iostream>

struct Student {
    int ISU;
    int points;
};

class Group {
   public:
    static const int TABLE_SIZE = 10000;
    Student* students[TABLE_SIZE] = {nullptr};
    int totalPoints = 0;
    int numStudents = 0;

    int hash(int key) { return key % TABLE_SIZE; }

    void addStudent(int ISU, int points) {
        int idx = hash(ISU);
        int i = 0;
        while (students[(idx + i * i) % TABLE_SIZE] &&
               students[(idx + i * i) % TABLE_SIZE]->ISU != ISU) {
            i++;
        }
        int pos = (idx + i * i) % TABLE_SIZE;
        if (!students[pos]) {
            students[pos] = new Student{ISU, points};
            totalPoints += points;
            numStudents++;
        } else {
            totalPoints += (points - students[pos]->points);
            students[pos]->points = points;
        }
    }

    void removeStudent(int ISU) {
        int idx = hash(ISU);
        int i = 0;
        while (students[(idx + i * i) % TABLE_SIZE] &&
               students[(idx + i * i) % TABLE_SIZE]->ISU != ISU) {
            i++;
        }
        int pos = (idx + i * i) % TABLE_SIZE;
        if (students[pos]) {
            totalPoints -= students[pos]->points;
            delete students[pos];
            students[pos] = nullptr;
            numStudents--;
        }
    }

    int getAverageScore() {
        return numStudents == 0
                   ? 0
                   : static_cast<double>(totalPoints) / numStudents;
    }

    int getMaxScore() {
        int maxScore = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (students[i] && students[i]->points > maxScore) {
                maxScore = students[i]->points;
            }
        }
        return maxScore;
    }
};

class University {
   public:
    static const int TABLE_SIZE = 10000;
    Group* groups[TABLE_SIZE] = {nullptr};

    int hash(int key) { return key % TABLE_SIZE; }

    Group* getGroup(int groupNumber) {
        int idx = hash(groupNumber);
        if (!groups[idx]) {
            groups[idx] = new Group();
        }
        return groups[idx];
    }
};

int logic() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);

    int M, Q;
    std::cin >> M >> Q;
    University uni;

    for (int i = 0; i < Q; ++i) {
        char query;
        int group, ISU, points;
        std::cin >> query;

        switch (query) {
            case 'a':
                std::cin >> group;
                if (group < 0) group = 0;
                std::cout << uni.getGroup(group)->getAverageScore() << "\n";
                break;
            case '-':
                std::cin >> group >> ISU;
                if (group < 0) group = 0;
                if (ISU < 0) ISU = 0;
                uni.getGroup(group)->removeStudent(ISU);
                break;
            case '+':
                std::cin >> group >> ISU >> points;
                if (group < 0) group = 0;
                if (points < 0) points = 0;
                if (ISU < 0) ISU = 0;
                uni.getGroup(group)->addStudent(ISU, points);
                break;
            case 'm':
                std::cin >> group;
                if (group < 0) group = 0;
                std::cout << uni.getGroup(group)->getMaxScore() << "\n";
                break;
        }
    }
    return 0;
}
