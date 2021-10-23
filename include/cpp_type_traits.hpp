/**
 * 템플릿 메타 프로그래밍
 * 컴파일 시간에 연산을 수행한다.
 * https://sungbeom.github.io/2020/01/05/EffectiveCpp7-8.html
 * 
 * 여기서 enum은 값을 계산하는 용도로 사용되는 데, TMP에서 이것을 '나열자 둔갑술(enum hack)'라고 한다.
 * value 변수는 현재 계산된 계승 값을 담는 역할을 맡습니다.
 **/

#ifndef _CPP_TYPE_TRAITS_HPP_
#define _CPP_TYPE_TRAITS_HPP_

#include <type_traits>

namespace ft {
	namespace detail {
		typedef char	one;
		typedef char	two[2];

		template<typename T>
		one	test_type(int T::*);
		template<typename T>
		two&	test_type(...);
	}

	template<typename Iterator, typename Container>
	class normal_iterator;

	typedef char one;
	typedef char two[2];

	struct true_type {};
	struct false_type {};

	template<bool>
	struct truth_type {
		typedef false_type type;
	};

	template<>
	struct truth_type<true> {
		typedef true_type type;
	};

	template<class S, class T>
	struct traitor {
		enum { value = bool(S::value) || bool(T::value) };
		typedef typename truth_type<value>::type type;
	};

	// Compare for equality of types.
	template<typename, typename>
	struct are_same {
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename T> 
	struct are_same<T, T> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*-------
	is_void
	-------*/
	// Holds if the template-argument is a void type.
	template<typename T>
	struct is_void {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_void<void> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*----------
	is_integer
	----------*/
	template<class T>
	struct is_integer {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_integer<bool> {
		enum { value = 1 };
		typedef true_type type;
	};

	/**
	 * 예시로 is_integer<'c'>::value == 1이 되고,
	 * 		is_integer<'c'>::type == true_type가 된다.
	 **/
	template<>
	struct is_integer<char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<signed char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<unsigned char> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<short> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<unsigned short> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<int> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<unsigned int> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<unsigned long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<long long> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_integer<unsigned long long> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*-----------
	is_floating
	-----------*/
	template<typename T>
	struct is_floating {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_floating<float> {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_floating<double> {
		enum { value = 1 };
		typedef true_type type;
	};

	template<>
	struct is_floating<long double> {
		enum { value = 0 };
		typedef true_type type;
	};

	/*----------
	is_pointer
	----------*/
	template<typename T>
	struct is_pointer {
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename T>
	struct is_pointer<T*> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*------------------
	Normal iterator type
	------------------*/
	template<typename T>
	struct is_normal_iterator {
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename Iterator, typename Container>
	struct is_normal_iterator<ft::normal_iterator<Iterator, Container> > {
		enum { value = 1 };
		typedef true_type type;
	};

	/*-------------
	is_arithmetic
	-------------*/
	template<typename T>
	struct is_arithmetic : public traitor<is_integer<T>, is_floating<T> > { };

	/*--------------
	is_fundamental
	--------------*/
	template<typename T>
	struct is_fundamental : public traitor<is_void<T>, is_pointer<T> > { };

	/*---------
	is_scalar
	---------*/
	// A scalar type is an arithmetic type or a pointer type
	template<typename T>
	struct is_scalar : public traitor<is_arithmetic<T>, is_pointer<T> > { };

	/*----
	is_pod
	----*/
	// For the immediate use, the following is a good approximation.
	template<typename T>
	struct is_pod {
		enum { value = (sizeof(detail::test_type<T>(0)) != sizeof(detail::one)) };
	};

	/*--------
	is_empty
	--------*/
	template<typename T>
	struct is_empty {
		private:
			template<typename>
			struct first { };
			template<typename Up>
			struct second : public Up { };
		public:
			enum { value = sizeof(first<T>) == sizeof(second<T>) };
	};
	/*-------
	is_char
	-------*/
	//For use in std::copy and std::find overloads for streambuf iterators.
	template<typename T>
	struct is_char {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_char<char> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*---------
	conditional
	---------*/
	template <bool B, class If, class Then>
	struct conditional { typedef If type; };
	template <class If, class Then>
	struct conditional<false, If, Then> { typedef Then type; };
}
#endif