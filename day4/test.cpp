#define BOOST_TEST_MODULE Advent of Code day 4

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
using namespace adventofcode::day4;

///@todo: BOOST_DATA_TEST_CASE
void run_test(const result_type & expected, const input_type & input)
{
   const auto solved = solve(input);

   std::stringstream ss_expected;
   ss_expected << expected;

   std::stringstream ss_solved;
   ss_solved << solved;

   BOOST_CHECK_MESSAGE(expected == solved,
         boost::format("Expected %1%, received %2%") % ss_expected.str() % ss_solved.str());
}

BOOST_AUTO_TEST_CASE(test)
{
   run_test(result_type(609043, 6742839), "abcdef");
   run_test(result_type(1048970, 5714438), "pqrstuv");
}

BOOST_AUTO_TEST_CASE(solution)
{
   std::ifstream input_data("/home/dm/git/adventofcode/day4/input-data");
   std::string input_data_str((std::istreambuf_iterator<char>(input_data)),
         std::istreambuf_iterator<char>());

   run_test(result_type(346386, 9958218), input_data_str);

   const auto solved = solve(input_data_str);
   BOOST_TEST_MESSAGE(
         boost::format("Solution for day #4: %1% is lowest positive number for 5 zeros, %2% for 6 zeros!")
               % solved.first % solved.second);
}
