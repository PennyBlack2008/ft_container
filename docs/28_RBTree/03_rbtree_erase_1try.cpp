// https://hyunipad.tistory.com/15 근데 좀 이상하다.
#include <stdio.h>

typedef struct tagRBTNode {
  struct tagRBTNode* Parent;
  struct tagRBTNode* Left;
  struct tagRBTNode* Right;

  enum {RED, BLACK} Color;
  int Data;
}RBTNode;

extern RBTNode* Nil;

RBTNode* RBT_SearchNode(RBTNode* Tree, int Target) {
  if (Tree == Nil)
    return NULL;

  if (Tree->Data > Target) {
    return RBT_SearchNode(Tree->Left, Target);
  }
  else if (Tree->Data < Target) {
    return RBT_SearchNode(Tree->Right, Target);
  }
  else{
    return Tree;
  }
}

RBTNode* RBT_SearchMinNode(RBTNode* Tree) {
  if (Tree == Nil) {
    return Nil;
  }
  if (Tree->Left == Nil) {
    return Nil;
  }
  else {
    return RBT_SearchMinNode(Tree->Left);
  }
}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor) {
  RBTNode* Sibling = NULL;

  // Successor가 이중흑색노드
  while (Successor->Parent != NULL && Successor->Color == BLACK) {
    // 이중흑색이 루트까지 가거나 빨간색 노드에게 넘어가면 반복 종료
    if (Successor == Successor->Parent->Left) {
      // 이중흑색 노드가 왼쪽인 경우
      Sibling = Successor->Parent->Right;
      // 1. 형제가 빨간색인 경우
      if (Sibling->Color == RED) {
        Sibling->Color = BLACK; // 형제를 검은색 칠하고
        Successor->Parent->Color = RED; // 부모를 빨간색 칠하고
        RBT_RotateLeft(Root, Successor->Parent); // 부모를 기준으로 좌회전
      }
      // 2. 형제가 검은색인 경우
      else {
        // 2-1. 형제의 양쪽 자식이 모두 검은색인 경우
        if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK) {
          Sibling->Color = RED; // 형제노드만 빨간색으로 칠해준다.
          Successor = Successor->Parent; // 이중 흑색노드를 이중흑색노드의 부모로 대체한다.
        }
        // 2-2. 왼쪽 자식이 빨간색, 오른쪽 자식은 검은색인 경우
        else {
          if (Sibling->Left->Color == RED) {
            Sibling->Left->Color = BLACK; // 왼쪽 자식은 검정색 칠해주고
            Sibling->Color = RED; // 형제노드 빨간색 칠해주고
            RBT_RotateRight(Root, Sibling); // 형제노드를 기준으로 우회전
            Sibling = Successor->Parent->Right;
          }
          else { // 2-3. 오른쪽 자식이 빨간색인 경우
            Sibling->Color = Successor->Parent->Color;
            Successor->Parent->Color = BLACK;
            Sibling->Right->Color = BLACK;
            RBT_RotateLeft(Root, Successor->Parent);
            Successor = (*Root);
          }
        }
      }
    }
    else { // 이중흑색 노드가 오른쪽 자식일 때
      Sibling = Successor->Parent->Left;
      // 1. 형제가 빨간색인 경우
      if (Sibling->Color == RED) {
        Sibling->Color = BLACK;
        Successor->Parent->Color = RED;
        RBT_RotateRight(Root, Successor->Parent);
      }
      // 2. 형제가 검은색인 경우
      else {
        // 2-1. 형제의 양쪽 자식이 모두 검은색인 경우
        if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK) {
          Sibling->Color = RED;
          Successor = Successor->Parent;
        }
        // 2-2. 오른쪽 자식이 빨간색인 경우
        else {
          if (Sibling->Right->Color == RED) {
            Sibling->Right->Color = BLACK;
            Sibling->Color = RED;
            RBT_RotateLeft(Root, Sibling);
            Sibling = Successor->Parent->Left;
          }
          // 2-3. 오른쪽 자식이 빨간색인 경우
          Sibling->Color = Successor->Parent->Color;
          Successor->Parent->Color = BLACK;
          Sibling->Right->Color = BLACK;
          RBT_RotateRight(Root, Successor->Parent);
          Successor = (*Root);
        }
      }
    }
  }
}

RBTNode* RBT_RemoveNode(RBTNode** Root, int Data) {
  RBTNode* Removed = NULL;
  RBTNode* Successor = NULL;
  RBTNode* Target = RBT_SearchNode((*Root), Data);

  if (Target == NULL) {
    return NULL;
  }

  if (Target->Left == Nil || Target->Right == Nil) {
    Removed = Target;
  }
  else {
    Removed = RBT_SearchMinNode(Target->Right);
    Target->Data = Removed->Data;
  }

  if (Removed->Left != Nil) {
    Successor = Removed->Left;
  }
  else {
    Successor = Removed->Right;
  }

  Successor->Parent = Removed->Parent;

  if (Removed->Parent == NULL) {
    (*Root) = Successor;
  }
  else {
    if (Removed == Removed->Parent->Left) {
      Removed->Parent->Left = Successor;
    }
    else {
      Removed->Parent->Right = Successor;
    }
  }

  // 삭제한 노드가 검은색인 경우 이중 흑색이기 때문에 처리를 위해 리빌딩 함수 호출
  if (Removed->Color == BLACK)
    RBT_RebuildAfterRemove(Root, Successor);
  return Removed;
}