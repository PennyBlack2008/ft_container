#ifndef _STACK_HPP_
#define _STACK_HPP_
#include "vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef Container container_type;

    protected:
        container_type c;
    
    public:
        explicit stack(const container_type& c = container_type())
            : c(c) {}

        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        value_type& top() { return c.back(); }
        const value_type& top() const { return c.back(); }
        void push(const value_type& x) { c.push_back(x); }
        void pop() { c.pop_back(); }
    
    private:
        template <typename T, typename Container>
        friend bool operator==(const stack<T, Container>&, const stack<T, Container>&);

        template <typename T, typename Container>
        friend bool operator<(const stack<T, Container>&, const stack<T, Container>&);
    };

    template <class T, 
}

#endif