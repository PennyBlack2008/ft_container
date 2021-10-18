#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "../include/iterator.hpp"
#include "../include/uninitialized.hpp"
#include "../include/functexcept.hpp"
#include "../include/algorithm.hpp"

namespace ft {
    /*-----------
     Vector_base
    ------------*/
    template<typename T, typename Alloc>
    struct Vector_Base {
        typedef typename Alloc::template rebind<T>::other T_alloc_type;

        struct Vector_impl : public T_alloc_type {
            T*      M_start;
            T*      M_finish;
            T*      M_end_of_storage;

            Vector_impl(): T_alloc_type(), M_start(0), M_finish(0), M_end_of_storage(0) {}
            Vector_impl(T_alloc_type const& a): T_alloc_type(a), M_start(0), M_finish(0), M_end_of_storage(0) {}
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
    class vector : protected Vector_base<T, Alloc> {
        private:
            typedef typename Alloc                            Alloc_value_type;
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
				ft::uninitialized_fill_n_a(this->M_impl.M_start, n, value, M_get_Tp_allocator());
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
                        const allocator_type& a = allocator_type()) : Base(a) {
                typedef typename ft::is_integer<InputIterator>::type Integral;
                M_initialize_dispatch(first, last, Integral());
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
                    M_erase_at_end(this->M_impl.M_start + new_size);
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

            /* @operator[] Access element */

            /* @at Access element */

            /* @front Access first element */

            /* @back Access last element */

            /* @assign Assign vector content */

            /* @push_back Add element at the end */

            /* @pop_back Delete last element */

            /* @insert Insert elements */

            /* @erase Erase elements */
            
            /* @swap Swap content */

            /* @clear Clear content */

            /* @get_allocator Get allocator*/

            /* @relational operators */

            /* @swap */

            /* @vector<bool> */
    };

}

#endif