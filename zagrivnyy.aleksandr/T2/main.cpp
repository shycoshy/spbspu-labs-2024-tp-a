#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#include "dataStruct.hpp"
#include "delimiter.hpp"

int main()
{
  using input_it_t = std::istream_iterator< zagrivnyy::DataStruct >;
  std::vector< zagrivnyy::DataStruct > data;

  while (!(std::cin.eof()))
  {
    std::copy(input_it_t{std::cin}, input_it_t{}, std::back_inserter(data));

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using output_it_t = std::ostream_iterator< zagrivnyy::DataStruct >;
  std::copy(data.begin(), data.end(), output_it_t{std::cout, "\n"});

  return 0;
}
