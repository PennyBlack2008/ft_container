#ifndef _UNINITIALIZED_HPP_
#define _UNINITIALIZED_HPP_

#include <algorithm>
#include "construct.hpp"
#include "./iterator.hpp"

namespace ft {

	/*------------------------
	uninitialized_fill_n_aux
	------------------------*/
	template<typename ForwardIterator, typename Size, typename T>
	inline void uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, true_type) {
		std::fill_n(first, n, x);
	}


	template<typename ForwardIterator, typename Size, typename T>
	void uninitialzied_fill_n_aux(ForwardIterator first, Size n, const T& x, false_type) {
		ForwardIterator cur = first;
		try {
			for(;n>0;--n,++cur)
				ft::Construct(&*cur, x);
		} catch(...) {
			ft::Destroy(first, cur);
			throw;
		}
	}

	/*------------------
	uninitialized_fill_n
	------------------*/
	template<typename ForwardIterator, typename Size, typename T>
	inline void uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
		typedef typename ft::iterator_traits<ForwardIterator>::value_type	ValueType;
		typedef typename ft::is_scalar<ValueType>::type					Is_Pod;
		ft::uninitialized_fill_n_aux(first, n, x, Is_Pod());
	}

	/*--------------------
	uninitialized_copy_a
	--------------------*/
	template<typename InputIterator, typename ForwardIterator, typename Allocator>
	ForwardIterator uninitialized_copy_a(InputIterator first, InputIterator last, ForwardIterator result, Allocator alloc) {
		ForwardIterator cur = result;
		try {
			for(;first != last; ++first, ++cur)
				alloc.construct(&*cur, *first);
			return cur;
		} catch(...) {
			ft::Destroy(result, cur, alloc);
			throw;
		}
	}

	template<typename InputIterator, typename ForwardIterator, typename T>
	inline ForwardIterator uninitialized_copy_a(InputIterator first, InputIterator last, ForwardIterator result, std::allocator<T>) {
		return std::uninitialized_copy(first, last, result);
	}	

	/*----------------------
	uninitialized_fill_n_a
	----------------------*/
	template<typename ForwardIterator, typename Size, typename T, typename Allocator>
	void uninitialized_fill_n_a(ForwardIterator first, Size n, const T& x, Allocator alloc) {
		ForwardIterator cur = first;
		try {
			for(;n>0;--n, ++cur)
			alloc.construct(&*cur, x);
		} catch(...) {
			ft::Destroy(first, cur, alloc);
			throw;
		}
	}

	template<typename ForwardIterator, typename Size, typename T, typename T2>
	inline void uninitialized_fill_n_a(ForwardIterator first, Size n, const T& x, allocator<T2>) {
		ft::uninitialized_fill_n(first, n, x);
	}
}
#endif