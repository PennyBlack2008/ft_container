#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <__config>
#include <cstddef>
#include <type_traits>

namespace ft {
	// Define a nested type if some predicate holds.
	template<bool, typename>
	struct enable_if { };

	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<typename T, T v>
	struct integral_constant {
		static const T			value = v;
		typedef T					value_type;
		typedef integral_constant	type;
		operator value_type() const {
			return value;
		}
	};

	/*----
	remove
	----*/
	template<typename T>
	struct remove_volatile {
		typedef T type;
	};

	template<typename T>
	struct remove_volatile<volatile T> {
		typedef T type;
	};

	template<typename T>
	struct remove_const {
		typedef T type;
	};

	template<typename T>
	struct remove_const<const T> {
		typedef T type;
	};

	template<typename T>
	struct remove_cv {
		typedef typename remove_volatile<typename remove_const<T>::type>::type type;
	};

	// is_integral 이미 존재하고 있음.
	template<typename T>
	struct is_integral : integral_constant<bool, is_integral(T)> { };
}

#endif