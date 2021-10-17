#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <__config>
#include <cstddef>
#include <type_traits>

namespace ft {
	// Define a nested type if some predicate holds.
	template<bool, typename>
	struct enable_if { };

	template<typename TP>
	struct enable_if<true, TP> {
		typedef TP type;
	};

	template<typename TP, TP v>
	struct integral_constant {
		static const TP			value = v;
		typedef TP					value_type;
		typedef integral_constant	type;
		operator value_type() const {
			return value;
		}
	};

	/*----
	remove
	----*/
	template<typename TP>
	struct remove_volatile {
		typedef TP type;
	};

	template<typename TP>
	struct remove_volatile<volatile TP> {
		typedef TP type;
	};

	template<typename TP>
	struct remove_const {
		typedef TP type;
	};

	template<typename TP>
	struct remove_const<const TP> {
		typedef TP type;
	};

	template<typename TP>
	struct remove_cv {
		typedef typename remove_volatile<typename remove_const<TP>::type>::type type;
	};

	// is_integral 이미 존재하고 있음.
	template<typename TP>
	struct is_integral : integral_constant<bool, is_integral(TP)> { };
}

#endif