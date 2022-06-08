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
    public:
        Location(int line, int col);
        ~Location(void);
    };
}
