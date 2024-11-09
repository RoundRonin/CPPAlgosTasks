#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "logic7.cpp"

// TODO
/*
We don't know how to act:
1. When the same student is added to another group. We no
it can be done, but not whether the student should be deleted
from the previous group, or not

We can change two things:
1. Remove hashing from the groups and start going through them
to find if this student was previously added to remove him
2. Stop creating a doubly linked list and just search through
the list of students to find the best
*/

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

TEST(CodeOutputTest, Test2NoN) {
    std::string input =
        "5 5\n+ 1000 10 100\n+ 1000 20 50\n- 1000 10\na 1000\nm 1000";
    std::string expectedOutput = "50\n50\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, Test2N) {
    std::string input =
        "5 5\n+ 1000 10 100\n+ 1000 20 50\n- 1000 10\na 1000\nm 1000\n";
    std::string expectedOutput = "50\n50\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, BasicAdditionandRemoval) {
    std::string input =
        "5 6\n+ 1 10 100\n+ 1 20 200\n- 1 20\na 1\n+ 1 30 50\na 1";
    std::string expectedOutput = "100\n75\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, MultipleGroupsZeroState) {
    std::string input = "5 6\n+ 1 10 100\na 2\nm 2\n+ 3 30 300\nm 1\nm 3";
    std::string expectedOutput = "0\n0\n100\n300\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, RemovingNonExistentStudent) {
    std::string input = "5 5\n+ 1 10 100\n+ 1 20 200\n- 1 30\na 1\nm 1";
    std::string expectedOutput = "150\n200\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingIsuNumbers) {
    std::string input = "5 6\n+ 1 10 100\n+ 2 10 50\na 1\na 2\nm 1\nm 2";
    std::string expectedOutput = "100\n50\n100\n50\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingISUNumbers_MultipleOverlaps) {
    std::string input =
        "5 8\n+ 1 10 100\n+ 1 20 200\n+ 2 10 50\n+ 2 30 300\n+ 3 10 10\na 1\na "
        "2\na 3";
    std::string expectedOutput = "150\n175\n10\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// TODO Maybe we shouldn't allow same ISU in different groups:
// 1. Either delete the previous and add a new one
// 2. Or don't create a new one
// 3. Or do as before and create a new one

TEST(CodeOutputTest, OverlappingISUNumbers_SameISU_DifferentGroups) {
    std::string input =
        "5 7\n+ 1 10 100\n+ 2 10 50\n+ 3 10 75\n+ 1 20 200\na 1\na 2\na 3";
    std::string expectedOutput = "150\n50\n75\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// TODO check what happens when you add the same ISU to the same group
// Currently it should overwrite the previous one
TEST(CodeOutputTest, OverlappingISUNumbers_DifferentPoints_SameISU) {
    std::string input =
        "5 6\n+ 1 10 100\n+ 1 10 150\n+ 1 10 200\n+ 2 10 50\na 1\na 2";
    std::string expectedOutput = "200\n50\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// It is really hard to check for hash collision in such a manner. We have
// to account in the size of the table and the hash function, of cousre
TEST(CodeOutputTest, OverlappingISUNumbers_HashCollision) {
    std::string input =
        "5 8\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\na 1\n- 1 10\na "
        "1\nm 1";
    std::string expectedOutput = "125\n133\n200\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// adding the same thing twice
TEST(CodeOutputTest, OverlappingISUNumbers_SameThingTwice) {
    std::string input = "5 3\n+ 1 10 100\n+ 1 10 100\na 1";
    std::string expectedOutput = "100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// TEST(CodeOutputTest, OverlappingISUNumbers_SameThingTwice) {
//     std::string input = "5 3\n+ 1 10 100\n+ 1 10 100\na 1";
//     std::string expectedOutput = "100\n";
//     EXPECT_EQ(runCodeWithInput(input), expectedOutput);
// }

TEST(CodeOutputTest, OverlappingISUNumbers_HighLoadFactor) {
    std::string input =
        "5 9\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\n+ 2 12 100\n"
        "+ 2 32 200\n+ 2 42 50\na 1\na 2";
    std::string expectedOutput = "125\n116\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingISUNumbers_TwoTimes0) {
    std::string input = "5 3\n+ 1 10 100\n+ 1 10 100\na 1";
    std::string expectedOutput = "100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingISUNumbers_TwoTimes1) {
    std::string input =
        "5 6\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\na 1\n+ 1 10 "
        "100";
    std::string expectedOutput = "125\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// TODO maybe the behaviour should be different
TEST(CodeOutputTest, OverlappingISUNumbers_TwoTimes1_N_MoreThanShouldBe) {
    std::string input =
        "5 11\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\na 1\n+ 1 10 "
        "100";
    std::string expectedOutput = "125\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

// Fine
TEST(CodeOutputTest, OverlappingISUNumbers_TwoTimes1_N_LessThanShouldBe) {
    std::string input =
        "5 4\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\na 1\n+ 1 20 50\n+ 1 10 "
        "100";
    std::string expectedOutput = "150\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingISUNumbers_TwoTimes2) {
    std::string input =
        "5 10\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\na 1\n+ 1 10 "
        "100\n+ 1 11 150\n+ 1 21 "
        "200\n+ 1 20 50\na 1";
    std::string expectedOutput = "125\n125\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingISUNumbers_TwoTimes3) {
    std::string input =
        "10 18\n+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\n+ 2 12 100\n"
        "+ 2 32 200\n+ 2 42 50\na 1\na 2\n+ 1 10 100\n+ 1 11 150\n+ 1 21 "
        "200\n+ 1 20 50\n+ 2 12 100\n"
        "+ 2 32 200\n+ 2 42 50\na 1\na 2";
    std::string expectedOutput = "125\n116\n125\n116\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, OverlappingISUNumbers_HighLoadFactorExtra) {
    std::string input =
        "+ 1 10 100\n+ 1 11 150\n+ 1 21 200\n+ 1 20 50\n+ 2 12 100\n"
        "+ 2 32 200\n+ 2 42 50\na 1\na 2\n";
    std::string expectedOutput = "125\n116\n";

    int times = 200;
    std::string inmul;
    inmul.reserve(input.size() * times);
    std::string outmul;
    outmul.reserve(expectedOutput.size() * times);

    std::string prefix =
        std::to_string(5 * 10 * times) + " " + std::to_string(9 * times) + '\n';
    inmul += prefix;

    for (int i = 0; i < times; ++i) {
        inmul += input;
        outmul += expectedOutput;
    }

    // std::cout << "inmul:\n" << inmul << "\n";
    // std::cout << "outmul:\n" << outmul << "\n";
    EXPECT_EQ(runCodeWithInput(inmul), outmul);
}

TEST(CodeOutputTest, RemovalFollowedByReAddition) {
    std::string input =
        "5 6\n+ 1 10 150\n- 1 10\n+ 1 10 100\na 1\n+ 1 20 50\na 1";
    std::string expectedOutput = "100\n75\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, SameISUDifferentPoints_RemoveAndAdd) {
    std::string input =
        "5 7\n+ 1 10 100\n+ 1 10 150\n- 1 10\n+ 1 10 200\n+ 2 10 50\na 1\na 2";
    std::string expectedOutput = "200\n50\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, AdditionAndImmediateRemoval) {
    std::string input =
        "5 8\n+ 1 10 100\n+ 1 20 150\n- 1 10\na 1\n+ 1 30 50\n- 1 20\na 1\nm 1";
    std::string expectedOutput = "150\n50\n50\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, RepeatedAdditionsAndRemovals) {
    std::string input =
        "5 10\n+ 1 10 100\n+ 1 20 150\n+ 1 30 200\n- 1 10\n+ 1 10 250\n- 1 "
        "20\na 1\nm 1\n- 1 10\na 1";
    std::string expectedOutput = "225\n250\n200\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCaseWithZeroStudents) {
    std::string input = "5 5\n+ 1 10 100\n- 1 10\nm 1\na 1\na 2";
    std::string expectedOutput = "0\n0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, MaxCapacityTest) {
    std::string input =
        "5 7\n+ 1 10 100\n+ 1 20 200\n+ 1 30 300\n+ 1 40 400\n- 1 30\na 1\nm 1";
    std::string expectedOutput = "233\n400\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, HighNumberOfGroups) {
    std::string input =
        "10000 5\n+ 9999 10 100\nm 9999\n+ 1 20 200\nm 1\na 9999";
    std::string expectedOutput = "100\n200\n100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, GroupIdLargerThanNumber) {
    std::string input = "10 5\n+ 9999 10 100\nm 9999\n+ 1 20 200\nm 1\na 9999";
    std::string expectedOutput = "100\n200\n100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, BigISUNumber) {
    std::string input = "10 5\n+ 1 100000 100\nm 1\n+ 2 100001 200\nm 2\na 1";
    std::string expectedOutput = "100\n200\n100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, RepeatedAddRemoveSameISU) {
    std::string input =
        "5 6\n+ 1 10 100\n- 1 10\n+ 1 10 150\n- 1 10\n+ 1 10 200\na 1";
    std::string expectedOutput = "200\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, MixedOperationsDifferentGroups) {
    std::string input =
        "5 9\n+ 1 10 100\n+ 2 20 200\n+ 1 30 300\nm 1\nm 2\n- 1 10\na 1\n+ 2 "
        "30 150\na 2";
    std::string expectedOutput = "300\n200\n300\n175\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, BoundaryGroupNumbers) {
    std::string input =
        "5 6\n+ 0 10 100\n+ 4 20 200\n+ 9999 30 300\na 0\na 4\na 9999";
    std::string expectedOutput = "100\n200\n300\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, ZeroPointsScenarios) {
    std::string input = "5 5\n+ 1 10 0\n+ 1 20 0\na 1\nm 1\na 2";
    std::string expectedOutput = "0\n0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, LargeISUNumbers) {
    std::string input =
        "5 4\n+ 1 100000 100\n+ 2 200000 200\n+ 3 300000 300\na 1";
    std::string expectedOutput = "100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_DuplicateGroups) {
    std::string input = "5 5\n+ 1 10 100\n+ 1 10 150\n- 1 10\na 1\nm 1";
    std::string expectedOutput = "0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_AllGroupsNoStudents) {
    std::string input = "5 4\na 1\na 2\na 3\na 4";
    std::string expectedOutput = "0\n0\n0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_SameISURepeatedlyAddedAndRemoved) {
    std::string input =
        "5 8\n+ 1 10 100\n- 1 10\n+ 1 10 150\n- 1 10\n+ 1 10 200\n- 1 10\na "
        "1\nm 1";
    std::string expectedOutput = "0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_AddAndRemoveHighISU) {
    std::string input = "5 4\n+ 1 1000000 100\n- 1 1000000\nm 1\na 1";
    std::string expectedOutput = "0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_MaxISU) {
    std::string input = "5 4\n+ 1 2147483647 100\nm 1\na 1\n- 1 2147483647";
    std::string expectedOutput = "100\n100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_LargeNumberGroups) {
    std::string input =
        "1000 5\n+ 100 10 100\n+ 500 20 200\n- 100 10\na 100\nm 500";
    std::string expectedOutput = "0\n200\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_ZeroPointsMultipleGroups) {
    std::string input =
        "5 8\n+ 1 10 0\n+ 2 20 0\n+ 3 30 0\n+ 4 40 0\na 1\na 2\na 3\na 4";
    std::string expectedOutput = "0\n0\n0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_MultipleStudentsSameISU) {
    std::string input =
        "5 6\n+ 1 10 100\n+ 2 10 150\n+ 3 10 200\n+ 4 10 250\na 1\na 2";
    std::string expectedOutput = "100\n150\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_EmptyGroupsAfterOperations) {
    std::string input = "5 6\n+ 1 10 100\n+ 1 20 150\n- 1 10\n- 1 20\na 1\na 2";
    std::string expectedOutput = "0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_MultipleAddsAndRemoves) {
    std::string input =
        "5 9\n+ 1 10 100\n+ 1 20 150\n- 1 10\n+ 1 30 200\n- 1 20\n+ 1 40 "
        "50\n+ 1 50 250\na 1\nm 1";
    std::string expectedOutput = "166\n250\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_AddAndRemoveDifferentGroups) {
    std::string input =
        "5 9\n+ 1 10 100\n- 1 10\n+ 2 10 150\n- 2 10\n+ 3 10 200\n- 3 10\n+ 4 "
        "10 250\na 1\na 4";
    std::string expectedOutput = "0\n250\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_MultipleGroupsHighISUNumbers) {
    std::string input =
        "5 7\n+ 1 1000000 100\n+ 2 2000000 150\n+ 3 3000000 200\n- 1 "
        "1000000\n+ 4 4000000 250\na 1\na 4";
    std::string expectedOutput = "0\n250\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_RemoveNonExistentStudent) {
    std::string input = "5 5\n+ 1 10 100\n- 1 20\na 1\n+ 2 20 150\nm 2";
    std::string expectedOutput = "100\n150\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

TEST(CodeOutputTest, EdgeCase_EmptyInput) {
    std::string input = "5 0\n";
    std::string expectedOutput = "";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}
TEST(CodeOutputTest, EdgeCase_MaxGroupsZeroRequests) {
    std::string input = "10000 0\n";
    std::string expectedOutput = "";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}
// TEST(CodeOutputTest, EdgeCase_MaxGroupsMaxRequests) {
//     std::string input;
//     std::string expectedOutput;
//     input = "10000 10000\n";
//     for (int i = 0; i < 10000; ++i) {
//         input += "+ " + std::to_string(i) + " " + std::to_string(i * 100) +
//                  " " + std::to_string(i) + "\n";
//         expectedOutput += std::to_string(i) + "\n";
//     }
//     for (int i = 0; i < 10000; ++i) {
//         input += "a " + std::to_string(i) + "\n";
//     }
//     EXPECT_EQ(runCodeWithInput(input), expectedOutput);
// }
TEST(CodeOutputTest, EdgeCase_NegativeISU) {
    std::string input = "5 4\n+ 1 -10 100\nm 1\na 1\n- 1 -10";
    std::string expectedOutput = "100\n100\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}
// TEST(CodeOutputTest, EdgeCase_NegativePoints) {
//     std::string input = "5 4\n+ 1 10 -100\nm 1\na 1\n- 1 10";
//     std::string expectedOutput = "-100\n-100\n";
//     EXPECT_EQ(runCodeWithInput(input), expectedOutput);
// }
// TEST(CodeOutputTest, EdgeCase_MultipleNegativePoints) {
//     std::string input = "5 5\n+ 1 10 -100\n+ 1 20 -150\na 1\nm 1\n- 1 10";
//     std::string expectedOutput = "-125\n-150\n";
//     EXPECT_EQ(runCodeWithInput(input), expectedOutput);
// }
// TEST(CodeOutputTest, EdgeCase_HighLoad) {
//     std::string input;
//     std::string expectedOutput;
//     input = "5 1000\n";
//     for (int i = 0; i < 1000; ++i) {
//         input += "+ " + std::to_string(i % 5) + " " + std::to_string(i) + " "
//         +
//                  std::to_string((i + 1) * 10) + "\n";
//         expectedOutput += std::to_string((i + 1) * 10) + "\n";
//     }
//     EXPECT_EQ(runCodeWithInput(input), expectedOutput);
// }
// TEST(CodeOutputTest, EdgeCase_MixedPositiveAndNegativePoints) {
//     std::string input =
//         "5 6\n+ 1 10 100\n+ 1 20 -150\n+ 1 30 200\n+ 1 40 -50\na 1\nm 1";
//     std::string expectedOutput = "25\n200\n";
//     EXPECT_EQ(runCodeWithInput(input), expectedOutput);
// }
TEST(CodeOutputTest, EdgeCase_AddingRemovingSameISUWithinGroup) {
    std::string input =
        "5 8\n+ 1 10 100\n- 1 10\n+ 1 10 150\n- 1 10\n+ 1 10 200\n- 1 10\na "
        "1\nm 1";
    std::string expectedOutput = "0\n0\n";
    EXPECT_EQ(runCodeWithInput(input), expectedOutput);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
