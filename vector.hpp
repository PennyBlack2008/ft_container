#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <limits>

namespace ft
{
template<typename T>
class vector
{
    T* mData;
    size_t mCapacity;
    size_t mLength;
public:
    // 생성자
    vector(): mData(NULL), mCapacity(0), mLength(0) {}
    vector(size_t nums, T data) : mCapacity(nums), mLength(nums) { 
        mData = new T[nums];
        for (size_t i = 0; i < nums; i++)
            mData[i] = data;
    }
    // Vector(iterator first, iterator last) : mData(NULL), mCapacity(0), mLength(0) {
    //     this->assign(first, last);
    // }
    vector(vector const& other) {
        mData = new T[other.mCapacity];
        for (size_t i = 0; i < other.mCapacity; i++)
            mData[i] = other[i];
    }

    void reserve(size_type n){
        mCapacity = n;
        // 더 큰 용량이 오면 exception 던지게
    }
};
}

#endif