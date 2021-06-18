// http://cplusplus.com/reference/vector/vector/reserve/
/*
void reserve (size_type n);
Request a change in capacity
Requests that the vector capacity be at least enough to contain n elements.

If n is greater than the current vector capacity, 
the function causes the container to reallocate its storage increasing its capacity to n (or greater).

In all other cases, the function call does not cause a reallocation and 
the vector capacity is not affected.

This function has no effect on the vector size and cannot alter its elements.
*/

/*
reserve 는 vector container 의 용량을 제한하는 것이 아니라, 미리 용량을 늘려놓음.

만약, reserved 용량을 초과한 값이 들어간다면 현재 가지고 있는 용량의 2배로 container 를 늘려놓는다.
즉, vector 용량을 초과하면 제한하지 않고 용량이 떨어지더라도 오히려 미리 늘려놓는 것이다.

이와 다르게 resize 는 제한 시킬 수 있다. 용량 초과된 메모리는 다 초기화된다.
*/
#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int>::size_type sz;

    std::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i)
    {
        foo.push_back(i);
        if (sz != foo.capacity())
        {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
   
    std::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(bar.max_size());
    std::cout << "making bar grow:\n";
    for (int i = 0; i < 300; ++i)
    {
        bar.push_back(i);
        if (sz != bar.capacity())
        {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
    
    return (0);
}