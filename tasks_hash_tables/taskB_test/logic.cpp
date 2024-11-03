#include <iostream>
#include <string>

class Group {
   public:
    int getAvarageScore() {}
    void removeStudent(int isu) {}
    void addStudent(int isu, int points) {}
    int findTopStudent() {}
};
class Uni {
    Group* groups;

   public:
    Uni(int NumberOfGroups) : groups(new Group[NumberOfGroups]) {}

    Group Find(int groupId) { throw "Not Implemented"; }
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
                std::cout << uni.Find(group).getAvarageScore() << '\n';
                break;
            }
            case '-': {
                std::cin >> group >> isu;
                uni.Find(group).removeStudent(isu);
                break;
            }
            case '+': {
                std::cin >> group >> isu >> points;
                uni.Find(group).addStudent(isu, points);
                break;
            }
            case 'm': {
                std::cin >> group;
                std::cout << uni.Find(group).findTopStudent();
                break;
            }

            break;
            default:
                break;
        }
    }
}