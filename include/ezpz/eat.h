#ifndef EZPZ_EAT_H
#define EZPZ_EAT_H

#include <istream>
#include <string>
#include <ios>

namespace ezpz
{
    namespace detail
    {
        template<typename Stream,
                 typename CharT = typename Stream::char_type>
        Stream& skip_known (Stream& s, const CharT* what)
        {
            s >> std::ws;
            while (*what)
            {
                typename Stream::int_type c = s.peek();
                if (c == *what)
                {
                    ++what;
                    s.get();
                }
                else
                {
                    s.setstate(std::ios::failbit);
                    return s;
                }
            }
            return s;
        }
    }

    template <typename CharT>
    struct eat
    {
        eat(const CharT* s) : string(s) {}
        const CharT* const string;
    };

    template <typename Stream,
              typename CharT = typename Stream::char_type>
    Stream& operator>> (Stream& stream, const eat<CharT>& e)
    {
        return detail::skip_known(stream, e.string);
    }
}

#endif // EZPZ_EAT_H
