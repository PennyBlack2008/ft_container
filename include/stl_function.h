#ifndef _FUNCTION_H
#define _FUNCTION_H 1

namespace ft
{
  // 20.3.1 base classes
  /** @defgroup s20_3_1_base Functor Base Classes
   *  Function objects, or @e functors, are objects with an @c operator()
   *  defined and accessible.  They can be passed as arguments to algorithm
   *  templates and used in place of a function pointer.  Not only is the
   *  resulting expressiveness of the library increased, but the generated
   *  code can be more efficient than what you might write by hand.  When we
   *  refer to "functors," then, generally we include function pointers in
   *  the description as well.
   *
   *  Often, functors are only created as temporaries passed to algorithm
   *  calls, rather than being created as named variables.
   *
   *  Two examples taken from the standard itself follow.  To perform a
   *  by-element addition of two vectors @c a and @c b containing @c double,
   *  and put the result in @c a, use
   *  \code
   *  transform (a.begin(), a.end(), b.begin(), a.begin(), plus<double>());
   *  \endcode
   *  To negate every element in @c a, use
   *  \code
   *  transform(a.begin(), a.end(), a.begin(), negate<double>());
   *  \endcode
   *  The addition and negation functions will be inlined directly.
   *
   *  The standard functiors are derived from structs named @c unary_function
   *  and @c binary_function.  These two classes contain nothing but typedefs,
   *  to aid in generic (template) programming.  If you write your own
   *  functors, you might consider doing the same.
   *
   *  @{
   */
  /**
   *  This is one of the @link s20_3_1_base functor base classes@endlink.
   */

  /// One of the @link s20_3_3_comparisons comparison functors@endlink.
  template <class _Tp>
    struct less : public std::binary_function<_Tp, _Tp, bool>
    {
      bool
      operator()(const _Tp& __x, const _Tp& __y) const
      { return __x < __y; }
    };



  template <class _Pair>
    struct _Select1st : public std::unary_function<_Pair,
					      typename _Pair::first_type>
    {
      typename _Pair::first_type&
      operator()(_Pair& __x) const
      { return __x.first; }

      const typename _Pair::first_type&
      operator()(const _Pair& __x) const
      { return __x.first; }
    };

} // namespace std

#endif /* _FUNCTION_H */

// Local Variables:
// mode:C++
// End:
