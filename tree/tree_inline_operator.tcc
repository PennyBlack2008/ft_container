namespace ft
{
  template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc>
  inline bool
    operator==(const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
                const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
  {
    return x.size() == y.size()
            && equal(x.begin(), x.end(), y.begin());
  }

  template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc>
  inline bool
    operator<(const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
              const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
  {
    return lexicographical_compare(x.begin(), x.end(),
                                    y.begin(), y.end());
  }

  template<typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
  inline bool
    operator!=(const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
                const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
  { return !(x == y); }

  template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc>
  inline bool
    operator>(const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
              const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
  { return y < x; }

  template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc>
  inline bool
    operator<=(const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
                const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
    { return !(y < x); }

  template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc>
  inline bool
    operator>=(const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
                const RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
    { return !(x < y); }

  template<typename Key, typename Val, typename KeyOfValue,
            typename Compare, typename Alloc>
  inline void
    swap(RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& x,
          RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& y)
  { x.swap(y); }
}