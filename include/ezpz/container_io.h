#ifndef EZPZ_PRINT_CONTAINER_H
#define EZPZ_PRINT_CONTAINER_H

#include <type_traits>
#include <typeinfo>
#include "stream_iterators.h"

namespace ezpz 
{
    template <typename Stream,
              typename Container,
              typename CharT = typename Stream::char_type
             >
    Stream& print_container (Stream& s,
                             const Container& cont,
                             const CharT* start,
                             const CharT* end,
                             const CharT* separator)
    {
        using ValueTRef = decltype(*::std::begin(cont));
        using ValueT = typename ::std::remove_reference<ValueTRef>::type;

        s << start;
        ::ezpz::ostream_iterator<ValueT, CharT> it(s, separator);
        ::std::copy (::std::begin(cont), ::std::end(cont), it);
        s << end;
        return s;
    }

    template <typename Stream,
              typename Container,
              typename CharT = typename Stream::char_type
             >
    Stream& operator<< (Stream& s, const Container& cont)
    {
        static const CharT start[] = { '[', 0 };
        static const CharT end[] = { ']', 0 };
        static const CharT separator[] = { ',', ' ', 0 };
        return print_container(s, cont, start, end, separator);
    }

    template <typename Stream,
              typename Container,
              typename CharT = typename Stream::char_type
             >
    Stream& read_container (Stream& s,
                            Container& cont,
                            const CharT* start,
                            const CharT* end,
                            const CharT* separator)
    {
        using ValueTRef = decltype(*::std::begin(cont));
        using ValueT = typename ::std::remove_reference<ValueTRef>::type;

        {
            eat<CharT> es(start);
            ezpz::operator>> (s, es);
        }
        if (!s) return s;
        ::ezpz::istream_iterator<ValueT, CharT> stream_start(s, separator), stream_end;
        ::std::copy(stream_start, stream_end, ::std::back_inserter(cont));
        {
            s.clear();
            eat<CharT> ee(end);
            ezpz::operator>> (s, ee);
        }
        return s;
    }

    template <typename Container, 
              typename Stream,
              typename CharT = typename Stream::char_type
             >
    Stream& operator>> (Stream& s, Container& cont)
    {
        static const CharT start[] = { '[', 0 };
        static const CharT end[] = { ']', 0 };
        static const CharT separator[] = { ',', 0 };
        return read_container(s, cont, start, end, separator);
    }
}

#endif // EZPZ_PRINT_CONTAINER_H
