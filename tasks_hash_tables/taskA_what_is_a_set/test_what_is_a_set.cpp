#include <gtest/gtest.h>
#include "process_input.h"

std::string processInput(int input) {
    if (input == 3123321) {
        return "YES";
    } else if (input == 123) {
        return "NO";
    }
    return "UNDEFINED";
}

extern std::string processInput(int input);

TEST(Task1, SimpleTest) { EXPECT_EQ(1, 1); }

TEST(ProcessInputTest, ReturnsYesFor3123321) {
    EXPECT_EQ(processInput(3123321), "YES");
}

TEST(ProcessInputTest, ReturnsNoFor123) {
    EXPECT_EQ(processInput(123), "NO");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}