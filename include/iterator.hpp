#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <cstddef>
#include <type_traits>
#include "../include/type_traits.hpp"
#include "../include/cpp_type_traits.hpp"

namespace ft {
	/*-----------
	iterator_tags
	------------*/
	class input_iterator_tag {};
	class output_iterator_tag {};
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	/*-------
	iterator
	-------*/
	template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
		class Iterator {
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
		};

	/*-------------
	iterator_traits
	-------------*/
	template <class Iterator>
		struct iterator_traits {
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterartor_category	iterator_category;
		};

	template <class T>
		struct iterator_traits<T*> {
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef random_access_iterator_tag	iterator_category;
		};

	template <class T>
		struct iterator_traits<const T*> {
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef const T*					pointer;
			typedef const T&					reference;
			typedef random_access_iterator_tag	iterator_category;
		};

	template <class T>
    struct iterator_traits<const T*> {
      typedef ptrdiff_t					difference_type;
  		typedef T							value_type;
  		typedef const T*					pointer;
  		typedef const T&					reference;
  		typedef random_access_iterator_tag	iterator_category;
    };

	template <class InputIterator>
	void __advance(InputIterator& i, typename iterator_traits<InputIterator>::difference_type n, input_iterator_tag) {
		for (;n>0;--n)
			++i;
	};

	template<class BidirIterator>
	void __advance(BidirIterator& i, typename iterator_traits<BidirIterator>::difference_type n, bidirectional_iterator_tag) {
		if (n >= 0)
			for (;n>0;--n)
				++i;
		else
			for (;n<0;++n)
				--i;
	}

	template <class RandIterator>
	void __advance(RandIterator& i, typename iterator_traits<RandIterator>::difference_type n, random_access_iterator_tag) {
		i += n;
	};

	template <class InputIterator>
	void advance(InputIterator& i, typename iterator_traits<InputIterator>::difference_type n) {
		// 양방향 반복자가 아닌 케이스가 존재할때를 위해서 n>=0인 조건과 반복자의 타입에 대한 비교가 필요하나 현 서브젝트에선 다 양방향 반복자 이상이라 구현 X
		__advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
	}

