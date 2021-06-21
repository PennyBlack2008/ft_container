// https://github.com/rchallie/ft_containers/blob/4a13b644a2d537328ab25b6a11050ef0a63d5774/vector.hpp

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        /*
        ** The first template parameter (T)
        */
        typedef T       value_type;
        
        /*
        ** The second template parameter (Alloc)
        */
        typedef Alloc   allocator_type;

        /*
        ** allocator_type::reference
        ** A type provides a reference to an element stored in
        ** a vector.
        ** For the default allocator is a reference to value_type
        ** (value_type&)
        */
        typedef typename allocator_type::reference      reference;

        /*
        ** allocator_type::const_reference
        ** Type that give a reference to a const element stored.
        ** Useful to read and perform const operator.
        ** A type const_reference can't be used to modify the value
        ** of an element.
        ** For the default allocator is a const reference to value_type
        ** (const value_type&)
        */
        typedef typename allocator_type::const_reference    const_reference;

        /*
        ** allocator_type::const
        **
        **
        **
        **
        **
        **/


        vector();
        vector(const vector&);
        virtual ~vector();
        vector& operator=(const vector& op);

    };
}
#endif