#ifndef EZPZ_STREAM_ITERATORS_H
#define EZPZ_STREAM_ITERATORS_H

#include <ostream>
#include <istream>
#include <string>
#include <iterator>
#include <cstddef>
#include <ios>

#include "eat.h"

namespace ezpz
{
    template<typename ElemType, typename CharType = char,
           typename Traits = std::char_traits<CharType> >
    class ostream_iterator
    : public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
    public:
      typedef CharType                        char_type;
      typedef Traits                          traits_type;
      typedef std::basic_ostream<CharType, Traits> ostream_type;

    private:
      ostream_type*	    stream;
      const CharType*	string;
      bool              phase2;

    public:
      ostream_iterator(ostream_type& s, const CharType* c)
      : stream(&s), string(c), phase2(false)  { }

      ostream_iterator(ostream_type& s)
      : stream(&s), string(0), phase2(false)  { }

      ostream_iterator(const ostream_iterator& obj)
      : stream(obj.stream), string(obj.string), phase2(obj.phase2)  { }

      ostream_iterator&
      operator=(const ElemType& value)
      {
          if (phase2 && string)
              *stream << string;

          phase2 = true;

          *stream << value;
          return *this;
      }

      ostream_iterator&
      operator*()
      { return *this; }

      ostream_iterator&
      operator++()
      { return *this; }

      ostream_iterator&
      operator++(int)
      { return *this; }
    };

    template<typename ElemType, typename CharT = char,
             typename Traits = std::char_traits<CharT>, typename Dist = std::ptrdiff_t>
    class istream_iterator
      : public std::iterator<std::input_iterator_tag, ElemType, Dist, const ElemType*, const ElemType&>
    {
      public:
        typedef CharT                         char_type;
        typedef Traits                        traits_type;
        typedef std::basic_istream<CharT, Traits>  istream_type;

      private:
        istream_type*	stream;
        ElemType		value;
        const CharT*    string;
        bool		    ok;
        bool            phase2;

      public:
        istream_iterator()
        : stream(0), value(), string(0), ok(false), phase2(false) {}

        istream_iterator(istream_type& s)
        : stream(&s), string(0), phase2(false)
        { read(); }

        istream_iterator(istream_type& s, const CharT* what)
        : stream(&s), string(what), phase2(false)
        { read(); }

        istream_iterator(const istream_iterator& obj)
        : stream(obj.stream), value(obj.value), string(obj.string), 
          ok(obj.ok), phase2(obj.phase2)
        { }

        const ElemType& 
        operator*() const
        {
            return value;
        }

        const ElemType* 
        operator->() const { return &(operator*()); }

        istream_iterator&
        operator++()
        {
            read();
            return *this;
        }

        istream_iterator
        operator++(int)
        {
            istream_iterator tmp = *this;
            read();
            return tmp;
        }

        bool
        equal(const istream_iterator& x) const
            { return (ok == x.ok) && (!ok || stream == x.stream); }

      private:
        void
        read()
        {
            if (phase2 && string)
                *stream >> eat<CharT>(string);

            ok = (stream && *stream) ? true : false;
            if (ok)
            {
                *stream >> value;
                ok = *stream ? true : false;
                phase2 = true;
            }
        }
    };

    template<typename ElemType, typename CharT, typename Traits, typename Dist>
        inline bool
        operator==(const istream_iterator<ElemType, CharT, Traits, Dist>& x,
                   const istream_iterator<ElemType, CharT, Traits, Dist>& y)
        { return x.equal(y); }

    template <class ElemType, class CharT, class Traits, class Dist>
        inline bool
        operator!=(const istream_iterator<ElemType, CharT, Traits, Dist>& x,
                   const istream_iterator<ElemType, CharT, Traits, Dist>& y)
        { return !x.equal(y); }

} 

#endif // EZPZ_STREAM_ITERATORS_H
