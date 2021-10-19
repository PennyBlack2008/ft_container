#ifndef _CPP_TYPE_TRAITS_HPP_
#define _CPP_TYPE_TRAITS_HPP_

#include <type_traits>

namespace ft {
	namespace detail {
		typedef char	one;
		typedef char	two[2];

		template<typename Tp>
		one	test_type(int Tp::*);
		template<typename Tp>
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

	template<class Sp, class Tp>
	struct traitor {
		enum { value = bool(Sp::value) || bool(Tp::value) };
		typedef typename truth_type<value>::type type;
	};

	// Compare for equality of types.
	template<typename, typename>
	struct are_same {
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename Tp>
	struct are_same<Tp, Tp> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*-------
	is_void
	-------*/
	// Holds if the template-argument is a void type.
	template<typename Tp>
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
	template<class Tp>
	struct is_integer {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_integer<bool> {
		enum { value = 1 };
		typedef true_type type;
	};

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
	template<typename Tp>
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
	template<typename Tp>
	struct is_pointer {
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename Tp>
	struct is_pointer<Tp*> {
		enum { value = 1 };
		typedef true_type type;
	};

	/*------------------
	Normal iterator type
	------------------*/
	template<typename Tp>
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
	template<typename Tp>
	struct is_arithmetic : public traitor<is_integer<Tp>, is_floating<Tp> > { };

	/*--------------
	is_fundamental
	--------------*/
	template<typename Tp>
	struct is_fundamental : public traitor<is_void<Tp>, is_pointer<Tp> > { };

	/*---------
	is_scalar
	---------*/
	// A scalar type is an arithmetic type or a pointer type
	template<typename Tp>
	struct is_scalar : public traitor<is_arithmetic<Tp>, is_pointer<Tp> > { };

	/*----
	is_pod
	----*/
	// For the immediate use, the following is a good approximation.
	template<typename Tp>
	struct is_pod {
		enum { value = (sizeof(detail::test_type<Tp>(0)) != sizeof(detail::one)) };
	};

	/*--------
	is_empty
	--------*/
	template<typename Tp>
	struct is_empty {
		private:
			template<typename>
			struct first { };
			template<typename Up>
			struct second : public Up { };
		public:
			enum { value = sizeof(first<Tp>) == sizeof(second<Tp>) };
	};
	/*-------
	is_char
	-------*/
	//For use in std::copy and std::find overloads for streambuf iterators.
	template<typename Tp>
	struct is_char {
		enum { value = 0 };
		typedef false_type type;
	};

	template<>
	struct is_char<char> {
		enum { value = 1 };
		typedef true_type type;
	};
}
#endif