/* ppcontext.hh
 *
 * Preprocessor context
 */

#ifndef PPCONTEXT_HH
#define PPCONTEXT_HH

#include <map>

namespace SFCC
{
    namespace Preprocessor
    {
        class PPContext
        {
            public:
                PPContext(std::string source);
                ~PPContext();

            private:
                std::map<std::string, std::string> identifiers;
        };
    }
}

#endif // PPCONTEXT_HH
