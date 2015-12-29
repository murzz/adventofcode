#pragma once

#include <string>
#include <vector>
#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <boost/format.hpp>
//#include <boost/tokenizer.hpp>

namespace adventofcode
{
namespace day3
{

using houses_type = int;
using second_type = houses_type;
//using area_type = side_type;
using result_type = std::pair<houses_type, second_type>;
using input_type = std::string;

std::ostream & operator<<(std::ostream & lhs, const result_type & rhs)
{
   lhs << "[" << rhs.first << ", " << rhs.second << "]";
   return lhs;
}

//result_type operator +=(result_type & lhs, const result_type & rhs)
//{
//   lhs.first += rhs.first;
//   lhs.second += rhs.second;
//   return lhs;
//}

namespace detail
{
namespace move
{
constexpr input_type::value_type north = '^';
constexpr input_type::value_type south = 'v';
constexpr input_type::value_type east = '>';
constexpr input_type::value_type west = '<';
}

struct santa
{
   int x_;
   int y_;
   santa(int x = 0, int y = 0) :
         x_(x), y_(y)
   {
   }
   void move(const input_type::value_type & direction)
   {
      switch (direction)
      {
         case move::north:
            north();
            break;
         case move::south:
            south();
            break;
         case move::east:
            east();
            break;
         case move::west:
            west();
            break;
         default:
            std::cerr << "Unexpected direction: " << direction << std::endl;
      }
   }
   void north()
   {
      y_++;
   }
   void south()
   {
      y_--;
   }
   void east()
   {
      x_++;
   }
   void west()
   {
      x_--;
   }
};

std::ostream & operator<<(std::ostream & lhs, const santa & rhs)
{
   lhs << "[" << rhs.x_ << ", " << rhs.y_ << "]";
   return lhs;
}

struct house
{
   int x_;
   int y_;
   int visited_;

   house(const house & house) :
         x_(house.x_), y_(house.y_), visited_(house.visited_)
   {
   }

   house(const santa & santa) :
         x_(santa.x_), y_(santa.y_), visited_(1)
   {
   }

   int r(const house & house) const

   {
//      return std::sqrt(house.x_ * house.x_ + house.y_ * house.y_);
      return house.x_ + house.y_;
//      return house.x_ * house.y_ ;
   }

   bool is_self(const house & rhs) const

   {
      return &rhs == this;
   }

   bool operator<(const house & rhs) const

   {
      return r(*this) < r(rhs);
   }

   bool operator==(const house & rhs) const

   {
      return (x_ == rhs.x_) && (y_ == rhs.y_);
   }

   house & operator=(const house & rhs)

   {
      x_ = rhs.x_;
      y_ = rhs.y_;
      visited_ = rhs.visited_;
      return *this;
   }
};

std::ostream & operator<<(std::ostream & lhs, const house & rhs)
{
   lhs << "[" << rhs.x_ << ", " << rhs.y_ << ", " << rhs.visited_ << "]";
   return lhs;
}

//using houses = std::set<house>;
using houses = std::vector<house>;

void visit_house(houses & visited_houses, const santa & santa)
{
   const house visited_house(santa);
   visited_houses.push_back(visited_house);
}

void calculate_repititions(houses & visited_houses)
{
   for (auto & test_house : visited_houses)
   {
      for (const auto & house : visited_houses)
      {
         if (house == test_house && !house.is_self(test_house))
         {
            test_house.visited_++;
         }
      }
   }
}

void trim_houses(houses & visited_houses, houses & unique_houses)
{

//   houses.erase(std::remove_if(houses.begin(),
//         houses.end(),
//         [](auto x)
//         {  return std::isspace(x);
//         }),
//         houses.end());

//   std::sort(houses.begin(), houses.end());
//   auto last = std::unique(houses.begin(), houses.end());
//   houses.erase(last, houses.end());

   for (const auto & house : visited_houses)
   {
      const auto found = std::find(unique_houses.begin(), unique_houses.end(), house);
      if (found == unique_houses.end())
      {
         unique_houses.push_back(house);
      }
   }
}

void print_houses(const houses & houses, const std::string & header)
{
   std::cout << header << std::endl;
   for (const auto & house : houses)
   {
      std::cout << house << std::endl;
   }
}

result_type solve(const input_type & input)
{
   houses visited_houses;
   houses unique_houses;

   // starting point, first house should be visited there too
   santa santa;
   visit_house(visited_houses, santa);

   // movements
   for (const auto& step : input)
   {
      santa.move(step);
      visit_house(visited_houses, santa);
   }
   const auto visited_count = visited_houses.size();

   // analysis
//   calculate_repititions(visited_houses);

//   print_houses(visited_houses, "--- before ---");

   trim_houses(visited_houses, unique_houses);

//   print_houses(visited_houses, "--- after ---");

   return result_type(unique_houses.size(), visited_count);
}
}

result_type solve(const input_type & input)
{
   return detail::solve(input);
}

}
}
