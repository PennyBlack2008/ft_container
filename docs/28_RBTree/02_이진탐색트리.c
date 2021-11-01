/**
 * https://wkdtjsgur100.github.io/binary-search-tree/
 **/
#include <stdio.h>
#include <stdlib.h>

typedef struct  NodeStruct
{
    int value;
    struct NodeStruct* leftChild;
    struct NodeStruct* rightChild;
}               Node;

Node* root = NULL; // root 초기화

/** 이 함수는 적절한 삽입위치를 찾을 때까지 재귀함수가 된다 */
Node* BST_insert(Node* root, int value)
{
    /** 만약 root가 NULL이면 트리가 비어있다는 뜻이니깐,
     * 본인이 root가 되면 된다. 본인이 root가 되고, 
     * 각각의 멤버 변수를 초기화한다.
     * */
    if (root == NULL)
    {
        root = (Node*)malloc(sizeof(Node));
        root->leftChild = root->rightChild = NULL;
        root->value = value;
        return root;
    }
    else /** Tree가 비어있지 않다면??!! */
    {
        /** root의 값이 value보다 크면 root를 좀 더 왼쪽에 모셔야한다.
         * 반대로 작다면 root를 좀 더 오른쪽에 모신다.
         * */
        if (root->value > value)
            root->leftChild = BST_insert(root->leftChild, value);
        else
            root->rightChild = BST_insert(root->rightChild, value);
    }
    return root;
}

/** 해당 root 기준에서 가장 작은 노드를 찾는 함수 */
Node* findMinNode(Node* node)
{
    Node* tmp = root;
    while (tmp->leftChild != NULL)
        tmp = tmp->leftChild;
    return tmp;
}

/** 삭제의 4가지 단계
 * 1. */
Node* BST_delete(Node* root, int value)
{
    Node* tNode = NULL;
    /** root에 아무것도 없을 정도로 root를 옮겨다녔으면 이제 그만 찾아야지~ */
    if (root == NULL)
        return NULL;

    /** 원하는 value(key)값을 못찾았으니 왼쪽으로 root를 옮긴다. */
    if (root->value > value)
        root->leftChild = BST_delete(root->leftChild, value);
    else if (root->value < value) /** 여기는 반대로 오른쪽으로 root를 옮긴다. */
        root->rightChild = BST_delete(root->rightChild, value);
    else /** 삭제대상인 key값을 찾긴했는 데, 이제 이 key값의 상태를 확인 후, 조심히 삭제해야한다*/
    {
        // 자식 노드가 둘 다 있을 경우
        if (root->rightChild != NULL && root->leftChild != NULL)
        {
            // 1. tNode가 successor node이다. 삭제 노드 대신 희생하게 된다.
            tNode = findMinNode(root->rightChild);
            // 2. 이 root에 successor node가 갖고 있던 값을 넣는다.
            root->value = tNode->value;
            // 3. successor node를 삭제하기 위해 다시 이 함수를 실행한다.
            root->rightChild = BST_delete(root->rightChild, tNode->value);
        }
        else
        {
            // 4. successor node를 삭제한다.가 되어야할 것같은 데...모르겠다. 예제를 더 찾아봐야겠다.
            tNode = (root->leftChild == NULL) ? root->rightChild : root->leftChild;
            free(root); 
            return tNode;
        }
    }
    return root;
}

Node* BST_search(Node* root, int value)
{
    if (root == NULL)
        return NULL;
    
    if (root->value == value)
        return root;
    else if (root->value > value)
        return BST_search(root->leftChild, value);
    else
        return BST_search(root->rightChild, value);
}

void BST_print(Node* root)
{
    if (root == NULL)
        return ;

    printf("%d ", root->value);
    BST_print(root->leftChild);
    BST_print(root->rightChild);
}

int main()
{
    root = BST_insert(root, 5);
    root = BST_insert(root, 3);
    root = BST_insert(root, 7);
    root = BST_insert(root, 1);
    root = BST_insert(root, 9);
    root = BST_insert(root, 6);

    root = BST_delete(root, 5);

    BST_print(root);
    return (0);
}