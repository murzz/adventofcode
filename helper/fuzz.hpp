#pragma once

#include <stdexcept>
#include <iostream>

#include "helper/solution.hpp"

#define ADVENT_OF_CODE_FUZZ() \
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) \
{ \
    try{ \
        adventofcode::input_type input(reinterpret_cast<const char*>(data), size); \
        const auto output = solve(input); \
        (void)output; \
    } \
    catch(const std::exception & e) { \
        std::cout << e.what() << std::endl; \
    } \
    return 0; \
}
