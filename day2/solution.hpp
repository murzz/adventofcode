#pragma once

#include <iostream>
#include <fstream>
#include <boost/format.hpp>

namespace adventofcode
{
namespace day1
{
using result_type = std::pair<int, int>;
namespace detail
{
result_type solution(std::istream && map)
{
   auto floor = 0; // start counting floors from 0
   const auto basement = -1; // basement floor number is -1
   auto is_basement_visited = false;
   auto position = 0; // position of first basement visit
   const std::istream::char_type up = '(';
   const std::istream::char_type down = ')';

   std::istream::char_type direction;
   while (map >> direction)
   {
      if (direction == up)
      {
         floor++;
      }
      else
         if (direction == down)
         {
            floor--;
         }
         else
         {
            std::cerr << boost::format("unknown direction '%1%'") % direction << std::endl;
            // although direction is incorrect it will be still count
         }

      if (!is_basement_visited)
      {
         position++;
      }

      if (basement == floor)
      {
         is_basement_visited = true;
      }
   }
   return std::make_pair(floor, is_basement_visited ? position : -1);
}
}

result_type solve(std::istream && input)
{
   return detail::solution(std::move(input));
}

result_type solve()
{
   std::ifstream input_data("input-data");
   return solve(std::move(input_data));
}

}
}
