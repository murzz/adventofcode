#pragma once

#include <tuple>
#include <string>
#include <iostream>
#include <algorithm>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
namespace ut = boost::unit_test;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
namespace pt = boost::property_tree;

//#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <boost/format.hpp>

#include "helper/solution.hpp"

namespace adventofcode
{

class dataset
{
public:
   enum
   {
      arity = 4
   };

   struct iterator
   {
      iterator(pt::ptree::iterator iter) :
            iter_(iter)
      {
      }

      auto operator*() const
      {
         const auto title = iter_->first;
         const auto input = iter_->second.get<adventofcode::input_type>("input");
         const auto output1 = iter_->second.get<adventofcode::output_type::first_type>("output1");
         const auto output2 = iter_->second.get<adventofcode::output_type::second_type>("output2");

         return std::make_tuple(title, input, output1, output2);
      }

      void operator++()
      {
         iter_++;
      }

      private:
         pt::ptree::iterator iter_;
   };

   dataset()
   {
      pt::read_info("test-data", tree_);
   }

   ut::data::size_t size() const
   {
      return tree_.size();
   }

   iterator begin()
   {
      return iterator(tree_.begin());
   }

private:
   pt::ptree tree_;

//       //TODO: this class is constructed before test suite is registered thus master_test_suite().argc/argv is empty
//   const std::string test_data_filename()
//   {
//      po::options_description options("Test options");
//      options.add_options()
//         ("help", "produce help message")
//         ("input,i", po::value<std::string>()->default_value("test-data"), "input data filename");
//
//      std::cout << ut::framework::master_test_suite().argc;
//      po::variables_map vm;
//      po::store(
//            po::parse_command_line(ut::framework::master_test_suite().argc,
//                  ut::framework::master_test_suite().argv, options), vm);
//      po::notify(vm);
//
//      if (vm.count("help"))
//      {
//         std::cout << options << std::endl;
//      }
//
//      return vm["filename"].as<std::string>();
//   }

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

//TODO: usage of BOOST_TEST_MESSAGE causes `Failure occurred in a following context:` message, WTF?
#define ADVENT_OF_CODE_TEST(test_case_name)\
BOOST_DATA_TEST_CASE(test_case_name, adventofcode::dataset(), title, input, output1, output2)\
{\
   const auto output = solve(input);\
   BOOST_CHECK(output.first == output1);\
   BOOST_CHECK(output.second == output2);\
   const auto has_2_placeholders = [](const auto & title)->bool{return 4 == std::count(std::begin(title), std::end(title), '%');};\
   if (has_2_placeholders(title)) {std::cout << boost::format(title) % output.first % output.second << std::endl;}\
}
