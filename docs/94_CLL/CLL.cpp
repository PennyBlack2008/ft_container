/*
https://robodream.tistory.com/173
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int Value;
    struct ListNode* Link;
}ListNode;

typedef struct List
{
    ListNode* head;
    ListNode* tail;
}List;

/* 맨 앞에 요소를 추가한다. */
void Add_first(List* Target_List, int item);
/* pos 위치에 요소를 추가한다. */
void Add(List* Target_List, int pos, int item);
/* pos 위치에 요소를 제거한다. */
void Delete(List* Target_List, int pos);
/* list 초기화 */
void List_Initializer(List* Target_List);
/* pos 위치의 요소를 item 으로 바꾼다. */
void Replace(List* Target_List, int pos, int item);
void Find(List* Target_List, int item);
/* pos 위치의 요소를 반환한다. */
void get_entry(List* Target_List, int pos);
/* 리스트의 길이를 구한다. */
void get_length(List* Target_List);
/* 리스트가 비었는 지를 검사한다. */
void is_empty(List* Target_List);
void Printing(List* Target_List);

/* 
1. 제일 앞에 노드 추가
*/
void Add_first(List* Target_List, int item)
{
    ListNode* New = (ListNode*)malloc(sizeof(ListNode)); // 새로 값을 넣을 곳
    if (Target_List->head == NULL) // LL에 하나도 없을 때
    {
        Target_List->head = New;
        Target_List->tail = New;
        New->Value = item;
        New->Link = Target_List->tail;
        return ;
    }
    else // Target_List->header != NULL
    {
        New->Link = Target_List->head;
        New->Value = item;
        Target_List->head = New;
        Target_List->tail->Link = Target_List->head;
        return ;
    }
    return ;
}

/*
2. 노드 추가
*/
void Add(List* Target_List, int pos, int item)
{
    if (pos == 1)
    {
        Add_first(Target_List, item);
    }
    int i = 1;
    ListNode* Cur = Target_List->head;
    ListNode* New = (ListNode*)malloc(sizeof(ListNode));
    while (i > pos - 1)
    {
        Cur = Cur->Link;
        i++;
    }
    New->Value = item;
    New->Link = Cur->Link;
    Cur->Link = New;
}

/*
3. 노드 삭제
단순 연결 리스트와 완전히 같다.
*/
void Delete(List* Target_List, int pos)
{
    int i = 1;
    ListNode* Temp = NULL;
    ListNode* Cur = Target_List->head;
    while (i < pos)
    {
        if (i == pos - 1)
            Temp = Cur;
        Cur = Cur->Link;
        i++;
    }
    Temp->Link = Cur->Link;
    delete (Cur);
}

/*
4. 리스트 초기화
단순 연결 리스트와 같으나 tail 포인터를 초기화 하는 것을 추가
*/
voidd List__Initializer(List* Target_List)
{
    Target_List->head = NULL;
    Target_List->tail = NULL;
}

/*
5. 특정 위치 값 교체
*/
void Replace(List* Target_List, int pos, int item)
{
    int i = 1;
    ListNdoe* Cur = Target_List->head;
    while (i < pos)
    {
        Cur = Cur->Link;
        i++;
    }
    Cur->Value = item;
}

/*
6. 특정 값 탐색
*/
void Find(List* Target_List, int item)
{
    ListNode* Cur = Target_List->head;
    int i = 1;
    while (Cur != Target_List->head)
    {
        if (Cur->Value == item)
        {
            printf("%d 번째 노드에 %d 가 있습니다.\n", i, item);
        }
        i++;
        Cur = Cur->Link;
    }
}

/*
7. 특정 위치의 값 구하기
*/
void get_entry(List* Target_List, int pos)
{
    int i = 1;
    ListNode* Cur = Target_List->head;
    while (i < pos)
    {
        Cur = Cur->Link;
        i++;
    }
    printf("%d 번째에는 %d 가 있습니다.\n", pos, Cur->Value);
}

/*
8. 총 길이 구하기
*/
void get_length(List* Target_List)
{
    ListNode* Cur = Target_List->head;
    int i = 1;
    while (Cur != Target_List->head)
    {
        i++;
        Cur = Cur->Link;
    }
    printf("노드의 갯수는 %d 개 입니다.\n", i);
}

/*
9. 비어 있는 지 확인
*/
void is_empty(List* Target_List)
{
    if (Target_List->head == NULL)
        printf("리스트가 비었습니다.\n");
    if (Target_List->head != NULL)
        printf("리스트에 내용이 있습니다.\n");
}

/*
10. 리스트 내의 모든 데이터 출력

리스트 내의 모든 데이터를 출력합니다.
단순 연결 리스트와 비교해서 루프 끝내는 조건이 헤더와 같은 때이다.
*/
void Printing(List* Target_List)
{
    ListNode* Cur = Target_List->head;
    printf("%d -> ", Cur->Value);
    Cur = Cur->Link;
    while (Cur != Target_List->head)
    {
        printf("%d -> ", Cur->Value);
        Cur = Cur->Link;
    }
    printf("\n");
}