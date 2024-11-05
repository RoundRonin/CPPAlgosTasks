#include <sstream>

#include "logic.cpp"

int main() {
    std::string input =
        // "5 8\n+ 1 10 100\n+ 1 2 3\nm 1\na 1\n+ 2 10 5\na 2\nm 2\n- 2 10\n";
        // "5 5\n+ 1000 10 100\n+ 1000 20 50\n- 1000 10\na 1000\nm 1000";
        "5 10\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\na 1\n+ 1 10 "
        "100\n+ 1 11 150\n+ 1 21 "
        "200\n+ 1 20 50\na 1";
    std::istringstream in(input);
    logic(in);
    // logic();
    return 0;
}
