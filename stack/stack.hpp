#ifndef _STACK_HPP_
#define _STACK_HPP_
#include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
        typedef typename Container::value_type      Container_value_type;

        template<typename T1, typename Container1>
        friend bool
            operator==(const stack<T1, Container1>&, const stack<T1, Container1>&);

        template<typename T1, typename Container1>
        friend bool
            operator<(const stack<T1, Container1>&, const stack<T1, Container1>&);

    public:
        typedef typename Container::value_type      value_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;
        typedef typename Container::size_type       size_type;
        typedef          Container                  container_type;

    protected:
        Container c;
    
    public:
        explicit stack(const container_type& c = container_type())
            : c(c) {}

        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        reference top() { return c.back(); }
        const_reference top() const { return c.back(); }
        void push(const value_type& x) { c.push_back(x); }
        void pop() { c.pop_back(); }
    };
    /**
     *  @brief  Stack equality comparison.
     *  @param  x  A %stack.
     *  @param  y  A %stack of the same type as @a x.
     *  @return  True iff the size and elements of the stacks are equal.
     *
     *  This is an equivalence relation.  Complexity and semantics
     *  depend on the underlying sequence type, but the expected rules
     *  are: this relation is linear in the size of the sequences, and
     *  stacks are considered equivalent if their sequences compare
     *  equal.
     */
    template<typename T, typename Container>
    inline bool
        operator==(const stack<T, Container>& x, const stack<T, Container>& y)
    { return x.c == y.c; }

    /**
     *  @brief  Stack ordering relation.
     *  @param  x  A %stack.
     *  @param  y  A %stack of the same type as @a x.
     *  @return  True iff @a x is lexicographically less than @a y.
     *
     *  This is an total ordering relation.  Complexity and semantics
     *  depend on the underlying sequence type, but the expected rules
     *  are: this relation is linear in the size of the sequences, the
     *  elements must be comparable with @c <, and
     *  std::lexicographical_compare() is usually used to make the
     *  determination.
     */
    template<typename T, typename Container>
        inline bool
    operator<(const stack<T, Container>& x, const stack<T, Container>& y)
    { return x.c < y.c; }

    /// Based on operator==
    template<typename T, typename Container>
        inline bool
    operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
    { return !(x == y); }

    /// Based on operator<
    template<typename T, typename Container>
        inline bool
    operator>(const stack<T, Container>& x, const stack<T, Container>& y)
    { return y < x; }

     /// Based on operator<
    template<typename T, typename Container>
    inline bool
        operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
    { return !(y < x); }

    /// Based on operator<
    template<typename T, typename Container>
    inline bool
        operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
    { return !(x < y); }
}

#endif