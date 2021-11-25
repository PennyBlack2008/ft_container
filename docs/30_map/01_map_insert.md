# map_insert

## 1번 형태

```
pair<iterator, bool> insert(const value_type& val);
template <class P> pair<iterator, bool> insert (P&& val);
```

```
int main()
{
  map<char, int> mymap;

  pair<map<char, int>::iterator, bool> a = mymap.insert(pair<char,int>('a', 100));
  if (a.second)
  {
    cout << "It has been saved successfully << endl;
    cout << a.first->first << ": " << a.first->second << endl;
  }
  else
  {
    cout << "element 'a' already existed" << endl;
  }
  return 0;
}
```

## 2번 형태

position을 넣어주므로 tree를 덜 탐색하도록 insert를 도와준다. 근데, position이 val가 있어야할 위치보다 뒤에 있으면 오히려 시간이 더 걸린다.

```
iterator insert(const_iterator position, const value_type& val);
template <class P> iterator insert(const_iterator position, P&& val);
```

```
int main()
{
  map<char, int> mymap;

  mymap.insert(std::pair<char, int>('a', 100));
  mymap.insert(std::pair<char, int>('z', 200));

  // 2번 constructor
  map<char, int>::iterator it = mymap.begin();
  mymap.insert(it, pair<char, int>('b', 300)); // 최대 효율로 넣기
  mymap.insert(it, pair<char, int>('c', 400)); // 최대 효율 x

  return 0;
}
```

## 3번 형태

```
template <class InputIterator>
  void insert(InputIterator first, InputIterator last);
```

mymap에 있는 map(트리)의 범위에 해당되는 데이터들을 새로 선언한 another map(트리)에 넣는다.
```
int main()
{
  map<char, int> mymap;

  mymap.insert(pair<char, int>('a', 100));
  mymap.insert(pair<char, int>('z', 200));
  mymap.insert(pair<char, int>('z', 300));
  mymap.insert(pair<char, int>('b', 400));
  mymap.insert(pair<char, int>('c', 500));

  map<char, int> another;
  another.insert(mymap.begin(), mymap.find('c'));

  for (pair<char, int> p : another)
    cout << p.first << ": " << p.second << endl;

  return 0;
}
```