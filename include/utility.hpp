#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {
	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair()
		: first(), second() { }

		pair(const T1& a, const T2& b)
		: first(a), second(b) { }

		template<class U1, class U2>
			pair(const pair<U1, U2>& p)
		: first(p.first), second(p.second) { }
	};

	template<class T1, class T2>
	inline bool
		operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{ return x.first == y.first && x.second == y.second; }

	// 우선적으로 x.first와 y.first를 비교하고, 만약 둘이 같다면, x.second와 y.second를 비교한다.
	template<class T1, class T2>
	inline bool
		operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{ return x.first < y.first || (!(y.first < x.first) && x.second < y.second); }

	template<class T1, class T2>
	inline bool
		operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{ return !(x == y); }

	template<class T1, class T2>
	inline bool
		operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{ return y < x; }

	template<class T1, class T2>
	inline bool
		operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{ return !(y < x); }

	template<class T1, class T2>
	inline bool
		operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{ return !(x < y); }

	template<class T1, class T2>
	inline pair<T1, T2>
		make_pair(T1 x, T2 y)
	{ return pair<T1, T2>(x, y); }

	template<class T>
	class set_key : public std::unary_function<T, T>
	{
    public:
			T&
				operator()(T& x) const
			{ return x; }

			const T&
				operator()(const T& x) const
			{ return x; }
	};

	template <class Pair>
	class map_key : public std::unary_function<Pair, typename Pair::first_type>
	{
    public:
			typename Pair::first_type&
				operator()(Pair& x) const
			{ return x.first; }

			const typename Pair::first_type&
				operator()(const Pair& x) const
			{ return x.first; }
	};

	template <class Pair>
	class map_value : public std::unary_function<Pair, typename Pair::second_type>
	{
    public:
			typename Pair::second_type&
				operator()(Pair& x) const
			{ return x.second; }

			const typename Pair::second_type&
				operator()(const Pair& x) const
			{ return x.second; }
	};
}

#endif