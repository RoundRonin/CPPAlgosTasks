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

// Example tests
TEST(CodeOutputTest, SimpleTest) {
    std::string input = "6\n3 5 1 4 6 6\n";
    std::string expectedOutput = "1\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, AnotherTest) {
    std::string input = "6\n1 3 5 7 9 11\n";
    std::string expectedOutput = "/* expected result */\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
