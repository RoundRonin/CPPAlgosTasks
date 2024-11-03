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

TEST(CodeOutputTest, SimpleTest) {
    std::string input = "3 1 2 3 3 2 1\n";
    std::string expectedOutput = "YES\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, AnotherTest) {
    std::string input = "1 2 3\n";
    std::string expectedOutput = "NO\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
