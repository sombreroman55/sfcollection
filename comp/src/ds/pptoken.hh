/* pptoken.hh
 *
 * Pre-processor token class representation
 */

#ifndef PPTOKEN_HH
#define PPTOKEN_HH

#include <string>
#include <cstdint>

namespace SFCC
{
    namespace DataStructures
    {
        enum class PPTokenType : uint8_t
        {
            none,
            header_name,
            identifier,
            pp_number,
            character_constant,
            string_literal,
            punctuator
        };

        class PPToken
        {
            public:
                PPToken(std::string _lexeme, PPTokenType _type);
                ~PPToken();

            private:
                std::string lexeme;
                PPTokenType type;
        };
    }
}

#endif // PPTOKEN_HH
