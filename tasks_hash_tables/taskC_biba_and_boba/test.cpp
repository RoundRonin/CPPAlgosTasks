#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "logic.cpp"

std::string runCodeWithInput(const std::string& input) {
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());

    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    logic();

    std::cout.rdbuf(oldCoutStreamBuf);

    return oss.str();
}

TEST(CodeOutputTest, SimpleTest) {
    std::string input = "6\n3 5 1 4 6 6\n";
    std::string expectedOutput = "1\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, SingleElement) {
    std::string input = "1\n10\n";
    std::string expectedOutput = "0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, IdenticalHeights) {
    std::string input = "5\n2 2 2 2 2\n";
    std::string expectedOutput = "0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, IncreasingHeights) {
    std::string input = "5\n1 2 3 4 5\n";
    std::string expectedOutput = "10\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, DecreasingHeights) {
    std::string input = "5\n5 4 3 2 1\n";
    std::string expectedOutput = "0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, AlternatingHeights) {
    std::string input = "6\n1 3 1 3 1 3\n";
    std::string expectedOutput = "0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, LargeNumbers) {
    std::string input = "5\n100000 200000 300000 400000 500000\n";
    std::string expectedOutput = "0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, NegativeHeights) {
    std::string input = "5\n-1 -2 -3 -4 -5\n";
    std::string expectedOutput = "0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, MixedHeights) {
    std::string input = "6\n3 5 -1 4 0 6\n";
    std::string expectedOutput = "1\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