	/*-------
	distance
	-------*/
	template <class InputIterator>
		typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, input_iterator_tag) {
			typename iterator_traits<InputIterator>::difference_type r(0);
			for (;first!=last;++first)
				++r;
			return r;
		}

	template <class InputIterator>
		typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, random_access_iterator_tag) {
			return last - first;
		}

	template<class InputIterator>
		typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
			return __distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
		}

	/*-----------------------------------------------------------
	back_inserter
	usage: push_back 함수를 포함하고 있는 vector, deque, list에서 사용. 항상 컨테이너로 초기화해야함
	description: 반복기 어댑터는 요소를 덮어쓰는 것이 아니라, 시퀀스 끝 부분에 요소를 삽입
	link: https://docs.microsoft.com/ko-kr/cpp/standard-library/back-insert-iterator-class?view=msvc-160
	------------------------------------------------------------*/
	template <class Container>
		class back_insert_iterator :
			public Iterator<output_iterator_tag, void, void, void, void>
		{
			protected:
				/* back_insert_iterator가 뒤에 요소를 삽입할 컨테이너의 형식입니다. */
				Container* container;
			public:
				/* back_insert_iterator에 대한 컨테이너를 제공하는 형식입니다. */
				typedef Container container_type;
				/* @back_insert_iterator 컨테이너의 마지막 요소 다음에 요소를 삽입합니다. */
				explicit back_insert_iterator (Container& x) : container(&x) { }
				/* @&operator= 컨테이너의 백 엔드에 값을 추가하거나 푸시합니다. */
				back_insert_iterator<Container>& operator= (typename Container::const_reference value) {
					container->push_back(value);
					return *this;
				}
				/* @&operator* 출력 반복기 식 i x를 구현하는 데 사용되는 Dereferencing 연산자 */
				back_insert_iterator<Container>& operator* () {
					return *this;
				}
				/* @&operator++ 값을 저장할 다음 위치에 back_insert_iterator를 증가 */
				back_insert_iterator<Container>& operator++ () {
					return *this;
				}
				/* @operator++ 값을 저장할 다음 위치에 back_insert_iterator를 증가 */
				back_insert_iterator<Container> operator++ (int) {
					return *this;
				}
		};

	template <class Container>
		back_insert_iterator<Container> back_inserter(Container& x) {
			return back_insert_iterator<Container>(x);
		}

	/*----------------------------------------------------
	front_inserter
	usage: push_front가 있는 deque, list에서 사용, 항상 컨테이너를 사용하여 초기화해야함
	description: 요소를 덮어쓰는 것이 아니라, 시퀀스 앞 부분에 요소를 삽입
	link: https://docs.microsoft.com/ko-kr/cpp/standard-library/front-insert-iterator-class?view=msvc-160
	-----------------------------------------------------*/

	template <class Container>
		class front_insert_iterator:
			public Iterator<output_iterator_tag, void, void, void, void>
		{
		protected:
			/* front_inser_iterator가 앞에 요소를 삽입할 컨테이너의 형식입니다. */
			Container* container;
		public:
			/* @container_type 전면 삽입 대상인 컨테이너를 나타내는 형식입니다. */
			typedef Container container_type;
			/* @front_insert_iterator 지정된 컨테이너 개체 앞에 요소를 삽입할 수 있는 반복기를 만듭니다. */
			explicit front_insert_iterator(Container& x) : container(&x) { }
			/* @&operator= 컨테이너의 앞에 값을 추가(푸시)합니다. */
			front_insert_iterator<Container>& operator= (typename Container::const_reference value) {
				container->push_front(value);
				return *this;
			}
			/* @&operator* 주소가 지정된 요소를 반환하는 삽입 반복기를 역참조합니다. */
			front_insert_iterator<Container>& operator* () {
				return *this;
			}
			/* @&operator++ 값을 저장할 다음 위치에 back_insert_iterator를 증가시킵니다. */
			front_insert_iterator<Container>& operator++ () {
				return *this;
			}
			/* @operator++ 값을 저장할 다음 위치에 back_insert_iterator를 증가시킵니다. */
			front_insert_iterator<Container> operator++ (int) {
				return *this;
			}
		};

	template <class Container>
		front_insert_iterator<Container> front_inserter(Container& x) {
			return front_insert_iterator<Container>(x);
		}

	/*--------------
	insert_iterator
	---------------*/
	template <class Container>
		class insert_iterator :
			public Iterator<output_iterator_tag, void, void, void, void>
		{
		protected:
			Container* container;
			typename Container::iterator iter;
		public:
			/* @container_type 일반 삽입 대상인 컨테이너를 나타내는 형식입니다. */
			typedef Container container_type;
			/* @insert_iterator 컨테이너의 지정된 위치에 요소를 삽입하는 insert_iterator를 만듭니다. */
			explicit insert_iterator(Container& x, typename Container::iterator i) : container(&x), iter(i) {}
			/* @operator= 컨테이너에 값을 삽입하고 새 요소를 가리키도록 업데이트된 반복기를 반환합니다. */
			insert_iterator<Container>& operator= (typename Container::const_reference value) {
				iter = container->insert(iter, value);
				++iter;
				return *this;
			}
			/* @&opertator* 주소가 지정된 요소를 반환하는 삽입 반복기를 역참조합니다. */
			insert_iterator<Container>& operator* () {
				return *this;
			}
			/* @&operator++ 값을 저장할 다음 위치에 insert_iterator를 증가시킵니다. */
			insert_iterator<Container>& operator++ () {
				return *this;
			}
			/* @&operator++ (int) 값을 저장할 다음 위치에 insert_iterator를 증가시킵니다. */
			insert_iterator<Container>& operator++ (int) {
				return *this;
			}
		};

	template <class Container, class Iterator>
		inline insert_iterator<Container> inserter(Container& x, Iterator i) {
			return insert_iterator<Container>(x, typename Container::iterator(i));
		}

	/*---------------
	reverse_iterator
	---------------*/
	template <class Iterator>
		class reverse_iterator :
			public Iterator<typename iterator_traits<Iterator>::iterator_category,
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
			reverse_iterator& operator=(const reverse_iterator<Iter>& x) {
				M_current = x.base();
				return *this;
			}
			/* @base reverse_iterator에서 기본 반복기를 복구합니다. */
			iterator_type		base() const {
				return M_current;
			}
			/* @operator* reverse_iterator가 주소를 지정하는 요소를 반환합니다.
			--를 하는 이유는 reverse_iterator의 until은 정방향 from -1의 위치와 같다
			(정방향과 다르게 NULL로 시작해서 끝값으로 끝난다) 그 반대로 reverse_iterator의 from은 정방향 until -1의 위치와 같다.
			*/
			reference			operator*() const {
				iterator_type	temp = M_current;
				return *--temp;
			}
			/* @operator-> reverse_iterator가 주소 지정하는 요소로 포인터를 반환합니다. */
			pointer				operator->() const {
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
		return !(x == y);
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
	using ft::Iterator;

	template <class Iterator, class Container>
	class normal_iterator {
		protected:
			Iterator	M_current;
		public:
			typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			  value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::reference		    	reference;
			typedef typename iterator_traits<Iterator>::pointer			    	pointer;

			normal_iterator() : M_current(Iterator()) { }
			explicit normal_iterator(const Iterator& i) : M_current(i) { }

			// Allow iterator to const_iterator conversion
			template <class Iter>
				normal_iterator(const normal_iterator<Iter,
					                typename enable_if<(ft::are_same<Iter, typename Container::pointer>::value),
					                                      Container>::type>& i)
				: M_current(i.base()) { }

			reference operator*() const {
				return *M_current;
			}

			pointer operator->() const {
				return M_current;
			}

			normal_iterator& operator++() {
				++M_current;
				return *this;
			}

			normal_iterator operator++(int) {
				return normal_iterator(M_current++);
			}

			normal_iterator& operator--() {
				--M_current;
				return *this;
			}

			normal_iterator& operator--(int) {
				return normal_iterator(M_current--);
			}

			reference operator[](const difference_type& n) const {
				return M_current[n];
			}

			normal_iterator& operator+=(const difference_type& n) {
				M_current += n;
				return *this;
			}

			normal_iterator& operator+(const difference_type& n) const {
				return normal_iterator(M_current + n);
			}

			normal_iterator& operator-=(const difference_type& n) {
				M_current -= n;
				return *this;
			}

			normal_iterator operator-(const difference_type& n) const {
				return normal_iterator(M_current - n);
			}

			const Iterator& base() const {
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