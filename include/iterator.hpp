#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <cstddef>
#include <iterator>
#include "../include/type_traits.hpp"
#include "../include/cpp_type_traits.hpp"

namespace ft {
	/*-------------
	iterator_traits
	-------------*/
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type					value_type;
		typedef typename Iterator::pointer						pointer;
		typedef typename Iterator::reference					reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t							difference_type;
		typedef T											value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t							difference_type;
		typedef T											value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	/*---------------
	reverse_iterator
	---------------*/
	template <class Iterator>
	class reverse_iterator :
		public std::iterator<typename iterator_traits<Iterator>::iterator_category,
												 typename iterator_traits<Iterator>::value_type,
												 typename iterator_traits<Iterator>::difference_type,
												 typename iterator_traits<Iterator>::pointer,
												 typename iterator_traits<Iterator>::reference>
		{
		protected:
			/* current는 해당 컨테이너의 정방향 iterator에서 받은 값 그대로의 base()상태 */
			Iterator M_current;
		public:
			/* @iterator_type reverse_iterator의 기본 반복기를 제공하는 형식 */
			typedef Iterator										                      		iterator_type;
			/* @difference_type 동일한 컨테이너 안에서 요소를 참조하는 두 reverse_iterator 사이의 차이를 제공하는 형식 */
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			/* @reference reverse_iterator로 주소를 지정하는 요소에 참조를 제공하는 형식*/
			typedef typename iterator_traits<Iterator>::reference		    	reference;
			/* @pointer reverse_iterator로 주소를 지정하는 요소에 포인터를 제공하는 형식 */
			typedef typename iterator_traits<Iterator>::pointer			    	pointer;

			reverse_iterator() : M_current() {}
			explicit reverse_iterator(Iterator x) : M_current(x) {}
			reverse_iterator(const reverse_iterator& x) : M_current(x.M_current) {}
			
			template <class Iter> // NOTE: 왜 그냥 Iter일까?
			reverse_iterator(const reverse_iterator<Iter>& x) : M_current(x.base()) {}
			
			template <class Iter>
			reverse_iterator&
				operator=(const reverse_iterator<Iter>& x)
			{
				M_current = x.base();
				return *this;
			}
			/* @base reverse_iterator에서 기본 반복기를 복구합니다. */
			iterator_type
				base() const
			{
				return M_current;
			}
			
			/* @operator* reverse_iterator가 주소를 지정하는 요소를 반환합니다.
			--를 하는 이유는 reverse_iterator의 until은 정방향 from -1의 위치와 같다
			(정방향과 다르게 NULL로 시작해서 끝값으로 끝난다) 그 반대로 reverse_iterator의 from은 정방향 until -1의 위치와 같다.
			*/
			reference
				operator*() const
			{
				iterator_type	temp = M_current;
				return *--temp;
			}
			/* @operator-> reverse_iterator가 주소 지정하는 요소로 포인터를 반환합니다. */
			pointer
				operator->() const
			{
				return &(operator*());
			}
			/* @&operator++ reverse_iterator를 이전 요소로 증가시킵니다. */
			reverse_iterator&	operator++() {
				--M_current;
				return *this;
			}
			/* @operator++ reverse_iterator를 이전 요소로 증가시킵니다. */
			reverse_iterator	operator++(int) {
				reverse_iterator	temp(*this);
				--M_current;
				return temp;
			}
			/* @&operator-- reverse_iterator를 이전 요소로 감소시킵니다. */
			reverse_iterator&	operator--() {
				++M_current;
				return *this;
			}
			/* @operator-- reverse_iterator를 이전 요소로 감소시킵니다. */
			reverse_iterator	operator--(int) {
				reverse_iterator	temp(*this);
				++M_current;
				return temp;
			}
			/* @operator+ 반복기에 오프셋을 추가하고 새 오프셋 위치에서 삽입된 요소를 주소 지정하는 새 reverse_iterator
							를 반환합니다.*/
			reverse_iterator	operator+ (difference_type n) const {
				return reverse_iterator(M_current - n);
			}
			/* @opreator+= reverse_iterator에서 지정된 오프셋을 추가합니다. */
			reverse_iterator&	operator+=(difference_type n) {
				M_current -= n;
				return *this;
			}
			/* @operator- reverse_iterator에서 오프셋을 차감하고 오프셋 위치에서 요소를 주소지정하는 reverse_iterator를 반환 */
			reverse_iterator	operator- (difference_type n) const {
				return reverse_iterator(M_current + n);
			}
			/* @operator-= reverse_iterator에서 지정된 오프셋을 차감합니다. */
			reverse_iterator&	operator-=(difference_type n) {
				M_current += n;
				return *this;
			}
			/* @operator[] reverse_iterator에서 주소 지정하는 요소의 요소 오프셋으로 지정된 위치 수 만큼 참조를 반환 */
			reference			operator[](difference_type n) const {
				return *(*this + n);
			}
		};

