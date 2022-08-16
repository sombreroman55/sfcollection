/* location.hh
 *
 * Location data
 *
 */

#pragma once

namespace sfas
{
  struct Location
  {
    private:
      int line_;
      int col_;
      friend class Token;
    public:
      Location();
      Location(int line, int col);
      ~Location();
  };
}
