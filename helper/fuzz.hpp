#pragma once

#include "helper/solution.hpp"

#define ADVENT_OF_CODE_FUZZ() \
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) \
{ \
    adventofcode::input_type input(reinterpret_cast<const char*>(data), size); \
    const auto output = solve(input); \
    return 0; \
}
