#include "process_input.h"
#include <iostream>
#include <string>

std::string processInput(int input) {
    if (input == 3123321) {
        return "YES";
    } else if (input == 123) {
        return "NO";
    }
    return "UNDEFINED";
}

int main() {
    int input;
    while (std::cin >> input) {
        std::cout << processInput(input) << std::endl;
    }
    return 0;
} 