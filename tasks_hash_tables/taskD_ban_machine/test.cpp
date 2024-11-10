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

// Basic Functionality Tests
TEST(BasicFunctionalitySuite, BasicFunctionalityTest1) {
    std::string input = "3\nfir sec thi\nthi fir sec\naaa sec bbb\n";
    std::string expectedOutput = "2 2 6\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(BasicFunctionalitySuite, BasicFunctionalityTest2) {
    std::string input = "2\none two\nthree four\nsix seven";
    std::string expectedOutput = "6 6 6\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(BasicFunctionalitySuite, BasicFunctionalityTest3) {
    std::string input =
        "3\napple banana orange\nbanana orange apple\ncarrot banana date\n";
    std::string expectedOutput = "2 2 6\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(BasicFunctionalitySuite, BasicFunctionalityTest4) {
    std::string input = "3\ndog cat lock\ncat dog lock\nlock lock lock";
    std::string expectedOutput = "2 2 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// Edge Cases Tests
TEST(EdgeCasesSuite, EdgeCaseTest1) {
    std::string input = "3\nshort medium long\nlong short medium\n\na b c\n";
    std::string expectedOutput = "3 3 9\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(EdgeCasesSuite, EdgeCaseTest2) {
    std::string input = "3\na b c\nd e f\ng h i\n";
    std::string expectedOutput = "9 9 9\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(EdgeCasesSuite, EdgeCaseTest3) {
    std::string input = "2\na\nb\n";
    std::string expectedOutput = "6 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(EdgeCasesSuite, EdgeCaseTest4) {
    std::string input =
        "2\npneumonoultramicroscopicsilicovolcanoconiosis\nhippopotomonstrosesq"
        "uipedaliophobia\n";
    std::string expectedOutput = "6 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// Special Characters Tests
TEST(SpecialCharactersSuite, SpecialCharactersTest1) {
    std::string input = "3\n!@# $%^ &*(\n)*& ^%$ #@!\n$%^ &*( !@#\n";
    std::string expectedOutput = "3 9 3\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(SpecialCharactersSuite, SpecialCharactersTest2) {
    std::string input = "2\nhello world\nworld hello\n";
    std::string expectedOutput = "2 2 2\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(SpecialCharactersSuite, SpecialCharactersTest3) {
    std::string input = "2\n\n\n###\n";
    std::string expectedOutput = "3 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(SpecialCharactersSuite, SpecialCharactersTest4) {
    std::string input = "2\n@home #coding\n#coding @home\n";
    std::string expectedOutput = "2 2 2\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// Empty Input Tests
TEST(EmptyInputSuite, EmptyInputTest1) {
    std::string input = "0\n";
    std::string expectedOutput = "0 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(EmptyInputSuite, EmptyInputTest2) {
    std::string input = "2\n\n\n\n\n";
    std::string expectedOutput = "0 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(EmptyInputSuite, EmptyInputTest3) {
    std::string input = "1\n\n\n";
    std::string expectedOutput = "0 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(EmptyInputSuite, EmptyInputTest4) {
    std::string input = "2\n\n\n\n\n\n\n\n\n";
    std::string expectedOutput = "0 0 0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
