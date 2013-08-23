#ifndef D_UTIL_ASSERT_H
#define D_UTIL_ASSERT_H

#include <boost/shared_ptr.hpp>
#include "CppUTest/TestHarness.h"

#define SHARED_PTRS_EQUAL(expect, actual) \
    SHARED_PTRS_EQUAL_LOCATION(expect, actual, __FILE__, __LINE__)

#define CHECK_SHARED_PTR_NULL(actual) \
    CHECK_SHARED_PTR_NULL_LOCATION(actual, __FILE__, __LINE__)

template <class T_Expect, class T_Actual>
void SHARED_PTRS_EQUAL_LOCATION(boost::shared_ptr<T_Expect> expect,
                                boost::shared_ptr<T_Actual>  actual,
                                const char *fileName, int lineNumber)
{
    POINTERS_EQUAL_LOCATION(expect.get(), actual.get(), fileName, lineNumber);
}

template <class T_Actual>
void CHECK_SHARED_PTR_NULL_LOCATION(boost::shared_ptr<T_Actual>  actual,
                                    const char *fileName, int lineNumber)
{
    POINTERS_EQUAL_LOCATION(NULL, actual.get(), fileName, lineNumber);
}


#endif
