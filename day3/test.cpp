#define BOOST_TEST_MODULE Advent of Code day 3

#include <boost/predef.h>

#if BOOST_COMP_CLANG
#include <boost/test/included/unit_test.hpp>
#else
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#endif

#include <fstream>
#include <streambuf>
#include <iostream>
#include <string>
#include <boost/format.hpp>

#include "solution.hpp"
using namespace adventofcode::day3;

///@todo: BOOST_DATA_TEST_CASE
void run_test(const result_type & expected, const input_type & input)
{
   const auto solved = solve(input);

   std::stringstream ss_expected;
   ss_expected << expected;

   std::stringstream ss_solved;
   ss_solved << solved;

   BOOST_CHECK_MESSAGE(expected == solved, boost::format("Expected %1%, received %2%") % ss_expected.str() % ss_solved.str());
}

BOOST_AUTO_TEST_CASE(test)
{
   run_test(result_type(2, 2), ">");
   run_test(result_type(4, 5), "^>v<");
   run_test(result_type(2, 11), "^v^v^v^v^v");
   run_test(result_type(4, 6), ">^^v^");
   run_test(result_type(4, 7), "<<<>>>");
   run_test(result_type(5, 8), "<<<>>>>");
   run_test(result_type(7, 13), "<<<>>>^^^vvv");
}

BOOST_AUTO_TEST_CASE(solution)
{
   std::ifstream input_data("input-data");
   std::string input_data_str((std::istreambuf_iterator<char>(input_data)),
         std::istreambuf_iterator<char>());

//   run_test(result_type(-1, 8193), input_data_str);

   const auto solved = solve(input_data_str);
   BOOST_TEST_MESSAGE(boost::format("Solution for day #3: %1% houses receive at least one present!") % solved.first);
}
