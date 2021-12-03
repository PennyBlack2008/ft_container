/*
* type_traits는 컴파일 시간동안 타입에 대한 다양한 속성을 알아내는 기술
* https://narss.tistory.com/entry/TypeTraits
*/
#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_

#include <__config>
#include <cstddef>
#include <type_traits>

namespace ft
{
	/**
	 * enable_if, SFINAE을 이용해서 true가 아니게 되면 오버로딩 후보에서 제외한다. 
	 * aka. 템플릿들을 위한 컴파일 타임 스위치
	 * 이 기능은 템플릿 메타 프로그래밍에서 코드 수를 줄이는 도구로 활용된다.
	*/
	template<bool, typename>
	struct enable_if { };

	template<typename T>
	struct enable_if<true, T>
	{ typedef T type; };

	/**
	 * integral_constant, 모든 정수 계열 상수 값을 타입으로 만들어주는 템플릿.
	 * is_pointer등의 type_traits를 만들 때 이것을 기반으로 간소화 및 가독성을 높일 수 있음 
	 **/
	template<typename T, T v>
	struct integral_constant
	{
		static const T				value = v;
		typedef T					value_type;
		typedef integral_constant	type;
		operator value_type() const
		{ return value; }
	};

	// __is_integral 이미 존재하고 있음.
	template<typename T>
	struct is_integral : integral_constant<bool, __is_integral(T)> { };
}

#endif