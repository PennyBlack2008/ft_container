#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <memory>
#include "../include/iterator.hpp"
#include "../include/uninitialized.hpp"
#include "../include/functexcept.hpp"
#include "../include/algorithm.hpp"

namespace ft {
    /*-----------
     Vector_base
     reference: https://www.fatalerrors.org/a/vector-source-code-analysis.html
    ------------*/
    template<typename T, typename Alloc>
    struct Vector_Base {
        typedef typename Alloc::template rebind<T>::other T_alloc_type;

        /* Vector_impl 구조체는 container의 기초적인 3개의 멤버변수를 초기화해서 Vector에서 사용할 수 있도록 준비해놓는다. */
        struct Vector_impl : public T_alloc_type {
            T*      M_start; // 메모리의 시작점
            T*      M_finish; // 메모리의 마지막 원소의 주소(마지막 원소의 시작점 주소)
            T*      M_end_of_storage; // 메모리의 끝(미리 확보된 메모리 포함해서의 끝)

            Vector_impl() : T_alloc_type(), M_start(0), M_finish(0), M_end_of_storage(0) {}
            Vector_impl(T_alloc_type const& a) : T_alloc_type(a), M_start(0), M_finish(0), M_end_of_storage(0) {}
        };

        public:
            typedef Alloc allocator_type;
            
            /* get_allocator() */
            T_alloc_type& M_get_T_allocator() {
                return *static_cast<T_alloc_type*>(&this->M_impl);
            }

            const T_alloc_type& M_get_T_allocator() const {
                return *static_cast<const T_alloc_type*>(&this->M_impl);
            }

            allocator_type get_allocator() const {
                return allocator_type(M_get_T_allocator());
            }

            /* constructor */
            Vector_base() : M_impl() {}
            Vector_base(const allocator_type& a) : M_impl(a) {}
            Vector_base(size_t n, const allocator_type& a) : M_impl(a) {
                this->M_impl.M_start = this->M_allocate(n);
                this->M_impl.M_finish = this->M_impl.M_start;
                this->M_impl.M_end_of_storage = this->M_impl.M_start + n;
            }

            /* destructor */
            ~Vector_base() {
                M_deallocate(this->M_impl.M_start, this->M_impl.M_end_of_storage - this->M_impl.M_start);
            }
        
        public:
            Vector_impl M_impl;
           
            T* M_allocate(size_t n) {
                return M_impl.allocate(n);
            }
          
            void M_deallocate(T* p, size_t n) {
                if (p) M_impl.deallocate(p, n);
            }
    };

    // generic template
    /*-------------------
    * vector 클래스
    * T -> 벡터에 저장되는 요소 데이터 형식
    * Allocator -> 벡터의 메모리 할당 및 할당 취소에 대한 세부 정보를 캡슐화하는 할당자 개체(선택사항)
    --------------------*/
    template <class T, class Alloc = std::allocator<T> >
    class vector : protected Vector_base<T, Alloc>
    {
    private:
        typedef typename Alloc::value_type                Alloc_value_type;
        typedef Vector_base<T, Alloc>                     Base;
        typedef vector<T, Alloc>                          vector_type;
        typedef typename Base::T_alloc_type               T_alloc_type;
    public:
        typedef T                                               value_type;
        typedef typename T_alloc_type::pointer                  pointer;
        typedef typename T_alloc_type::const_pointer            const_pointer;
        typedef typename T_alloc_type::reference                reference;
        typedef typename T_alloc_type::const_reference          const_reference;
        typedef ft::normal_iterator<pointer, vector_type>       iterator;
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;
        typedef ft::normal_iterator<const_pointer, vector_type> const_iterator;
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
        typedef size_t                                          size_type;
        typedef ptrdiff_t                                       difference_type;
        typedef Alloc                                           allocator_type;
    protected:
        using Base::M_allocate;
        using Base::M_deallocate;
        using Base::M_impl;
        using Base::M_get_T_allocator;
    public:
        /* 
        * 생성자
        * - 모든 생성자는 할당자 개체()를 저장(allocator)하고 벡터를 초기화합니다.
        */
        vector() : Base() {}
        /* 빈 초기 벡터를 지정합니다. */
        explicit vector(const allocator_type& a) : Base(a) {}
        /* 빈 초기 벡터를 지정합니다. 사용할 할당자 형식(allocator)을 명시적으로 지정합니다. */
        explicit vector(size_type n, const value_type& value = value_type(),
                            const allocator_type& a = allocator_type()) : Base(n, a) {
            ft::uninitialized_fill_n_a(this->M_impl.M_start, n, value, M_get_T_allocator());
            this->M_impl.M_finish = this->M_impl.M_start + n;
        }
        /* x벡터의 복사본을 지정합니다. */
        vector(const vector& x) : Base(x.size(), x.M_get_T_allocator()) {
            this->M_impl.M_finish = ft::uninitialized_copy_a(x.begin(), x.end(),
                                            this->M_impl.M_start, M_get_T_allocator());
        }

