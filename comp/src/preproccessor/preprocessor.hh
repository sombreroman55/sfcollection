/* preprocessor.hh
 *
 * Preprocessor module
 */

#ifndef PREPROCESSOR_HH
#define PREPROCESSOR_HH

namespace SFCC
{
    namespace Preprocessor
    {
        class Preprocessor
        {
            public:
                Preprocessor(std::string source);
                ~Preprocessor();

            private:
                PPContext _context;
        };
    }
}

#endif // PREPROCESSOR_HH
