#include <gtest/gtest.h>
#include "../Utils/vec.h"

TEST(TestCaseName, TestName) 
{
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(vec, constructor)
{
    fck::vec<int, 5> a = { 1, 2, 3, 4, 5, 6 };
    fck::vec<int, 5> b = { 1, 2, 3, 4, 5 };
    fck::vec<int, 5> c = { 1,2, 3 };

    a.print();
    b.print();
    c.print();
}

/*TEST(vec, add)
{
    fck::vec<int, 5> a = { 1, 2, 3, 4, 5, 6 };
    fck::vec<int, 5> b = { 1, 2, 3, 4, 5 };
    auto c = fck::operator+(a, b);
    c.print();
}*/

TEST(vec, length)
{
    fck::vec<int, 3> a = { 1, 2, 3 };

    EXPECT_GT(a.length(), 3);
}
