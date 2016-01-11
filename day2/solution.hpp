#pragma once

#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>

namespace adventofcode
{
namespace day2
{

using side_type = int;
using ribbon_type = side_type;
using area_type = side_type;
using result_type = std::pair<area_type, ribbon_type>;

result_type operator +=(result_type & lhs, const result_type & rhs)
{
   lhs.first += rhs.first;
   lhs.second += rhs.second;
   return lhs;
}

namespace detail
{
result_type single_gift(const side_type & l, const side_type & w, const side_type & h)
{
   // area
   const auto lw_area = l * w;
   const auto wh_area = w * h;
   const auto hl_area = h * l;
   const auto smallest_side_area = std::min(std::min(lw_area, wh_area), hl_area);

   const auto area = 2 * lw_area + 2 * wh_area + 2 * hl_area + smallest_side_area;

   // ribbon
   const auto bow = l * w * h; // the feet of ribbon required for
                               // the perfect bow is equal to the cubic feet of volume of the present.
                               // Don't ask how they tie the bow, though; they'll never tell.
   const auto lw_perimeter = 2 * (l + w);
   const auto wh_perimeter = 2 * (w + h);
   const auto hl_perimeter = 2 * (h + l);
   const auto smalles_perimeter = std::min(std::min(lw_perimeter, wh_perimeter), hl_perimeter);
   const auto ribbon = smalles_perimeter + bow;

   return std::make_pair(area, ribbon);
}

result_type single_gift(const std::string & gift_dimension_str)
{
   boost::char_separator<char> sep("x");
   boost::tokenizer<boost::char_separator<char>> gift_dimension(gift_dimension_str, sep);

   // Ugly conversion of tokens to integer dimensions
   std::vector<side_type> gift_dimension_items;

   for (const auto & gift_dimension_item : gift_dimension)
   {
      gift_dimension_items.push_back(std::stoi(gift_dimension_item));
   }

   const auto l = gift_dimension_items.back();
   gift_dimension_items.pop_back();
   const auto w = gift_dimension_items.back();
   gift_dimension_items.pop_back();
   const auto h = gift_dimension_items.back();
   gift_dimension_items.pop_back();

   return single_gift(l, w, h);
}

result_type many_gifts(const std::string & gift_dimensions_str)
{
   boost::char_separator<char> sep("\n");
   boost::tokenizer<boost::char_separator<char>> gift_dimensions(gift_dimensions_str, sep);

   result_type total = std::make_pair(0, 0);

   for (const auto & gift_dimension_str : gift_dimensions)
   {
      total += single_gift(gift_dimension_str);
   }

   return total;
}
}

result_type solve(const std::string & input)
{
   return detail::many_gifts(input);
}

}
}
