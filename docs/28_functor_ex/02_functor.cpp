#include <iostream>
#include <algorithm>

bool Compare(int N1, int N2) {
    if (N1 < N2)
        return true;
    else 
        return false;
}

int main(void) {
    int Array[] = { 5, 3, 2, 1, 7, 8 };
    /**
     * sort 안에 Compare가 if문으로 들어가 Compare의 규칙대로
     * sort이 이루어진다. 그리고 첫번째 파라미터, 두번째 파라미터는
     * 배열에서 소팅할 범위를 정해준것이다.
     */ 
    std::sort(Array, Array + 6, Compare);
    for (int i = 0; i < 6; i++)
        std::cout << Array[i] << ", ";
}