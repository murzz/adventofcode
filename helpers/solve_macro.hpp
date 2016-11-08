#pragma once

//#include <boost/test/included/unit_test.hpp>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct OptionsFixture
{
   OptionsFixture()
   {
      po::options_description options("Allowed options");
      options.add_options()
         ("help", "produce help message")
         ("filename,f", po::value<std::string>()->default_value("input-data"), "input data filename");

      po::store(
            po::parse_command_line(boost::unit_test::framework::master_test_suite().argc,
                  boost::unit_test::framework::master_test_suite().argv, options), vm_);
      po::notify(vm_);

      if (vm_.count("help"))
      {
         std::cout << options << "\n";
      }
   }

   po::variables_map vm_;

   const std::string & input_data_file_name() const
   {
      return vm_["filename"].as<std::string>();
   }
};

#define SOLVE(first_param, second_param, message)                                        \
BOOST_FIXTURE_TEST_CASE(solution, OptionsFixture)                                        \
{                                                                                        \
   BOOST_TEST_MESSAGE(boost::format("Loading test data: %1%") % input_data_file_name()); \
                                                                                         \
   std::ifstream input_data(input_data_file_name());                                     \
   const auto solved = solve(std::move(input_data));                                     \
                                                                                         \
   BOOST_TEST_MESSAGE(boost::format(message) % solved.first % solved.second);            \
   BOOST_TEST(solved.first == first_param);                                              \
   BOOST_TEST(solved.second == second_param);                                            \
}
