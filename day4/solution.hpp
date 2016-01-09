#pragma once

#include <string>
#include <openssl/md5.h>
//#include <functional>
//#include <vector>
//#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <boost/format.hpp>
//#include <boost/tokenizer.hpp>

namespace adventofcode
{
namespace day4
{

using secret_key_type = int;
using second_type = secret_key_type;
using result_type = std::pair<secret_key_type, second_type>;
using input_type = std::string;

std::ostream & operator<<(std::ostream & lhs, const result_type & rhs)
{
   lhs << "[" << rhs.first << ", " << rhs.second << "]";
   return lhs;
}

namespace detail
{

std::string byte_to_hex_string(const unsigned char * digest)
{
   std::string result;

#if 0
//   unsigned char digest[16];
   char buf[32];
   for (int i=0; i<16; i++)
   {
      sprintf(buf, "%02x", digest[i]);
      result.append( buf );
   }
#else
   static const char hexchars[] = "0123456789abcdef";
//   unsigned char digest[16];

   for (int i = 0; i < 16; i++)
   {
      unsigned char b = digest[i];
      char hex[3];

      hex[0] = hexchars[b >> 4];
      hex[1] = hexchars[b & 0xF];
      hex[2] = 0;

      result.append(hex);
   }
#endif

   return result;
}

result_type solve(const input_type & input)
{
   const secret_key_type no_result = -1;
   auto result = result_type(no_result, no_result);

   const std::string test1 = "00000";
   const std::string test2 = "000000";

   for (std::int32_t idx = 1; idx > 0; ++idx)
   {
      const auto new_input = input + std::to_string(idx);
      const auto digest = MD5(reinterpret_cast<const unsigned char*>(new_input.c_str()), new_input.size(), nullptr);
      const auto digest_hex = byte_to_hex_string(digest);
      const auto digest_hex_test1 = digest_hex.substr(0, test1.size());
      const auto digest_hex_test2 = digest_hex.substr(0, test2.size());

      if (test1 == digest_hex_test1 && result.first == no_result)
      {
         result.first = idx;
      }

      if (test2 == digest_hex_test2 && result.second == no_result)
      {
         result.second = idx;
      }

      if (result.first != no_result && result.second != no_result)
      {
         return result;
      }
   }
   return result;
}
}

result_type solve(const input_type & input)
{
   return detail::solve(input);
}

}
}
