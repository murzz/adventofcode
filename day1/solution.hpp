#pragma once

#include "helper/solution.hpp"

#include <stdexcept>
#include <sstream>


namespace adventofcode
{
namespace day1
{
namespace detail
{
output_type solve(const input_type & map)
{
   auto floor = 0; // start counting floors from 0
   const auto basement = -1; // basement floor number is -1
   auto is_basement_visited = false;
   auto position = 0; // position of first basement visit
   const std::stringstream::char_type up = '(';
   const std::stringstream::char_type down = ')';

   std::stringstream::char_type direction;
   std::stringstream map_stream(map);
   while (map_stream >> direction)
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
            throw std::invalid_argument(std::string("Invalid direction: ") + direction);
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

output_type solve(const input_type & input)
{
   return detail::solve(input);
}

}
}
