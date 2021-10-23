#ifndef _CONSTRUCT_HPP_
#define _CONSTRUCT_HPP_

#include <new>
#include "cpp_type_traits.hpp"

namespace ft {
	template<class T1, class T2>
	inline void Construct(T1* p, const T2& value) {
		new (static_cast<void*>(p))T1(value);
	}

	template<class T1>
	inline void Construct(T1* p) {
		new (static_cast<void*>(p))T1();
	}

	template<class T>
	inline void Destroy(T* pointer) {
		pointer->~T();
	}

	template<class ForwardIterator>
	inline void destroy_aux(ForwardIterator first, ForwardIterator last, false_type) {
		for (;first != last;++first)
			ft::Destroy(&*first);
	}

	template<class ForwardIterator>
	inline void destroy_aux(ForwardIterator first, ForwardIterator last, true_type) {
		(void)first;
		(void)last;
	}

	template<class ForwardIterator>
	inline void Destroy(ForwardIterator first, ForwardIterator last) {
		typedef typename iterator_traits<ForwardIterator>::value_type	Value_type;
		typedef typename is_scalar<Value_type>::type				 	Has_trivial_destructor;
		ft::destroy_aux(first, last, Has_trivial_destructor());
	}

	template<class T> class allocator;

	template<class ForwardIterator, typename Allocator>
	void Destroy(ForwardIterator first, ForwardIterator last, Allocator alloc) {
		for (;first != last; ++first)
			alloc.destroy(&*first);
	}

	template<class ForwardIterator, typename T>
	inline void Destroy(ForwardIterator first, ForwardIterator last, allocator<T>) {
		Destroy(first, last);
	}
}

#endif