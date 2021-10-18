#ifndef CONSTRUCT_HPP
#define CONSTRUCT_HPP

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

	template<class Tp>
	inline void Destroy(Tp* pointer) {
		pointer->~Tp();
	}

	template<class ForwardIterator>
	inline void destroy_aux(ForwardIterator first, ForwardIterator last, false_type) {
		for (;first != last;++first)
			ft::Destroy(&*first);
	}

	template<class ForwardIterator>
	inline void destroy_aux(ForwardIterator first, ForwardIterator last, true_type) {
	}

	template<class ForwardIterator>
	inline void Destroy(ForwardIterator first, ForwardIterator last) {
		typedef typename iterator_traits<ForwardIterator>::value_type Value_type;
		typedef typename is_scalar<Value_type>::type	Has_trivial_destructor;
		ft::destroy_aux(first, last, Has_trivial_destructor());
	}

	template<class Tp> class allocator;

	template<class ForwardIterator, typename Allocator>
	void Destroy(ForwardIterator first, ForwardIterator last, Allocator alloc) {
		for (;first != last; ++first)
			alloc.destroy(&*first);
	}

	template<class ForwardIterator, typename Tp>
	inline void Destroy(ForwardIterator first, ForwardIterator last, allocator<Tp>) {
		Destroy(first, last);
	}
}

#endif