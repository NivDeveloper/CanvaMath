#pragma once

#include <iostream>
#include <cassert>

#ifdef NDEBUG
#define MY_ASSERT(condition, message) ((void)0)
#else
#define MY_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << message << " in " << __FILE__ << " at line " << __LINE__ << std::endl; \
            assert(condition); \
        } \
    } while (false)
#endif