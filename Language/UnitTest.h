#pragma once
#include <iostream>

#define TEST_PRINT(MESSAGE)     std::cout << (MESSAGE) << std::endl
#define TEST_SUCCEED            TEST_PRINT("succeed")
#define TEST_FAIL               TEST_PRINT("fail")

#define TEST_ASSERT(CONDITION)          \
if (!!(CONDITION)) { TEST_SUCCEED; }    \
else { TEST_FAIL; throw 0; }

#define TEST_CASE(NAME)                 \
extern void TEST_CASE_FUNCTION_##NAME();\
class TEST_CASE_CLASS_##NAME            \
{                                       \
public:                                 \
    TEST_CASE_CLASS_##NAME()            \
    {                                   \
        TEST_PRINT(#NAME);              \
        TEST_CASE_FUNCTION_##NAME();    \
    }                                   \
} TEST_CASE_INSTANCE_##NAME;            \
void TEST_CASE_FUNCTION_##NAME()