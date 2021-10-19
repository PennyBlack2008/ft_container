#ifndef _ALGORITHM_HPP_
#define _ALGORITHM_HPP_

#include <algorithm>
#include "cpp_type_traits.hpp"
#include "./iterator.hpp"

namespace ft {
	/*--
	swap
	--*/
	template<typename Tp>
	inline void swap(Tp& a, Tp& b) {
		Tp tmp = a;
		a = b;
		b = tmp;
	}

	/*---
	equal
	---*/
	template<typename T1, typename T2 = T1>
	struct equal_to {
		bool operator()(const T1& x, const T1& y) const { return x == y; }
		bool operator()(const T1& x, const T2& y) const { return x == y; }
		bool operator()(const T2& x, const T1& y) const { return x == y; }
		bool operator()(const T2& x, const T2& y) const { return x == y; }
	};

	template<typename T1>
	struct equal_to<T1, T1> {
		bool operator()(const T1& x, const T1& y) const { return x == y; }
	};

	template<typename T1>
	struct equal_to<const T1, T1> {
		bool operator()(const T1& x, const T1& y) const { return x == y; }
	};

	template<typename T1>
	struct equal_to<T1, const T1> {
		bool operator()(const T1& x, const T1& y) const { return x == y; }
	};

	template<typename InputIterator1, typename InputIterator2, class BinaryPredicate>
	inline bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, (void)++first2)
			if (!pred(*first1, *first2))
				return false;
		return true;
	}

	template<typename InputIterator1, typename InputIterator2>
	inline bool
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		typedef typename iterator_traits<InputIterator1>::value_type	v1;
		typedef typename iterator_traits<InputIterator2>::value_type	v2;
		return equal(first1, last1, first2, equal_to<v1, v2>());
	}

	/*---------------------
	lexicographical_compare
	---------------------*/
	template<typename InputIterator1, typename InputIterator2>
	bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (;first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template<typename InputIterator1, typename InputIterator2, typename Compare>
	bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for (;first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	inline bool
	lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2)
	{
		const size_t	len1 = last1 - first1;
		const size_t	len2 = last2 - first2;
		const int		result = std::memcmp(first1, first2, std::min(len1, len2));
		return result != 0 ? result < 0 : len1 < len2;
	}

	inline bool
	lexicographical_compare(const char* first1, const char* last1, const char* first2, const char* last2)
	{
		#if CHAR_MAX == SCHAR_MAX
			return ft::lexicographical_compare((const signed char*) first1,
					(const signed char*) last1,
					(const signed char*) first2,
					(const signed char*) last2);
		#else
			return ft::lexicographical_compare((const unsigned char*) first1,
					(const unsigned char*) last1,
					(const unsigned char*) first2,
					(const unsigned char*) last2);
		#endif
	}

	template<bool, typename>
	struct __copy {
		template<typename II, typename OI>
		static OI copy(II first, II last, OI result) {
			for(; first != last; ++result, ++first)
				*result = *first;
			return result;
		}
	};

	template<bool BoolType>
	struct __copy<BoolType, random_access_iterator_tag> {
		template<typename II, typename OI>
		static OI copy(II first, II last, OI result) {
			typedef typename iterator_traits<II>::difference_type	Distance;
			for(Distance n = last - first; n > 0; --n) {
				*result = *first;
				++first;
				++result;
			}
			return result;
		}
	};
	
	template<>
	struct __copy<true, random_access_iterator_tag> {
		template<typename Tp>
		static Tp* copy(const Tp* first, const Tp* last, Tp* result) {
			std::memmove(result, first, sizeof(Tp) * (last - first));
			return result + (last - first);
		}
	};

	template<typename II, typename OI>
	inline OI copy_aux(II first, II last, OI result) {
		typedef typename iterator_traits<II>::value_type			ValueTypeI;
		typedef typename iterator_traits<OI>::value_type			ValueTypeO;
		typedef typename iterator_traits<II>::iterator_category	Category;
		const bool simple = (is_scalar<ValueTypeI>::value
									&& is_pointer<II>::value
									&& is_pointer<OI>::value
									&& are_same<ValueTypeI, ValueTypeO>::value);
		return ft::__copy<simple, Category>::copy(first, last, result);
	}

	template<bool, bool>
	struct copy_normal {
		template<typename II, typename OI>
		static OI copy_n(II first, II last, OI result) {
			return copy_aux(first, last, result);
		}
	};
	
	template<>
	struct copy_normal<true, false> {
		template<typename II, typename OI>
		static OI copy_n(II first, II last, OI result) {
			return copy_aux(first.base(), last.base(), result);
		}
	};

	template<>
	struct copy_normal<false, true> {
		template<typename II, typename OI>
		static OI copy_n(II first, II last, OI result) {
			return OI(copy_aux(first, last, result.base()));
		}
	};

	template<>
	struct copy_normal<true, true> {
		template<typename II, typename OI>
		static OI copy_n(II first, II last, OI result) {
			return OI(copy_aux(first.base(), last.base(), result.base()));
		}
	};

	template<typename InputIterator, typename OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		const bool in = ft::is_normal_iterator<InputIterator>::value;
		const bool out = ft::is_normal_iterator<OutputIterator>::value;
		return copy_normal<in, out>::copy_n(first, last, result);
	}
}

#endif