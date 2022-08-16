/* location.cc
 *
 * Location data
 *
 */

#include "location.hh"

namespace sfas
{
  Location::Location() : line_(-1), col_(-1) {}
  Location::Location(int line, int col) : line_(line), col_(col) {}
  Location::~Location() = default;
}