        /* 벡터의 범위(first, last)를 복사합니다. */
        template<typename InputIterator>
        vector(InputIterator first, InputIterator last,
                    const allocator_type& a = allocator_type(),
                    typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
                        : Base(a)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category IterCategory;
            M_range_initialize(first, last, IterCategory);
        }
        
        ~vector() {
            ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish, M_get_T_allocator());
        }
        
        vector& operator=(const vector& x);

        iterator begin() {
            return iterator(this->M_impl.M_start);
        }

        const_iterator begin() const {
            return const_iterator(this->M_impl.M_start);
        }

        /* @end()는 실질적 마지막 값의 뒤에 있는 NULL 데이터의 시작점을 가리킨다. */
        iterator end() {
            return iterator(this->M_impl.M_finish);
        }

        const_iterator end const {
            return const_iterator(this->M_impl.M_finish);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return reverse_iterator(begin());
        }

        /* @size Return size */
        size_type size() const {
            return size_type(this->M_impl.M_finish - this->M_impl.M_start);
        }

        /* @max_size Return maximum size. system 또는 lib에 정의된 max size를 반환하지만, 그것이 반드시 allocate을 보장해주지 않음 */
        size_type max_size() const {
            return M_get_T_allocator().max_size();
        }

        /* @resize Change size */
        void resize(size_type new_size, value_type x = value_type()) {
            if (new_size < size())
                erase(this->M_impl.M_start + new_size, end());
            else
                insert(end(), new_size - size(), x);
        }

        /* @capacity Return size of allocated storage capacity. 현재 용량(size + 빈공간에 해당 타입이 들어갈 있는 갯수)을 반환 */
        size_type capacity() const {
            return size_type(this->M_impl.M_end_of_storage - this->M_impl.M_start);
        }

        /* @empty Test whether vector is empty */
        bool empty() const {
            return begin() == end();
        }
        
