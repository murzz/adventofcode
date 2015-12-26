#define BOOST_TEST_MODULE advent of code day 1 tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <boost/format.hpp>

#include "solution.hpp"
using namespace adventofcode::day1;

///@todo: BOOST_DATA_TEST_CASE
void run_test(const int & floor, const int & position, const std::string & map)
{
   const auto solved = solve(std::stringstream(map));
   const auto solved_floor = solved.first;
   const auto solved_position = solved.second;

   BOOST_CHECK_MESSAGE(floor == solved_floor,
         boost::format("solved floor is %1%, expected floor is %2%!") % solved_floor % floor);

   BOOST_CHECK_MESSAGE(position == solved_position,
         boost::format("solved position is %1%, expected position is %2%!") % solved_position % position);
}

BOOST_AUTO_TEST_CASE(test)
{
   run_test(0, -1, "(())");
   run_test(0, -1, "()()");

   run_test(3, -1, "(((");
   run_test(3, -1, "(()(()(");

   run_test(-1, 3, "())");
   run_test(-1, 1, "))(");

   run_test(-3, 1, ")))");
   run_test(-3, 1, ")())())");

   run_test(-1, 1, ")");
   run_test(-1, 5, "()())");
}

BOOST_AUTO_TEST_CASE(solution)
{
   std::ifstream input_data("input-data");
   const auto solved = solve(std::move(input_data));
   const auto solved_floor = solved.first;
   const auto solved_position = solved.second;

   BOOST_TEST_MESSAGE(boost::format("Santa's floor is floor #%1%, he will enter basement on his %2%(th) move") % solved_floor % solved_position);
}
