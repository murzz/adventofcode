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

   bool is_self(const house & rhs) const

   {
      return &rhs == this;
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

using houses = std::vector<house>;

void visit_house(houses & visited_houses, const santa & santa)
{
   const house visited_house(santa);
   visited_houses.push_back(visited_house);
}

void trim_houses(const houses & visited_houses, houses & unique_houses)
{
   for (const auto & house : visited_houses)
   {
      const auto unique_house = std::find(unique_houses.begin(), unique_houses.end(), house);
      if (unique_house == unique_houses.end())
      {
         // house not found, it is unique
         unique_houses.push_back(house);
      }
   }
}

result_type solve(const input_type & input)
{
   // last year
   houses visited_houses_last;
   houses unique_houses_last;

   // this year
   houses visited_houses_this;
   houses unique_houses_this;

   // starting point, first house should be visited there too
   detail::santa santa_last;
   visit_house(visited_houses_last, santa_last);

   detail::santa santa_this;
   detail::santa robo_santa_this;
   visit_house(visited_houses_this, santa_this); // both are visiting the same house

   // movements replay
   auto whos_turn = 2;
   for (const auto& step : input)
   {
      // last year
      santa_last.move(step);
      visit_house(visited_houses_last, santa_last);

      // this year
      if (whos_turn % 2)
      {
         santa_this.move(step);
         visit_house(visited_houses_this, santa_this);
      }
      else
      {
         robo_santa_this.move(step);
         visit_house(visited_houses_this, robo_santa_this);
      }
      whos_turn++;
   }

   // analysis
   trim_houses(visited_houses_last, unique_houses_last);
   trim_houses(visited_houses_this, unique_houses_this);

   return result_type(unique_houses_last.size(), unique_houses_this.size());
}
}

result_type solve(const input_type & input)
{
   return detail::solve(input);
}

}
}
