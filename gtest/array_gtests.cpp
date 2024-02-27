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

TEST(ArrayTests, Subscript) {
    Array<int> arr{10};
    arr[0] = 3;
    arr[3] = 5;
    EXPECT_EQ(arr[0], 3);
    EXPECT_EQ(arr[3], 5);

    Array<string> s_arr{2};
    s_arr[0] = "this";
    s_arr[1] = "test";
    EXPECT_EQ(s_arr[0], "this");
    EXPECT_EQ(s_arr[1], "test");
}

TEST(ArrayTests, Print) {
    stringstream out;

    Array<int> arr{3};
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    out << arr;

    EXPECT_EQ(out.str(), "0 1 2 ");
}

TEST(ArrayTests, Read) {
    stringstream in{"1 2 3"};

    Array<int> arr{3};
    in >> arr;

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}


TEST(IntArrayTests, OutOfBounds) {
    Array<int> arr{10};
    EXPECT_ANY_THROW(arr[11]);
}


