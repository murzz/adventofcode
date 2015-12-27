#define BOOST_TEST_MODULE Advent of Code day 2

#include <boost/predef.h>

#if BOOST_COMP_CLANG
#include <boost/test/included/unit_test.hpp>
#else
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#endif

#include <fstream>
#include <streambuf>
#include <string>
#include <boost/format.hpp>

#include "solution.hpp"
using namespace adventofcode::day2;

///@todo: BOOST_DATA_TEST_CASE
template<typename Solver>
void run_test(const area_type & area, const ribbon_type & ribbon, Solver solver)
{
   const auto solved = solver();

   const auto solved_area = solved.first;
   const auto solved_ribbon = solved.second;

   BOOST_CHECK_MESSAGE(area == solved_area,
         boost::format("solved area is %1%, expected area is %2%!") % solved_area % area);

   BOOST_CHECK_MESSAGE(ribbon == solved_ribbon,
         boost::format("solved ribbon is %1%, expected ribbon is %2%!") % solved_ribbon % ribbon);
}

BOOST_AUTO_TEST_CASE(test)
{
   const auto solver_single = [](const side_type & l, const side_type & w,
         const side_type & h)->auto
   {
      return detail::single_gift(l, w, h);
   };

   const auto solver_single_str = [](const std::string & lwh)->auto
   {
      return detail::many_gifts(lwh);
   };

   const auto solver_many_str = [](const std::string & many_lwh)->auto
   {
      return detail::many_gifts(many_lwh);
   };

   run_test(58, 34, std::bind(solver_single, 2, 3, 4));
   run_test(43, 14, std::bind(solver_single, 1, 1, 10));

   run_test(58, 34, std::bind(solver_single_str, "2x3x4"));
   run_test(43, 14, std::bind(solver_single_str, "1x1x10"));

   run_test(101, 48, std::bind(solver_many_str, "2x3x4\n1x1x10"));
}

BOOST_AUTO_TEST_CASE(solution)
{
   std::ifstream input_data("input-data");
   std::string gift_dimensions_str((std::istreambuf_iterator<char>(input_data)),
         std::istreambuf_iterator<char>());

   const auto solved = solve(gift_dimensions_str);
   const auto solved_area = solved.first;
   const auto solved_ribbon = solved.second;

   BOOST_TEST_MESSAGE(
         boost::format("Solution for day #2: Elves need total %1% square feet of wrapping paper and %2% feet of ribbon!") % solved_area
               % solved_ribbon);
}
