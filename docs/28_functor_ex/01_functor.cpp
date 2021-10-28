/**
 * https://blog.plorence.kr/544
 */

#include <iostream>

class Money {
private:
    int _Money = 0;
public:
    int operator()() {
        return this->_Money;
    }
    void operator()(int N) {
        this->_Money += N;
    }
};

int main(void) {
    Money money;
    money(100);
    int M = money();
    std::cout << M;
}