	/**
	 *  @param  x  A %reverse_iterator.
	 *  @param  y  A %reverse_iterator.
	 *  @return  A simple bool.
	 *
	 *  Reverse iterators forward many operations to their underlying base()
	 *  iterators.  Others are implemented in terms of one another.
	 *  inline 함수로 만든 것은 함수 자체가 짧아 inline으로 하여 속도 빠르게, 디버그 쉽게
	 *
	 */
 	 template<typename Iterator>
    inline bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return x.base() == y.base();
	}
	/* <의 명령문의 결과가 x < y가 아니라 x > y 인 이유는 reverse 관점에서 결과를 도출해야하기 때문이다. 정방향에서 더 클수록
  		reverse 관점에서 더 작다는 뜻이다. base 함수는 정방향인 current 멤버 변수를 그대로 가져오기 때문이다. */
  	template<typename Iterator>
    inline bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return y.base() < x.base();
	}

  	template<typename Iterator>
    inline bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}

  /* 이 경우에는 base()가 아닌 current를 reverse대로 이미 계산되어 나온 결과와의 비교이기 때문에 그대로 y < x 로 비교해도 된다. */
	template<typename Iterator>
    inline bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return y < x;
	}

	template<typename Iterator>
    inline bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(y < x);
	}

  	template<typename Iterator>
  	inline bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x < y);
	}

  	template<typename Iterator>
    inline typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return y.base() - x.base();
	}

  	template<typename Iterator>
    inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return reverse_iterator<Iterator>(x.base() - n);
	}

  	// _GLIBCXX_RESOLVE_LIB_DEFECTS
  	// DR 280. Comparison of reverse_iterator to const reverse_iterator.
  	template<typename IteratorL, typename IteratorR>
    inline bool operator==(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return x.base() == y.base();
	}

 	/* <의 명령문의 결과가 x < y가 아니라 x > y 인 이유는 reverse 관점에서 결과를 도출해야하기 때문이다. 정방향에서 더 클수록
	reverse 관점에서 더 작다는 뜻이다. base 함수는 정방향인 current 멤버 변수를 그대로 가져오기 때문이다. */
  	template<typename IteratorL, typename IteratorR>
    inline bool operator<(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return y.base() < x.base();
	}

  	template<typename IteratorL, typename IteratorR>
    inline bool operator!=(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return !(x.base() == y.base());
	}

  	template<typename IteratorL, typename IteratorR>
    inline bool operator>(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return y < x;
	}

  	template<typename IteratorL, typename IteratorR>
    inline bool operator<=(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return !(y < x);
	}

  	template<typename IteratorL, typename IteratorR>
    inline bool operator>=(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return !(x < y);
	}

  	template<typename IteratorL, typename IteratorR>
		inline typename reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) {
		return y.base() - x.base();
	}

	using ft::iterator_traits;

	template <class Iterator, class Container>
	class normal_iterator {
		protected:
			Iterator	M_current;
		public:
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::reference		   	reference;
			typedef typename iterator_traits<Iterator>::pointer			   	pointer;

			normal_iterator() : M_current(Iterator()) { }
			explicit normal_iterator(const Iterator& i) : M_current(i) { }

			// Allow iterator to const_iterator conversion SFINAE를 이용
			template <class Iter>
				normal_iterator(const normal_iterator<Iter,
					                typename enable_if<(ft::are_same<Iter, typename Container::pointer>::value),
					                                      Container>::type>& i)
				: M_current(i.base()) { }

			reference
				operator*() const
			{
				return *M_current;
			}

			pointer
				operator->() const
			{
				return M_current;
			}

			normal_iterator&
				operator++()
			{
				++M_current;
				return *this;
			}

			normal_iterator
				operator++(int)
			{
				return normal_iterator(M_current++);
			}

			normal_iterator&
				operator--()
			{
				--M_current;
				return *this;
			}

			normal_iterator
				operator--(int)
			{
				return normal_iterator(M_current--);
			}

			reference
				operator[](const difference_type& n) const
			{
				return M_current[n];
			}

			normal_iterator&
				operator+=(const difference_type& n)
			{
				M_current += n;
				return *this;
			}

			normal_iterator
				operator+(const difference_type& n) const
			{
				return normal_iterator(M_current + n);
			}

			normal_iterator&
				operator-=(const difference_type& n)
			{
				M_current -= n;
				return *this;
			}

			normal_iterator
				operator-(const difference_type& n) const
			{
				return normal_iterator(M_current - n);
			}

			const Iterator&
				base() const
			{
				return M_current;
			}
	};

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool operator==(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<typename Iterator, typename Container>
	inline bool operator==(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() == rhs.base();
	}

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool operator!=(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<typename Iterator, typename Container>
	inline bool operator!=(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() != rhs.base();
	}

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool operator<(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<typename Iterator, typename Container>
	inline bool operator<(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() < rhs.base();
	}

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool operator>(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<typename Iterator, typename Container>
	inline bool operator>(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() > rhs.base();
	}

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool operator<=(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<typename Iterator, typename Container>
	inline bool operator<=(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template<typename IteratorL, typename IteratorR, typename Container>
	inline bool operator>=(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<typename Iterator, typename Container>
	inline bool operator>=(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template<typename IteratorL, typename IteratorR, typename Container>
	inline typename normal_iterator<IteratorL, Container>::difference_type
	operator-(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs) {
		return lhs.base() - rhs.base();
	}

	template<typename Iterator, typename Container>
	inline typename normal_iterator<Iterator, Container>::difference_type
	operator-(const normal_iterator<Iterator, Container>& lhs, const normal_iterator<Iterator, Container>& rhs) {
		return lhs.base() - rhs.base();
	}

	template<typename Iterator, typename Container>
	inline normal_iterator<Iterator, Container>
	operator+(typename normal_iterator<Iterator, Container>::difference_type n, const normal_iterator<Iterator, Container>& i) {
		return normal_iterator<Iterator, Container>(i.base() + n);
	}
}

#endif