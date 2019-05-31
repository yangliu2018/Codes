#include "UnitTest.h"

TEST_CASE(test1)
{
    TEST_ASSERT(2 + 2 == 1 + 3);
}

TEST_CASE(test2)
{
    TEST_ASSERT(1 + 1 == 2);
}

TEST_CASE(test3)
{
    TEST_ASSERT(1 + 1 == 3);
}


int main()
{
    return 0;
}
