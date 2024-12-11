#include <gtest/gtest.h>

#include "quicksort.h"
#include "utils.h"

/**
 * @brief test Generates a random sequence of specified size and sorts it with Quicksort using N threads.
 * @param nbThreads number of threads to use to sort the sequence
 * @param size of the sequence to sort
 * @param seed to use for the random generation of the sequence
 */
void test(int nbThreads, int size, int seed) {
    Quicksort<int> sorter(nbThreads);
    std::vector<int> array = generateSequence(size, seed);
    sorter.sort(array);
    EXPECT_FALSE(array.empty());  // check that the result is not empty
    EXPECT_TRUE(isSorted(array)); // check that result is sorted
}


TEST(SortingTest, Test1) {
    int size = 16;
    int nbThreads = 2;
    int seed = 23;

    test(nbThreads, size, seed);
}

TEST(SortingTest2, Test2) {
    int size = 16;
    int nbThreads = 4;
    int seed = 23;

    test(nbThreads, size, seed);
}

TEST(SortingTest3, Test3) {
    int size = 16;
    int nbThreads = 8;
    int seed = 23;

    test(nbThreads, size, seed);
}

TEST(SortingTest4, Test4) {
    int size = 16;
    int nbThreads = 16;
    int seed = 23;

    test(nbThreads, size, seed);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
