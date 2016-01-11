#pragma once

#include <string>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace adventofcode
{
namespace day5
{

using first_result_type = int;
using second_result_type = first_result_type;
using result_type = std::pair<first_result_type, second_result_type>;
using input_type = std::string;

std::ostream & operator<<(std::ostream & lhs, const result_type & rhs)
{
   lhs << "[" << rhs.first << ", " << rhs.second << "]";
   return lhs;
}

namespace detail
{

bool has_three_vowels(const input_type & input)
{
   const input_type vowels = "aeiou";
   auto vowels_count = 0;
   for (const auto & vowel : vowels)
   {
      for (auto pos = input.find(vowel); pos != std::string::npos; pos = input.find(vowel, pos + 1))
      {
         vowels_count++;
      }

      if (vowels_count >= 3)
      {
         return true;
      }
   }

   return false;
}

bool has_twice_in_a_row(const input_type & input)
{
   input_type::value_type prev_ch = '\t'; // no string should start with tab
   for (const auto & ch : input)
   {
      if (prev_ch == ch)
      {
         return true;
      }
      prev_ch = ch;
   }

   return false;
}

bool contains_subs(const input_type & input)
{
   std::vector<input_type> subs = { "ab", "cd", "pq", "xy" };
   for (const auto & sub : subs)
   {
      const auto idx = input.find(sub);
      const bool found = idx != std::string::npos;
      if (found)
      {
         return true;
      }
   }

   return false;
}

bool has_pair_twice(const input_type & input)
{
   // tokenize per pairs
   std::vector<input_type> pairs;
   for (input_type::size_type idx = 0; idx < input.size(); idx++)
   {
      const auto substr = input.substr(idx, 2);
      pairs.push_back(substr);
   }

   // find at least 2 pairs
   for (const auto & pair : pairs)
   {
      if (pair.size() != 2)
      {
         continue;
      }

      auto pair_count = 0;
      for (auto pos = input.find(pair); pos != std::string::npos; pos = input.find(pair, pos + 2))
      {
         pair_count++;
      }

      if (pair_count >= 2)
      {
         return true;
      }
   }
   return false;
}

bool has_splitted_pair(const input_type & input)
{
   input_type::value_type prev_prev_ch = '\t'; // no string should start with tab
   input_type::value_type prev_ch = '\t'; // no string should start with tab
   for (const auto & ch : input)
   {
      if (prev_prev_ch == ch)
      {
         return true;
      }
      prev_prev_ch = prev_ch;
      prev_ch = ch;
   }

   return false;
}

bool is_nice(const input_type & input)
{
   return has_three_vowels(input) && has_twice_in_a_row(input) && !contains_subs(input);
}

bool is_nicer(const input_type & input)
{
   return has_pair_twice(input) && has_splitted_pair(input);
}

result_type solve(const input_type & input)
{
   boost::char_separator<char> sep("\n");
   boost::tokenizer<boost::char_separator<char>> input_lines(input, sep);

   first_result_type nice = 0;
   first_result_type nicer = 0;

   for (const auto & line : input_lines)
   {
      if (is_nice(line))
      {
         nice++;
      }

      if (is_nicer(line))
      {
         nicer++;
      }
   }

   return result_type(nice, nicer);
}

}

result_type solve(const input_type & input)
{
   return detail::solve(input);
}

}
}
