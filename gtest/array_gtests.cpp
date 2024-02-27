#include <gtest/gtest.h>

#include <string>

#include "array.hpp"

using namespace std;

TEST(ArrayTests, Length) {
    Array<int> arr{3};
    EXPECT_EQ(arr.length(), 3);

    Array<string> arr2{10};
    EXPECT_EQ(arr2.length(), 10);

    EXPECT_EQ(Array<double>{}.length(), 0);
}


TEST(ArrayTests, CopyConstructor) {
    Array<int> arr{10};
    arr.fill_with_fn([](int) { return 20; });
    Array<int> arr2{arr};
    EXPECT_EQ(arr2.length(), 10);
    EXPECT_EQ(arr2[0], 20);
    EXPECT_EQ(arr2[9], 20);
}


TEST(ArrayTests, MoveConstructor) {
	Array<int> arr{10};
    arr.fill_with_fn([](int) { return 20; });

    Array<int> arr2{std::move(arr)};

    EXPECT_EQ(arr.length(), 0);
    EXPECT_EQ(arr2.length(), 10);
    EXPECT_EQ(arr2[0], 20);
    EXPECT_EQ(arr2[9], 20);
}

TEST(ArrayTests, FillWithFunction) {
    Array<int> arr{10};
    arr.fill_with_fn([](int i) { return i * i; });

    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[9], 81);
}


TEST(ArrayTests, Swap) {
    Array<int> arr{10};
    arr.fill_with_fn([](int) { return 20; });
    Array<int> arr2{2};
    arr2.fill_with_fn([](int) { return 5; });

    swap(arr, arr2);

    EXPECT_EQ(arr2.length(), 10);
    EXPECT_EQ(arr2[0], 20);
    EXPECT_EQ(arr2[9], 20);

    EXPECT_EQ(arr.length(), 2);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 5);
}

TEST(ArrayTests, CopyAssignment) {
    Array<int> arr{10};
    arr.fill_with_fn([](int) { return 20; });

    Array<int> arr2{2};
    arr2.fill_with_fn([](int) { return 5; });

    arr2 = arr;

    EXPECT_EQ(arr2.length(), 10);
    EXPECT_EQ(arr2[0], 20);
    EXPECT_EQ(arr2[9], 20);
}

TEST(ArrayTests, MoveAssignment) {
    Array<int> arr{10};
    arr.fill_with_fn([](int) { return 20; });

    Array<int> arr2{2};
    arr2.fill_with_fn([](int) { return 5; });

    arr2 = std::move(arr);

    EXPECT_EQ(arr2.length(), 10);
    EXPECT_EQ(arr2[0], 20);
    EXPECT_EQ(arr2[9], 20);
}
