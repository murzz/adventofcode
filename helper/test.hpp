#pragma once

#include <tuple>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

#include "helper/solution.hpp"

namespace adventofcode
{

class dataset
{
public:
   enum
   {
      arity = 3
   };

   struct iterator
   {
      iterator(boost::property_tree::ptree::iterator iter) :
            iter_(iter)
      {
      }

      auto operator*() const
      {
         const auto input = iter_->second.get<adventofcode::input_type>("input");
         const auto output1 = iter_->second.get<adventofcode::output_type::first_type>("output1");
         const auto output2 = iter_->second.get<adventofcode::output_type::second_type>("output2");

         return std::make_tuple(input, output1, output2);
      }

      void operator++()
      {
         iter_++;
      }

   private:
      boost::property_tree::ptree::iterator iter_;
   };

   dataset()
   {
      boost::property_tree::read_info("test-data", tree_);
   }

   boost::unit_test::data::size_t size() const
   {
      return tree_.size();
   }

   iterator begin()
   {
      return iterator(tree_.begin());
   }

private:
   boost::property_tree::ptree tree_;
};

}

namespace boost
{
namespace unit_test
{
namespace data
{
namespace monomorphic
{
// registering adventofcode::dataset as a proper dataset
template<>
struct is_dataset<adventofcode::dataset> : boost::mpl::true_
{
};
}
}
}
}

#define TEST(test_case_name)                                                               \
BOOST_DATA_TEST_CASE( test_case_name, adventofcode::dataset(), input, output1, output2)    \
{                                                                                          \
   const auto output = solve(input);                                                       \
   BOOST_CHECK(output.first == output1);                                                   \
   BOOST_CHECK(output.second == output2);                                                  \
}
