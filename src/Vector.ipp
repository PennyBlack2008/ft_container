namespace ft
{

template<typename value_type>
Vector<value_type>::iterator::iterator():
    pointer(nullptr)
{
}

template<typename value_type>
Vector<value_type>::iterator::iterator(value_type* val):
    pointer(val)
{
}

template<typename value_type>
Vector<value_type>::iterator::iterator(Vector<value_type>::iterator const&other):
    pointer(other.pointer)
{
}

template<typename value_type>
typename Vector<value_type>::iterator& Vector<value_type>::iterator::operator=(Vector<value_type>::iterator const& other)
{
    this->pointer = other.pointer;
    return (*this);
}

template<typename value_type>
Vector<value_type>::iterator::~iterator()
{
}

template<typename value_type>
value_type& Vector<value_type>::iterator::operator*()
{
    return (*this->pointer);
}

template<typename value_type>
value_type const& Vector<value_type>::const_iterator::operator*() const
{
    return (*this->pointer);
}

template<typename value_type>
bool Vector<value_type>::iterator::operator==(iterator const& other) const
{
    return (this->pointer == other.pointer);
}

template<typename value_type>
bool Vector<value_type>::iterator::operator!=(iterator const& other) const
{
    return (this->pointer != other.pointer);
}

template<typename value_type>
bool Vector<value_type>::iterator::operator<(iterator const& other) const
{
    return (this->pointer < other.pointer);
}

template<typename value_type>
bool Vector<value_type>::iterator::operator<=(iterator const& other) const
{
    return (this->pointer <= other.pointer);
}

template<typename value_type>
bool Vector<value_type>::iterator::operator>(iterator const& other) const
{
    return (this->pointer > other.pointer);
}

template<typename value_type>
bool Vector<value_type>::iterator::operator>=(iterator const& other) const
{
    return (this->pointer >= other.pointer);
}

template<typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::iterator::operator++(int)
{
    ++this->pointer;
    return (*this);
}

template<typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::iterator::operator++()
{
    Vector<value_type>::iterator tmp(*this);
    operator++();
    return (tmp);
}

template<typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::iterator::operator--(int)
{
    --this->pointer;
    return (*this);
}

template<typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::iterator::operator--()
{
    Vector<value_type>::iterator tmp(*this);
    operator--();
    return (tmp);
}

template<typename value_type>
Vector<value_type>::const_iterator::const_iterator():
    iterator(nullptr)
{
}

template<typename value_type>
Vector<value_type>::const_iterator::const_iterator(value_type* val):
    iterator(val)
{
}

template<typename value_type>
Vector<value_type>::const_iterator::const_iterator(Vector<value_type>::const_iterator const&other):
    iterator(other.pointer)
{
}

template<typename value_type>
typename Vector<value_type>::const_iterator& Vector<value_type>::const_iterator::operator=(Vector<value_type::const_iterator const& other)
{
}

template<typename value_type>
typename
}