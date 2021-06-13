/*
https://macinjune.com/all-posts/web-developing/mac-develop-tip/c-doubly-linked-list-%EA%B5%AC%ED%98%84/
*/
#include <stdlib.h>
#include <stdio.h>

/* 노드 구현 */
typedef struct Node
{
    int data;
    struct Node* nextNode;
    struct Node* prevNode; // Singly LL 에는 없음
} Node;

/*
** 노드 생성 **

입력 받은 데이터를 newNode->data 에 입력,
nextNode, prevNode 모두 NULL 로 초기화.
*/
Node* DLL_createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;
    return (newNode);
}

/* 노드 소멸 */
void DDL_destroyNode(Node* node)
{
    free(node);
}

/* 
** 노드 추가 **

Tail 뒤에 새로운 노드를 추가하는 연산으로 Singly 와 대부분 유사하나, newNode->prevNode = tail;
부분만 추가되었습니다.
*/
void DDL_appendNode(Node** head, Node* newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        /* 꼬리 찾기 */
        Node* tail = *head;
        while (tail->nextNode != NULL)
            tail = tail->nextNode;
        tail->nextNode = newNode;
        newNode->prevNode = tail;
        // 새로운 꼬리인 newNode의 newNode->nextNode 는 NULL 인 상태로
    }
}

/*
노드 탐색
*/
Node* DDL_getNodeAt(Node* head, int index)
{
    Node* current = head;
    while (current != NULL && --index >= 0)
    {
        current = current->nextNode;
    }
    return (current);
}

/*
노드 삭제
*/
void DDL_removeNode(Node** head, Node* removedNode)
{
    if (*head == removedNode)
    {
        *head = removedNode->nextNode;
        if (*head != NULL)
        {
            (*head)->prevNode = NULL;
        }
        removedNode->nextNode = NULL;
        removedNode->prevNode = NULL;
    }
    else
    {
        Node* temp = removedNode;
        removedNode->prevNode->nextNode = temp->nextNode;
        if (removedNode->nextNode != NULL)
            removedNode->nextNode->prevNode = temp->prevNode;
        removedNode->nextNode = NULL;
        removedNode->prevNode = NULL;
    }
}

/*
노드 삽입
*/
void insertAfter(Node* current, Node* newNode)
{
    if (current != NULL)
    {
        newNode->prevNode = current;
        newNode->nextNode = current->nextNode;
        if (current->nextNode != NULL)
            current->nextNode->prevNode = newNode;
        current->nextNode = newNode;
    }
}

/*
DDL 출력
*/
void DDL_display(Node** head)
{
    Node* current = *head;
    printf("PRINT CURRENT NODES\n");
    printf("===================\n");
    while (current != NULL)
    {
        printf("%d\t", current->data);
        current = current->nextNode;
    }
    printf("\n=================\n");
}

int main(int argc, const char* argv[])
{
    Node* list = NULL;
    Node* newNode = NULL;
    DDL_appendNode(&list, DLL_createNode(4));
    DDL_appendNode(&list, DLL_createNode(5));
    DDL_appendNode(&list, DLL_createNode(6));
    DDL_appendNode(&list, DLL_createNode(7));
    DDL_display(&list);

    Node* searchNode = DDL_getNodeAt(list, 1);
    DDL_removeNode(&list, searchNode);
    DDL_display(&list);
    return (0);
}