#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class A {
public:
    A() {}
    A(string s) : s(s), data(new char[10000])
    { cout << " constructor" << endl; }
    A(const A& ref)
    {
        this->s = ref.s;
        this->data = new char[10000];
        cout << s << " copy constructor" << endl;
    }
    // A(A&& ref) noexcept
    // {
    //     this->s = ref.s;
    //     this->data = ref.data;
    //     ref.data = nullptr;
    //     cout << s << " move constructor" << endl;
    // }
    ~A()
    {
        delete[] data;
        cout << " ~constructor" << endl;
    }
    void print() { printf("data 가 가리키고 있는 주소 값: %x\n", data); }
private:
    string s;
    char* data;
};

int main(void)
{
    vector<A> v;

    A a("a");
    A b("b");

    v.push_back(a); // 벡터에 값(a) 입력
    v[0].print(); // v[0] 에 있는 data 가 가리키는 주소 값 출력

    cout << "벡터가 가리키고 있는 주소 값 : " << &v[0] << ", v.capacity() : " << v.capacity() << endl;

    v.push_back(b); // 벡터에 값(b) 입력 
    v[0].print();

    cout << "벡터가 가리키고 있는 주소 값 : " << &v[0] << ", v.capacity() : " << v.capacity() << endl;
    cout << "/////////// cut ///////////" << endl;
    return (0);
}