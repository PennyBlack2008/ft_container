#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_

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

	// __is_integral 이미 존재하고 있음.
	template<typename T>
	struct is_integral : integral_constant<bool, __is_integral(T)> { };
}

#endif