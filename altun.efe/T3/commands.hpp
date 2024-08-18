#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <vector>
#include <map>
#include <functional>
#include "polygon.hpp"

namespace altun
{
  void count(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void getArea(std::ostream&,
      std::istream&,
      const std::vector< Polygon >&,
      const std::map< std::string, std::function< bool(const Polygon&) > >&);

  void findMax(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons);

  void findMin(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons);

  void maxSeq(std::ostream& out, std::istream& in,
      const std::vector< Polygon >& polygons);

  void echo(std::ostream& out, std::istream& in,
      std::vector< Polygon >& polygons);

}
#endif
