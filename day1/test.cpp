#define BOOST_TEST_MODULE Advent of Code day 1

//#include <boost/predef.h>

//#if BOOST_COMP_CLANG
//#include <boost/test/included/unit_test.hpp>
//#else
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
//#endif

#include <sstream>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <boost/format.hpp>

#include "solution.hpp"
#include "helpers/solve_macro.hpp"

namespace bdata = boost::unit_test::data;
using namespace adventofcode::day1;

namespace
{
   const std::array<int, 10> floors
      { 0, 0, 3, 3, -1, -1, -3, -3, -1, -1 };
   const std::array<int, 10> positions
      { -1, -1, -1, -1, 3, 1, 1, 1, 1, 5 };
   const std::array<std::string, 10> maps
      { "(())", "()()", "(((", "(()(()(", "())", "))(", ")))", ")())())", ")", "()())" };
}

BOOST_DATA_TEST_CASE(test, bdata::make(floors) ^ positions ^ maps, floor, position, map)
{
   const auto solved = solve(std::stringstream(map));
   const auto solved_floor = solved.first;
   const auto solved_position = solved.second;

   BOOST_CHECK_MESSAGE(floor == solved_floor,
         boost::format("solved floor is %1%, expected floor is %2%!") % solved_floor % floor);

   BOOST_CHECK_MESSAGE(position == solved_position,
         boost::format("solved position is %1%, expected position is %2%!") % solved_position % position);
}

SOLVE(74, 1795, "Solution for day #1: Santa's floor is floor #%1%, he will enter basement on his %2%(th) move!")