        /* @reserve Request a change in capacity */
        void reserve(size_type n) {
            /* 만약 capacity보다 n이 크면 n만큼의 capacity를 확보해놓는다. 이 경우 외에는 아무것도 하지 않는다. */
            if (this->capacity() < n) {
                const size_type old_size = size();
                pointer tmp = M_allocate_and_copy(n, this->M_impl.M_start, this->M_impl.M_finish);
                ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish, M_get_T_allocator());
                M_deallocate(this->M_impl.M_start, this->M_impl.M_end_of_storage - this->M_impl._M_start);
                this->M_impl.M_start = tmp;
                this->M_impl.M_finish = tmp + old_size;
                this->M_impl.M_end_of_storage = this->M_impl.M_start + n;
            }
        }

        /* @operator[] Access element 해당 컨테이너의 메모리 주소에서 n을 더해 그 주소의 시작점이 가리키는 값을 반환 */
        reference operator[](size_type n) {
            return *(this->M_impl._M_start + n);
        }

        const_reference operator[](size_type n) const {
            return *(this->M_impl.M_start + n);
        }

        /* @at Access element at은 []과 동일하나 너무 큰 값이 들어가면 예외를 던져준다. */
        reference at(size_type n) {
            if (n >= size())
                std::__throw_out_of_range("vector::range_check");
            return (*this)[n];
        }

        const_reference at(size_type n) const {
            if (n >= size())
                std::__throw_out_of_range("vector::range_check");
            return (*this)[n];
        }

        /* @front Access first element */
        reference front() {
            return *begin();
        }

        const_reference front() const {
            return *begin();
        }

        /* @back Access last element 
        * end()는 그 자체로 last element의 주소이다. 그런데 주소에다 -1을 하는 이유는,
        * 그래야 마지막 원소의 NULL값이 아닌 실질적으로 마지막 원소의 값을 참조할 수 있기 때문이다.
        */
        reference back() {
            return *(end() - 1);
        }

        const_reference back() const {
            return *(end() - 1);
        }
        
        pointer data() {
            return pointer(this->M_impl.M_start);
        }

        const_pointer data() const {
            return const_pointer(this->M_impl.M_start);
        }


        /* @assign Assign vector content */
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
            erase(begin(), end());
            insert(begin(), first, last);
        }

        void assign(size_type n, const value_type& value)
        {
            erase(begin(), end());
            insert(begin(), n, value);
        }

        /* @push_back Add element at the end */
        void push_back(const value_type& x) {
            /* 만약 vector 용량이 모두 차지 않았다면 if문을 실행, 아니면 else문 실행. */
            if (this->M_impl.M_finish != this->M_impl.M_end_of_storage) {
                this->M_impl.construct(this->M_impl.M_finish, x);
                ++this->M_impl.M_finish;
            }
            else {
                M_insert(end(), x);
            }
        }

        /* @pop_back Delete last element */
        void pop_back() {
            --this->M_impl.M_finish;
            this->M_impl.destroy(this->M_impl.M_finish);
        }

        /* @insert Insert elements */
        iterator insert(iterator position, const value_type& x) {
            const size_type n = position - begin();
            if (this->M_impl.M_finish != this->M_impl.M_end_of_storage && position == end()) {
                this->M_impl.construct(this->M_impl.M_finish, x);
                ++this->M_impl.M_finish;
            }
            else {
                M_insert(position, x);
                return iterator(this->M_impl.M_start + n);
            }
        }

        void insert(iterator position, size_type n, const value_type& x)
        {
            M_fill_insert(position, n, x);
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                        typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
            typedef typename iterator_traits<InputIterator>::iterator_category IterCategory;
            M_range_insert(position, first, last, IterCategory());
        }
        /* @erase Erase elements */
        iterator erase(iterator position) {
            if (position + 1 != end())
                /* position 자리에 새로운 position + 1 부터 end()까지의 메모리를 붙여준다 */
                ft::copy(position + 1, end(), position);
                --this->M_impl.M_finish; // 메모리가 1자리 앞당겨지므로 감소
                this->M_impl.destroy(this->M_impl._M_finish); // 마지막 자리 deallocate
                return position;
        }

        iterator erase(iterator first, iterator last) {
            iterator it(ft::copy(last, end(), first));
            M_destroy(it, end());
            this->M_finish = this->M_finish - (last - first);
            return first;
        }

        /* @swap Swap content vector container의 내용물을 서로 바꾼다. */
        void swap(vector& x) {
            std::swap(this->M_impl.M_start, x.M_impl.M_start);
            std::swap(this->M_impl.M_finish, x.M_impl.M_finish);
            std::swap(this->M_impl.M_end_of_storage, x.M_impl.M_end_of_storage);
            __swap_allocator(this->M_get_T_allocator(), x.M_get_T_allocator());
        }

        /* @clear Clear content vector 다 지운다 */
        void clear() {
            erase(begin(), end());
        }

        /* @get_allocator Get allocator*/

        /* @relational operators */

        /* @vector<bool> */

    protected:
        void M_destroy(value_type* first, value_type* last)
        {
            for (; first != last; ++first)
                this->M_alloc.destroy(first);
        }

        template<typename ForwardIterator>
        pointer M_allocate_and_copy(size_type n, ForwardIterator first, ForwardIterator last) {
            pointer result = this->M_allocate(n); // n만큼의 요소가 들어가도록 아직 초기화되지 않은 메모리를 확보해놓는다.
            try {
                /* @uninitialized_copy_a
                * 초기화되지 않은 메모리에 [first, last)를 result에 복사한다.
                *  만약 메모리할당에 실패했을 경우, exception을 내보낸다.
                * */
                ft::uninitialized_copy_a(first, last, result, M_get_T_allocator());
                return result;
            } catch(...) {
                M_deallocate(result, n);
                throw;
            }
        }
        
        template <typename InputIterator>
        void M_range_initialize(InputIterator first, InputIterator last, input_iterator_tag)
        {
            for (; first != last; ++first)
                push_back(*first);
        }
        
        template <typename ForwardIterator>
        void M_range_initialize(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            size_type n = distance(first, last);
            this->M_start = this->M_allocate(n);
            this->M_end_of_storage = this->M_start + n;
            this->M_finish = uninitialized_copy(first, last, this->M_start);
        }

        void M_insert(iterator position, const value_type& x)
        {
            if (this->M_finish != this->M_end_of_storage)
            {
                this->M_alloc.construct(this->M_finish, *(this->M_finish - 1));
                ++this->M_finish;
                value_type x_copy x;
                std::copy_backward(position, iterator(this->M_finish - 2), iterator(this->M_finish - 1));
                *position = x_copy;
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size != 0 ? 2 * old_size : 1;
                iterator new_start(this->M_allocate(len));
                iterator new_finish(new_start);
                try
                {
                    new_finish = std::uninitialized_copy(iterator(this->M_start), position, new_start);
                    this->M_alloc.construct(new_finish, x);
                    ++new_finish;
                    new_finish = std::uninitialized_copy(position, iterator(this->M_finish), new_finish);
                }
                catch(...)
                {
                    M_destroy(new_start, new_finish);
                    this->M_deallocate(new_start, len);
                    throw;
                }
                M_destroy(begin(), end());
                this->M_deallocate(this->M_start, this->M_end_of_storage - this->M_start);
                this->M_start = new_start;
                this->M_finish = new_finish;
                this->M_end_of_storage = new_start + len;
            }
        }

        template<typename T, typename Alloc>
        void vector<T, Alloc>::M_fill_insert(iterator position, size_type n, const value_type& x)
        {
            if (n != 0)
            {
                if (size_type(this->M_impl.M_end_of_storage - this->M_impl.M_finish) >= n)
                {
                    value_type x_copy = x;
                    const size_type elems_after = end() - position;
                    iterator old_finish(this->M_impl.M_finish);
                    if (elems_after > n)
                    {
                        std::uninitialized_copy(this->M_impl.M_finish - n, this->M_impl.M_finish, this->M_impl.M_finish);
                        this->M_impl.M_finish += n;
                        std::copy_backward(position.base(), old_finish - n, old_finish);
                        std::fill(position.base(), position.base() + n, x_copy);
                    }
                    else
                    {
                        ft::uninitialized_fill_n(this->M_impl.M_finish, n - elems_after, x_copy);
                        this->M_impl.M_finish += n - elems_after;
                        std::uninitialized_copy(position, old_finish, this->M_impl.M_finish);
                        this->M_impl.M_finish += elems_after;
                        std::fill(position, old_finish, x_copy);
                    }
                }
                else
                {
                    const size_type old_size = size();
                    const size_type len = old_size + std::max(old_size, n);
                    iterator new_start(this->M_allocate(len));
                    iterator new_finish(new_start);
                    try
                    {
                        new_finish = std::uninitialized_copy(begin(), position, new_start);
                        new_finish = ft::uninitialized_fill_n(new_finish, n, x);
                        new_finish = std::uninitialized_copy(position, end(), new_finish);
                    }
                    catch (...)
                    {
                        M_destroy(new_start, new_finish);
                        this->M_deallocate(new_start, len);
                        throw;
                    }
                    M_destroy(this->M_impl.M_start, this->M_impl.M_finish);
                    this->M_deallocate(this->M_impl.M_start, this->M_impl.M_end_of_storage - this->M_impl.M_start);
                    this->M_impl.M_start = new_start;
                    this->M_impl.M_finish = new_finish;
                    this->M_impl.M_end_of_storage = new_start + len;
                }
            }
        }

        template<typename T, typename Alloc> template <typename InputIterator>
        void vector<T, Alloc>::M_range_insert(iterator position, InputIterator first, InputIterator last, input_iterator_tag)
        {
            for (; first != last; ++first)
            {
                position = insert(position, *first);
                ++position;
            }
        }

        template<typename T, typename Alloc>
        template <typename ForwardIterator>
        void vector<T, Alloc>::M_range_insert(iterator position, ForwardIterator first, ForwardIterator last, forward_iterator_tag)
        {
            if (first != last)
            {
                size_type n = distance(first, last);
                if (size_type(this->M_impl.M_end_of_storage - this->M_impl.M_finish) >= n)
                {
                    const size_type elems_after = end() - position;
                    iterator old_finish(this->finish);
                    if (elems_after > n)
                    {
                        std::uninitialized_copy(this->M_impl.M_finish - n, this->M_impl.M_finish, this->M_impl.M_finish);
                        this-M_impl.>M_finish += n;
                        std::copy_backward(position, old_finish - n, old_finish);
                        ft::copy(first, last, position);
                    }
                    else
                    {
                        ForwardIterator mid = first;
                        advance(mid, elems_after);
                        std::uninitialized_copy(mid, last, this->M_impl.M_finish);
                        this->M_impl.M_finish += n - elems_after;
                        std::uninitialized_copy(position, old_finish, this->M_impl.M_finish);
                        this->M_impl.M_finish += elems_after;
                        copy(first, mid, position);
                    }
                }
                else
                {
                    const size_type old_size = size();
                    const size_type len = old_size + std::max(old_size, n);
                    iterator new_start(this->M_allocate(len));
                    iterator new_finish(new_start);
                    try
                    {
                        new_finish = std::uninitialized_copy(iterator(this->M_impl.M_start), position, new_start);
                        new_finish = std::uninitialized_copy(first, last, new_finish);
                        new_finish = std::uninitialized_copy(position, iterator(this->M_impl.M_finish), new_finish);
                    }
                    catch(...)
                    {
                        M_destroy(new_start, new_finish);
                        this->M_deallocate(new_start, len);
                        throw;
                    }
                    M_destroy(this->M_impl.M_start, this->M_impl.M_finish);
                    this->M_deallocate(this->M_impl.M_start, this->M_impl.M_end_of_storage - this->M_impl.M_start);
                    this->M_impl.M_start = new_start;
                    this->M_impl.M_finish = new_finish;
                    this->M_impl.M_end_of_storage = new_start + len;
                }
            }
        }
    };
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
    {
     return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
    }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
    {
      return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
    {
       return !(x == y);
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
    {
      return y < x;
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
    {
      return !(x < y);
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& x, const vector<T, Alloc>& y)
    {
      return !(y < x);
    }

    // specialized algorithms:
    template <class T, class Alloc>
    void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
    {
      x.swap(y);
    }
}

#endif