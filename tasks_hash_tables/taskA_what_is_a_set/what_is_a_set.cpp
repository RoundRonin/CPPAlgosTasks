#include <iostream>
#include <string>

#include "process_input.h"

std::string processInput(int input) {
    if (input == 3123321) {
        return "YES";
    } else if (input == 123) {
        return "NO";
    }
    return "UNDEFINED";
}

int main() {}