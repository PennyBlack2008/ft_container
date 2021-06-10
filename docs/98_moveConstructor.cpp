#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class A {
public:
    A() {}
    A(string s) : s(s), data(new char[100])
    { cout << " constructor" << endl; }
    // A(const A& ref)
    // {
    //     this->s = ref.s;
    //     this->data = new char[10000];
    //     cout << s << " copy constructor" << endl;
    // }
    A(A&& ref) noexcept
    {
        this->s = ref.s;
        this->data = ref.data;
        ref.data = nullptr;
        cout << s << " move constructor" << endl;
    }
    ~A()
    {
        delete[] data;
        cout << " ~constructor" << endl;
    }
    void print() { printf("v[?].data 변수의 주소 값: %x\n", (this->data)); }

    string s;
    char* data;
};

int main(void)
{
    vector<A> v;

    A a("a");
    A b("b");

    printf("a.data 변수의 주소 값: %x\n", a.data);
    v.push_back(move(a)); // 벡터에 값(a) 입력
    v[0].print(); // v[0] 에 있는 data 가 가리키는 주소 값 출력

    printf("b.data 변수의 주소 값: %x\n", b.data);
    v.push_back(move(b)); // 벡터에 값(b) 입력 <-- 무조건 move(b) 를 해줘야한다. 안그러면 복사생성자가 생성된다.
    v[1].print();

    cout << "/////////// cut ///////////" << endl;
    return (0);
}