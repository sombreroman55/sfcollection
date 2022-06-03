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
        int _line;
        int _col;
    public:
        Location(int line, int col);
        ~Location(void);
    };
}
