#define BOOST_TEST_MODULE Advent of Code

#include <boost/predef.h>

#if BOOST_COMP_CLANG
#include <boost/test/included/unit_test.hpp>
#else
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#endif

#include <fstream>
#include <streambuf>
#include <sstream>
#include <boost/format.hpp>

#include "solution.hpp"
using namespace adventofcode::day5;

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
   run_test(result_type(1, 0), "ugknbfddgicrmopn");
   run_test(result_type(1, 0), "aaa");
   run_test(result_type(0, 0), "jchzalrnumimnmhp");
   run_test(result_type(0, 0), "haegwjzuvuyypxyu");
   run_test(result_type(0, 0), "dvszwmarrgswjxmb");

   run_test(result_type(0, 1), "qjhvhtzxzqqjkmpb");
   run_test(result_type(0, 1), "xxyxx");
   run_test(result_type(0, 0), "uurcxstgmygtbstg");
   run_test(result_type(0, 0), "ieodomkazucvgmuy");
   run_test(result_type(0, 1), "aabaaba");
   run_test(result_type(0, 1), "aabaa");
   run_test(result_type(0, 1), "xyxy");
   run_test(result_type(0, 1), "xyxyxyx");
   run_test(result_type(0, 1), "xyxyabcdefeghi");
   run_test(result_type(0, 1), "aabcdefgaaabcdefeghi");
   run_test(result_type(0, 1), "aaaxyxy");
}

BOOST_AUTO_TEST_CASE(solution)
{
   std::ifstream input_data("input-data");
   std::string input_data_str((std::istreambuf_iterator<char>(input_data)),
         std::istreambuf_iterator<char>());

   run_test(result_type(258, 53), input_data_str);

   const auto solved = solve(input_data_str);
   BOOST_TEST_MESSAGE(
         boost::format("Solution for day #5: %1% strings are nice, %2% are nicer!")
               % solved.first % solved.second);
}
