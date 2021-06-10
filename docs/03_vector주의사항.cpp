/*
https://yankoo.tistory.com/77

벡터 자체는 지역 변수로 저장이되어 stack 에 있지만, 안의 원소들은 동적할당에 의하여 heap 에 있다.
때문에, thread 를 사용할 경우 상당한 문제가 생길 수 있다. heap 과 stack 을 공유하는 thread 에서 문제가
생길 수 있기 때문에 thread safe 하지 않다. fork 는 괜찮을 듯

때문에, std::vector<int>* v = new std::vector<int> 로 vector 자체를 동적할당 해줘야한다.
*/

#include <iostream>
#include <cstdio>
#include <thread>
#include <vector>
#include <random>
#include <mutex>

#define SIZE 10

std::mutex m;

// 배열과 벡터를 받는다. 벡터는 레퍼런스를 이용하여 넘긴다.
void Print(std::vector<int>* v, int* arr)
{
    m.lock();
    // v 벡터의 원소에 0 ~ 10 사이의 값을 더해준다.
    printf("벡터 : ");
    for (int i = 0; i < SIZE; i++)
    {
        std::random_device rd;
        int input = rd() % 10;
        (*v)[i] += input;
        printf("[%d] ", (*v)[i]);
    }
    puts("");

    // arr 배열의 원소에 0 ~ 10 사이의 값을 더해준다.
    printf("배열 : ");
    for (int i = 0; i < SIZE; i++)
    {
        std::random_device rd;
        int input = rd() % 10;
        arr[i] += input;
        printf("[%d] ", arr[i]);
    }
    puts("");
    m.unlock();
}

int main(void)
{
    std::vector<int>* v = new std::vector<int>;
    v->reserve(SIZE);
    std::random_device rd;
    int arr[SIZE];

    // 벡터와 배열을 랜덤 값들로 초기화 이때, 백터와 배열 같은 값으로 들어간다. 다만,
    // 벡터의 elements 는 heap, 배열의 elements 는 stack 으로 들어간다.
    for (int i = 0; i < SIZE; i++)
    {
        int input = rd() % 10;
        v->push_back(input);
        arr[i] = input;
    }

    std::thread t1(Print, v, arr);
    std::thread t2(Print, v, arr);
    t1.join();
    t2.join();

    // 쓰레드 이후의 상황
    puts("스레드 실행 후의 상황");
    printf("벡터 : ");
    for (int i = 0; i < SIZE; i++)
        printf("[%d] ", (*v)[i]);

    puts("");
    printf("배열 : ");
    for (int i = 0; i < SIZE; i++)
        printf("[%d] ", arr[i]);

    return (0);
}