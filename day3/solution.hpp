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
constexpr input_type::value_type up = '^';
constexpr input_type::value_type down = 'v';
constexpr input_type::value_type right = '>';
constexpr input_type::value_type left = '<';
}

struct santa
{
   int x_;
   int y_;
   santa(int x = 0, int y = 0) :
         x_(x), y_(y)
   {
   }
   void move(const input_type::value_type & step)
   {
      switch (step)
      {
         case move::up:
            up();
            break;
         case move::down:
            down();
            break;
         case move::right:
            right();
            break;
         case move::left:
            left();
            break;
      }
   }
   void up()
   {
      y_++;
   }
   void down()
   {
      y_--;
   }
   void right()
   {
      x_++;
   }
   void left()
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
         x_(house.x_), y_(house.y_), visited_(0)
   {
   }

   house(const santa & santa) :
         x_(santa.x_), y_(santa.y_), visited_(0)
   {
   }

   int r(const house & house) const
         {
//      return std::sqrt(house.x_ * house.x_ + house.y_ * house.y_);
      return house.x_ + house.y_;
//      return house.x_ * house.y_ ;
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

void remember_house(houses & houses, const santa & santa)
{
//   const house santa_house(santa);
//   for (const auto & house : houses)
//   {
//      std::cout << santa_house << "==" << house << " " << (santa_house == house) << std::endl;
//      std::cout << "!(" << santa_house << "<" << house << ") " << !(santa_house < house) << std::endl;
//      std::cout << "!(" << house << "<" << santa_house << ") " << !(house < santa_house) << std::endl;
//      std::cout << "                   " << ((santa_house < house) && !(house < santa_house)) << std::endl;
//   }
//
//   detail::house house(santa);
//   const auto inserted = houses.insert(house);
//   std::cout << "Santa " << santa << " inserted " << inserted.second << " s = " << houses.size() << std::endl;

   const house santa_house(santa);
   houses.push_back(santa_house);
}

void trim_houses(houses & houses)
{
//   std::cout << "before--------" << std::endl;
//   for (const auto & house : houses)
//   {
//      std::cout << house << std::endl;
//   }
   std::sort(houses.begin(), houses.end());
   auto last = std::unique(houses.begin(), houses.end());
   houses.erase(last, houses.end());
   std::cout << "after--------" << std::endl;

//      for (const auto & house : houses)
//      {
//         std::cout << house << std::endl;
//      }
}

result_type solve(const input_type & input)
{
   houses houses;
   santa santa;

   // starting point
   remember_house(houses, santa);

   // movements
   for (const auto & step : input)
   {
      santa.move(step);
      remember_house(houses, santa);
   }
   trim_houses(houses);
   return result_type(houses.size(), -1);
}
}

result_type solve(const input_type & input)
{
   return detail::solve(input);
}

}
}
