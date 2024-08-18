#include "commands.hpp"

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "helpers.hpp"
#include "figures.hpp"

void demin::doarea(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcommand = "";
  std::cin >> subcommand;
  std::vector< Polygon > filteredPolygons;
  std::function< double(const Polygon &) > countArea = getArea;

  if (subcommand == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), even);
  }
  else if (subcommand == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), odd);
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("<INVALID COMMAD>");
    }

    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons));
  }
  else
  {
    size_t nVertexes = 0;
    try
    {
      nVertexes = std::stoull(subcommand);
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAD>");
    }

    if (nVertexes < 3)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAD>");
    }

    using namespace std::placeholders;
    auto vertexesFilter = std::bind(checkVertexes, nVertexes, _1);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), vertexesFilter);
  }

  std::vector< double > areas;
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), countArea);
  double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (subcommand == "MEAN")
  {
    result /= polygons.size();
  }
  out << result << '\n';
}

void demin::domin(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    in.setstate(std::ios::failbit);
    throw std::logic_error("<INVALID COMMAD>");
  }

  std::vector< Polygon >::const_iterator min;
  std::string subcommand;
  std::cin >> subcommand;

  if (subcommand == "AREA")
  {
    min = std::min_element(polygons.cbegin(), polygons.cend(), compareAreas);
    out << getArea(*min) << '\n';
  }
  else if (subcommand == "VERTEXES")
  {
    min = std::min_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    out << (*min).points.size();
  }
  else
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("INVALID COMMAD>");
  }
}

void demin::domax(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    in.setstate(std::ios::failbit);
    throw std::logic_error("<INVALID COMMAD>");
  }

  std::vector< Polygon >::const_iterator max;
  std::string subcommand;
  std::cin >> subcommand;

  if (subcommand == "AREA")
  {
    max = std::max_element(polygons.cbegin(), polygons.cend(), compareAreas);
    out << getArea(*max) << '\n';
  }
  else if (subcommand == "VERTEXES")
  {
    max = std::max_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    out << (*max).points.size();
  }
  else
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("<INVALID COMMAD>>");
  }
}
