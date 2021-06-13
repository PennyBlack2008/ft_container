#include <iostream>
#include <string>

class Node
{
public:
    std::string txt;
    Node* tail;
};

class SLL
{
public:
    Node* LinkHead;
    Node* tempPoint;

    SLL()
    {
        LinkHead = NULL;
    }

    void CreateLinkToFirst(std::string txt)
    {
        Node* temp = new Node(); // 임의로 temp 를 하나 만들어 채워넣기 위해 메모리 할당
        temp->txt = txt;
        temp->tail = LinkHead; // 새 노드의 꼬리에 (구) 링크 헤드를 연결
        LinkHead = temp; // 이젠 새 노드가 (신) 링크 헤드가 된다.
    }

    void PrintAll()
    {
        tempPoint = LinkHead; // 출력을 위해 포인터가 옮겨 다닐 예정, LinkHead 를 복사하여 사용
        while (tempPoint->tail != NULL)
        {
            std::cout << tempPoint->txt << "->";
            tempPoint = tempPoint->tail; // 비어있는 곳까지 계속 찾아들어간다.
        }
        std::cout << tempPoint->txt << std::endl;
    }
};

int main(void)
{
    SLL* rainbow = new SLL();

    rainbow->CreateLinkToFirst("빨강");
    rainbow->CreateLinkToFirst("주황");
    rainbow->CreateLinkToFirst("노랑");
    rainbow->CreateLinkToFirst("초록");
    rainbow->CreateLinkToFirst("파랑");
    rainbow->CreateLinkToFirst("남색");
    rainbow->CreateLinkToFirst("보라");

    rainbow->PrintAll();
    return (0);
}