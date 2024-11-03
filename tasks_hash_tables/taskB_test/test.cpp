#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "logic.cpp"

// Function to simulate the execution of code.cpp
std::string runCodeWithInput(const std::string& input) {
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());

    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    // Ensure the correct namespace is used
    logic();

    std::cout.rdbuf(oldCoutStreamBuf);

    return oss.str();
}

TEST(CodeOutputTest, baseTest) {
    std::string input =
        "5 8\n+ 1 10 100\n+ 1 2 3\nm 1\na 1\n+ 2 10 5\na 2\nm 2\n- 2 10\n";
    std::string expectedOutput = "100\n51\n5\n5\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
