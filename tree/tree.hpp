#ifndef _TREE_HPP_
#define _TREE_HPP_ 1

#include "../include/algorithm.hpp" // equal
#include "../include/iterator.hpp"
#include "../include/utility.hpp" // ft::pair
#include <memory>

namespace ft
{
  enum RB_tree_color { RED = false, BLACK = true };

  struct RB_tree_node_base
  {
    typedef RB_tree_node_base*        Base_ptr;
    typedef const RB_tree_node_base*  Const_Base_ptr;

    RB_tree_color M_color;
    Base_ptr      M_parent;
    Base_ptr      M_left;
    Base_ptr      M_right;

    static Base_ptr
    S_minimum(Base_ptr x)
    {
      while (x->M_left != 0) x = x->M_left;
      return x;
    }

    static Const_Base_ptr
    S_minimum(Const_Base_ptr x)
    {
      while (x->M_left != 0) x = x->M_left;
      return x;
    }

    static Base_ptr
    S_maximum(Base_ptr x)
    {
      while (x->M_right != 0) x = x->M_right;
      return x;
    }

    static Const_Base_ptr
    S_maximum(Const_Base_ptr x)
    {
      while (x->M_right != 0) x = x->M_right;
      return x;
    }
  };

  template<typename Val>
  struct RB_tree_node : public RB_tree_node_base
  {
    typedef RB_tree_node<Val>*  Link_type; // 다음 노드
    Val                         M_value_field;
  };

  /* 
  * 증감 연산자에 사용되는 함수
  * RB_tree_increment, RB_tree_decrement
  */

  /* 
  * - RB_tree_increment는 node x를 탐색하는 iterator가 node x보다 하나 더 큰 node를 찾는다.
  *   - 오른쪽 자식이 있다면 오른쪽 자식에서 가장 왼쪽에 있는 node를 찾는다.
  *   - 자신 보다 큰 오른쪽 자식이 없다면 부모 node로 올라가고 자신이 부모의 오른쪽 자식이었는 지 확인한다.
  *     자기가 오른쪽 자식이었다면 다시 부모 node로 올라가 반복 작업을 하고, 왼쪽 자식이었다면 그대로 멈춘다.
  *   - 노드 삭제 과정에서 node x의 부모가 node x의 자식과 같게 되는 예외상황이 발생하는 데 이 때,
  *     부모 node로 올라가지 않는다.
  */
  RB_tree_node_base*
    RB_tree_increment(RB_tree_node_base* x)
  {
    if (x->M_right != 0)
    {
      x = x->M_right;
      while (x->M_left != 0)
        x = x->M_left;
    }
    else 
    {
      RB_tree_node_base* y = x->M_parent;
      while (x == y->M_right) 
      {
        x = y;
        y = y->M_parent;
      }
      /*
      *  예외처리: x가 header일 때를 위한 조건문
      */
      if (x->M_right != y) 
        x = y;
    }
    return x;
  }

  const RB_tree_node_base*
    RB_tree_increment(const RB_tree_node_base* x)
  {
    return RB_tree_increment(const_cast<RB_tree_node_base*>(x));
  }

  /* 
  * RB_tree_decrement
  * - RB_tree_decrement는 node x를 탐색하는 iterator가 node x보다 하나 더 작은 node를 찾는다.
  * - 가장 위에 있는 if문은 헤더와 노드한개가 있을 때 생기는 예외처리이다.(헤더는 새로운 노드를 자식과 동시에 부모로 삼는다)
  * - 만약 node x의 left가 존재하면 그 left node로 넘어간 후, 그 left node에서 가장 right에 있는
  *   값을 찾는다.
  * - 만약 node x의 left가 없다면, 부모로 올라가서 자신이 부모의 left node였는 지 확인하고,
  *   (i) 자기가 left node였다면, 부모의 부모로 올라가서 위를 다시 반복한다.
  *   (ii) 자기가 left node가 아니었다면, 그 부모를 return 한다.
  */
  RB_tree_node_base*
    RB_tree_decrement(RB_tree_node_base* x)
  {
    // x가 Header일 때 적용되는 상황 Header node에서 --를 할 때의 상황
    if (x->M_color == RED 
        && x->M_parent->M_parent == x)
      x = x->M_right;
    else if (x->M_left != 0) 
    {
      RB_tree_node_base* y = x->M_left;
      while (y->M_right != 0)
        y = y->M_right;
      x = y;
    }
    else 
    {
      RB_tree_node_base* y = x->M_parent;
      while (x == y->M_left) 
        {
          x = y;
          y = y->M_parent;
        }
      x = y;
    }
    return x;
  }

  const RB_tree_node_base*
    RB_tree_decrement(const RB_tree_node_base* x)
  {
    return RB_tree_decrement(const_cast<RB_tree_node_base*>(x));
  }

  template<typename T>
  struct RB_tree_iterator
  {
    typedef T     value_type;
    typedef T&    reference;
    typedef T*    pointer;

    typedef std::bidirectional_iterator_tag   iterator_category;
    typedef ptrdiff_t                         difference_type;

    typedef RB_tree_iterator<T>           Self;
    typedef RB_tree_node_base::Base_ptr   Base_ptr;
    typedef RB_tree_node<T>*              Link_type;

    RB_tree_iterator()
      : M_node() { }

    RB_tree_iterator(Link_type x)
      : M_node(x) { }

    reference
      operator*() const
    { return static_cast<Link_type>(M_node)->M_value_field; }

    pointer
      operator->() const
    { return &static_cast<Link_type>(M_node)->M_value_field; }

    Self&
      operator++()
    {
      M_node = RB_tree_increment(M_node);
      return *this;
    }

    Self
      operator++(int)
    {
      Self tmp = *this;
      M_node = RB_tree_increment(M_node);
      return tmp;
    }

    Self&
      operator--()
    {
      M_node = RB_tree_decrement(M_node);
      return *this;
    }

    Self
      operator--(int)
    {
      Self tmp = *this;
      M_node = RB_tree_decrement(M_node);
      return tmp;
    }

    bool operator==(const Self& x) const
    { return M_node == x.M_node; }

    bool operator!=(const Self& x) const
    { return M_node != x.M_node; }

    Base_ptr M_node;
  };

  template<typename T>
  struct RB_tree_const_iterator
  {
    typedef T                          value_type;
    typedef const T&                   reference;
    typedef const T*                   pointer;

    typedef RB_tree_iterator<T>                 iterator;

    typedef std::bidirectional_iterator_tag     iterator_category;
    typedef ptrdiff_t                           difference_type;

    typedef RB_tree_const_iterator<T>           Self;
    typedef RB_tree_node_base::Const_Base_ptr   Base_ptr;
    typedef const RB_tree_node<T>*              Link_type;

    RB_tree_const_iterator()
      : M_node() { }

    RB_tree_const_iterator(Link_type x)
      : M_node(x) { }

    RB_tree_const_iterator(const iterator& it)
      : M_node(it.M_node) { }

    reference
      operator*() const
    { return static_cast<Link_type>(M_node)->M_value_field; }

    pointer
      operator->() const
    { return &static_cast<Link_type>(M_node)->M_value_field; }

    Self&
      operator++()
    {
      M_node = RB_tree_increment(M_node);
      return *this;
    }

    Self
      operator++(int)
    {
      Self tmp = *this;
      M_node = RB_tree_increment(M_node);
      return tmp;
    }

    Self&
      operator--()
    {
      M_node = RB_tree_decrement(M_node);
      return *this;
    }

    Self
      operator--(int)
    {
      Self tmp = *this;
      M_node = RB_tree_decrement(M_node);
      return tmp;
    }

    bool
      operator==(const Self& x) const
    { return M_node == x.M_node; }

    bool
      operator!=(const Self& x) const
    { return M_node != x.M_node; }

    Base_ptr M_node;
  };

  template<typename Val>
  inline bool
    operator==(const RB_tree_iterator<Val>& x,
               const RB_tree_const_iterator<Val>& y)
  { return x.M_node == y.M_node; }

  template<typename Val>
  inline bool
    operator!=(const RB_tree_iterator<Val>& x,
               const RB_tree_const_iterator<Val>& y)
  { return x.M_node != y.M_node; }

  /*
  * RB_tree_rotate_left: Insert, Delete 시에 사용됨
  * 01. x의 오른쪽 자식 노드를 y에 저장한다.
  * 02. x의 오른쪽 자식노드를 B로 만든다.
  * 03. B의 부모노드를 x로 만드는 link를 연결한다.
  * 04. y의 부모노드를 현재 x부모노드로 할당한다.
  * 05. x의 부모노드가 NIL이라면, 즉 x가 root라면
  * 06. y를 root로 설정한다.
  * 07. 그렇지 않고 x의 부모노드가 존재한다면, 부모노드의 왼쪽 자식이었다면,
  * 08. y가 x의 부모노드의 왼쪽 자식노드가 되고
  * 09. 그렇지 않다면, y는 x의 부모노드의 오른쪽 자식이 된다.
  * 10. x가 y의 왼쪽 자식이 되게하고,
  * 11. y가 x의 부모노드가 되도록한다.
  **/
  void
    RB_tree_rotate_left(RB_tree_node_base* const x,
                        RB_tree_node_base*& root)
  {
    RB_tree_node_base* const y = x->M_right; // (01)

    x->M_right = y->M_left; // (02)
    if (y->M_left !=0)
      y->M_left->M_parent = x; // (03)
    y->M_parent = x->M_parent; // (04)

    if (x == root) // (05)
      root = y; // (06)
    else if (x == x->M_parent->M_left) // (07)
      x->M_parent->M_left = y; // (08)
    else
      x->M_parent->M_right = y; // (09)
    y->M_left = x; // (10)
    x->M_parent = y; // (11)
  }

  void
    RB_tree_rotate_right(RB_tree_node_base* const x,
                         RB_tree_node_base*& root)
  {
    RB_tree_node_base* const y = x->M_left;

    x->M_left = y->M_right;
    if (y->M_right != 0)
      y->M_right->M_parent = x;
    y->M_parent = x->M_parent;

    if (x == root)
      root = y;
    else if (x == x->M_parent->M_right)
      x->M_parent->M_right = y;
    else
      x->M_parent->M_left = y;
    y->M_right = x;
    x->M_parent = y;
  }

  void
    RB_tree_insert_and_rebalance(const bool insert_left,
                                 RB_tree_node_base* newNode,
                                 RB_tree_node_base* parent,
                                 RB_tree_node_base& header)
  {
    RB_tree_node_base *& root = header.M_parent;

    // Initialize fields in new node to insert.
    newNode->M_parent = parent;
    newNode->M_left = 0;
    newNode->M_right = 0;
    newNode->M_color = RED;

    // Insert.
    // Make new node child of parent and maintain root, leftmost and
    // rightmost nodes.
    // N.B. First node is always inserted left.
    if (insert_left)
    {
      parent->M_left = newNode; // also makes leftmost = newNode when parent == &header

      if (parent == &header)
      {
          header.M_parent = newNode;
          header.M_right = newNode;
      }
      else if (parent == header.M_left)
        header.M_left = newNode; // maintain leftmost pointing to min node
    }
    else
    {
      parent->M_right = newNode;

      if (parent == header.M_right)
        header.M_right = newNode; // maintain rightmost pointing to max node
    }

    /*                    삽입에서의 Rebalancing                     *\
    *  삽입에서의 Rebalancing은 Case 1, 2로 나뉜다.
    *  Case 1. 부모 노드가 레드인 데, 부모의 형제가 없거나 블랙일 때 => 회전
    *  Case 2. 부모 노드가 레드인 데, 부모의 형제가 레드일 때 => 색상 변환
    *  처리 이후, 다시한번 while문을 도는 데, 최악의 경우 O(log n)의 시간이 걸린다.
    *  xpp: GP(Grand parent)
    \*                                                            */
    while (newNode != root
	         && newNode->M_parent->M_color == RED)
    {
	    RB_tree_node_base* const xpp = newNode->M_parent->M_parent;

    	if (newNode->M_parent == xpp->M_left) // 본인의 부모가 xpp->M_left이고, 부모의 형제는 xpp->M_right이다.
  	  {
  	    RB_tree_node_base* const y = xpp->M_right; // y는 부모의 형제
  	    if (y && y->M_color == RED) // 부모의 형제까지 RED라면, ==> Case 2
	      {
          // 이 if문 안에서 부모와 부모의 형제는 RED인 상태이다.
          // 부모와 부모의 형제를 BLACK으로, 조부모를 RED로 바꿔준뒤
      		newNode->M_parent->M_color = BLACK;
      		y->M_color = BLACK;
      		xpp->M_color = RED;
      		newNode = xpp; // newNode에 부모를 넣어줘서 다시 while문을 돌려줘서 조부모의 윗세대도 정리해준다.
	      }
  	    else // 부모의 형제까지 BLACK이거나 부모의 형제가 없다면 ==> Case 1
	      {
  	    	if (newNode == newNode->M_parent->M_right) // 본인이 부모의 오른쪽 자식이라면
    		  {
    		    newNode = newNode->M_parent;
    		    RB_tree_rotate_left(newNode, root); // 부모를 기준으로 좌회전을 한다.
    		  }
          else
            newNode->M_parent->M_color = BLACK; // 부모의 색을 BLACK으로 만들고
      		xpp->M_color = RED; // 조부모의 색을 빨간색으로 바꿔준다.
      		RB_tree_rotate_right(xpp, root); // 조부모를 기준으로 우회전을 한다.
	      }
  	  }
    	else  // 본인의 부모가 xpp->M_right이고, 부모의 형제는 xpp->M_left이다.
  	  {
  	    RB_tree_node_base* const y = xpp->M_left; // y는 부모의 형제
  	    if (y && y->M_color == RED) // 부모의 형제의 색이 빨간색이라면 ==> Case 1
	      {
      		newNode->M_parent->M_color = BLACK; // 부모의 색을 검정색으로 칠하고
      		y->M_color = BLACK; // 부모의 형제 색을 검정색으로 칠한다.
      		xpp->M_color = RED; // 조부모의 색을 빨간색으로 칠하고
      		newNode = xpp; // 부모까지 밸런싱했으므로 조부모로 올라가서 다시 리밸런싱한다.
	      }
  	    else // 부모의 형제의 색이 검정색이라면, ==> Case 2
	      {
  	    	if (newNode == newNode->M_parent->M_left) // 본인이 부모의 왼쪽 자식이라면
    		  {
    		    newNode = newNode->M_parent;
    		    RB_tree_rotate_right(newNode, root); // 부모를 기준으로 우회전을 한다.
    		  }
          else // 본인이 부모의 오른쪽 자식이라면,
      		  newNode->M_parent->M_color = BLACK; // 부모의 색을 검정색으로 칠한다.
      		xpp->M_color = RED; // 조부모의 색을 빨간색으로 칠한다.
      		RB_tree_rotate_left(xpp, root); // 조부모를 기준으로 좌회전을 한다.
	      }
  	  }
    }
    root->M_color = BLACK;
  }

  // https://ict-nroo.tistory.com/73
  // successor 노드가 z 대신 삭제되고, z 노드는 successor 노드의 정보를 swap받는다.
  RB_tree_node_base*
    RB_tree_rebalance_for_erase(RB_tree_node_base* const z,
                                RB_tree_node_base& header)
  {
    RB_tree_node_base *& root = header.M_parent;
    RB_tree_node_base *& leftmost = header.M_left;
    RB_tree_node_base *& rightmost = header.M_right;
    RB_tree_node_base* y = z; // y가 successor가 된다
    RB_tree_node_base* x = 0;
    RB_tree_node_base* x_parent = 0;

    // 04 ~ 06 Successor 찾기 삭제 사전 작업
    // x가 중요한 이유는 y가 계승자가 되어 삭제되었을 때
    // y의 자식인 x가 미아상태가 되기 때문에 미리 저장해두고 처리하기 위함이다.
    /** 
     ** y의 왼쪽 자식이 NIL일 경우는
     ** x에 y의 오른쪽 자식을 저장한다.
     */
    if (y->M_left == 0)     // z has at most one non-null child. y == z.
      x = y->M_right;     // x might be null. // x가 successor가 되나?
    else // (04) y의 왼쪽 자식이 null이 아니라면,
    {
      /* 
      ** y의 오른쪽 자식이 NIL일 경우는
      ** x에 y의 왼쪽 자식을 저장한다.
      */
      if (y->M_right == 0)  // z has exactly one non-null child. y == z.
	      x = y->M_left;    // (05) y의 왼쪽 자식을 x로, x is not null.
      else
      {
        /* 
        ** y의 다음 순번 노드를 찾는 과정이다.
        ** y의 오른쪽 자식에서 가장 왼쪽에 있는 노드가 y가 되고,
        ** y에 오른쪽 자식이 있을 수도 있으므로 그 자식을 x로 저장한다.
        */
        // 여기서 z 얘기가 나오는 것은 아직까지는 y == z 이기 때문이다.
        // z has two non-null children.  Set y to
        y = y->M_right;   //   z's successor.  x might be null.
        while (y->M_left != 0)
          y = y->M_left;
        x = y->M_right; // (06) y의 오른쪽 자식을 x로 저장한다.
      }
    }
    
    /* (13) 삭제하려는 노드 대신 successor를 삭제한 경우, y와 z가 다르기 때문에
    **      successor y노드의 데이터를 카피해주는 작업이 필요하다
    **      조건문 y != z에서 y의 데이터들을 z노드로 copy해주는 작업을 한다.
    **      successor가 z의 값들을 받은 뒤 z대신 삭제된다.
    */
    if (y != z)
    {  
	    // relink y in place of z.  y is z's successor
    	z->M_left->M_parent = y;
    	y->M_left = z->M_left;
    	if (y != z->M_right)
  	  {
  	    x_parent = y->M_parent;
  	    if (x) x->M_parent = y->M_parent;
  	    y->M_parent->M_left = x;   // y must be a child of M_left
  	    y->M_right = z->M_right;
  	    z->M_right->M_parent = y;
  	  }
    	else
    	  x_parent = y;
    	if (root == z)
    	  root = y;
    	else if (z->M_parent->M_left == z)
    	  z->M_parent->M_left = y;
    	else
    	  z->M_parent->M_right = y;
    	y->M_parent = z->M_parent;
    	std::swap(y->M_color, z->M_color);
    	y = z;
    	// y now points to node to be actually deleted
    }
    else // Successor 필요없이 본인이 삭제되면 되는 상황
    {                        // y == z
    	x_parent = y->M_parent; // (07)
    	if (x)
    	  x->M_parent = y->M_parent; // (08)
    	if (root == z)
    	  root = x; // (09)
    	else
    	{
        if (z->M_parent->M_left == z)
    	    z->M_parent->M_left = x;
    	  else
    	    z->M_parent->M_right = x;
      }
      /*
      ** 만약 삭제될 노드 z가 Header에 기록된 leftmost or rightmost 였다면
      ** leftmost, rightmost를 Header에 갱신해야한다.
      */
	    if (leftmost == z)
      {
        if (z->M_right == 0)        // z->M_left must be null also
    	    leftmost = z->M_parent;
  	    else // makes leftmost == M_header if z == root
  	      leftmost = RB_tree_node_base::S_minimum(x);
      }
    	if (rightmost == z)
      {
        if (z->M_left == 0)         // z->M_right must be null also
          rightmost = z->M_parent; // makes rightmost == M_header if z == root
        else                      // x == z->M_left
          rightmost = RB_tree_node_base::S_maximum(x);
      }
    }

    /* 
      만약 x가 루트노드이거나, x가 레드노드이라면 x를 BLACK으로 만들어주고 종료한다
    */

    if (y->M_color != RED) // y가 BLACK이었을 경우(이중 흑색 노드)
    {
      /*                    삭제에서의 Rebalancing                     *\
      *  삽입에서의 Rebalancing은 Case 1, 2, 3, 4, 5, 6, 7, 8로 나뉜다.
      *  Case 1. x의 형제 노드 w가 RED인 경우
      *  Case 2. w가 BLACK, w의 왼쪽, 오른쪽 자식이 BLACK인 경우
      *  Case 3. w가 BLACK, w의 왼쪽 자식이 RED인 경우
      *  Case 4. w가 BLACK, w의 오른쪽 자식이 RED인 경우
      *  Case 5, 6, 7, 8. 은 Case 1,2,3,4의 대칭이다.
      *  xpp: GP(Grand parent), w: x의 uncle
      \*                                                            */
	    while (x != root && (x == 0 || x->M_color == BLACK))
      {
        if (x == x_parent->M_left) // 본인이 왼쪽일 때
  	    {
  	      RB_tree_node_base* w = x_parent->M_right; // w는 sibling
          /**
           * Case 1. w가 RED인 경우
           * 이 경우는 x의 자식노드가 BLACK 노드이다.
           * (1) w를 BLACK, p[x]를 RED
           * (2) p[x]에 대해 left-rotation.
           * (3) 이 때 w는 p[x]의 right가 되고, BLACK으로 칠한다. 이 때, p[x]가 RED로 된다.
           **/
  	      if (w->M_color == RED)
      		{
      		  w->M_color = BLACK; // sibling black
      		  x_parent->M_color = RED; // parent red (1)
      		  RB_tree_rotate_left(x_parent, root); // (2)
      		  w = x_parent->M_right;
      		}
          /**
           * Case 2. w가 BLACK, w의 왼쪽, 오른쪽 자식이 BLACK인 경우
           * (1) color[w] <- RED
           * (2) x <- p[x]
           * (3) 다시 while문
           **/
  	      if ((w->M_left == 0 ||
        		   w->M_left->M_color == BLACK) &&
        		  (w->M_right == 0 ||
        		   w->M_right->M_color == BLACK))
      		{
      		  w->M_color = RED; // (1)
      		  x = x_parent; // (2)
      		  x_parent = x_parent->M_parent; // (2)
            // (3) 다시 while문
      		}
	        else
		      {
            /**
             * Case 3. w가 BLACK, w의 오른쪽 자식이 BLACK인 경우
             * (1) w의 왼쪽자식을 BLACK
             * (2) w의 색을 RED
             * (3) w를 중심으로 우회전
             * (4) w는 x의 부모의 새로운 오른쪽 자식노드가 되고 색은 RED인 상태가 된다
             **/
      		  if (w->M_right == 0
      		      || w->M_right->M_color == BLACK)
    		    {
    		      w->M_left->M_color = BLACK; // (1)
    		      w->M_color = RED; // (2)
    		      RB_tree_rotate_right(w, root); // (3)
    		      w = x_parent->M_right; // (4)
    		    }
            /**
             * Case 4. w가 BLACK, w의 오른쪽 자식이 RED인 경우
             * (5) left-rotate 대상인 두 노드의 색을 서로 교환
             * (6) w의 오른쪽 자식 노드의 색을 BLACK
             * (7) p[x]를 기준으로 left-rotate한다.
             **/
      		  w->M_color = x_parent->M_color; // (5)
      		  x_parent->M_color = BLACK; // (5)
      		  if (w->M_right)
      		    w->M_right->M_color = BLACK; // (6)
      		  RB_tree_rotate_left(x_parent, root); // (7)
      		  break;
      		}
        }
        else
        {
          // x가 오른쪽일 때
          RB_tree_node_base* w = x_parent->M_left; // sibling은 왼쪽
          /**
           * Case 5. w가 RED인 경우
           * 이 경우는 x의 자식노드가 BLACK 노드이다.
           * (1) w를 BLACK, p[x]를 RED
           * (2) p[x]에 대해 right-rotation.
           * (3) 이 때 w는 p[x]의 left가 되고, BLACK으로 칠한다. 이 때, p[x]가 RED로 된다.
           **/
          if (w->M_color == RED)
          {
            w->M_color = BLACK; // (1)
            x_parent->M_color = RED; // (1)
            RB_tree_rotate_right(x_parent, root); // (2)
            w = x_parent->M_left; // (3)
          }
          /**
           * Case 6. w가 BLACK, w의 왼쪽, 오른쪽 자식이 BLACK인 경우
           * (1) color[w] <- RED
           * (2) x <- p[x]
           * (3) 다시 while문
           **/
          if ((w->M_right == 0 ||
              w->M_right->M_color == BLACK) &&
              (w->M_left == 0 ||
              w->M_left->M_color == BLACK))
          {
            w->M_color = RED; // (1)
            x = x_parent; // (2)
            x_parent = x_parent->M_parent; // (2)
          }
          else
          {
            /**
             * Case 7. w가 BLACK, w의 왼쪽 자식이 BLACK인 경우
             * (1) w의 오른쪽자식을 BLACK
             * (2) w의 색을 RED
             * (3) w를 중심으로 좌회전
             * (4) w는 x의 부모의 새로운 왼쪽 자식노드가 되고 색은 RED인 상태가 된다
             **/
            if (w->M_left == 0 || w->M_left->M_color == BLACK)
            {
              w->M_right->M_color = BLACK; // (1)
              w->M_color = RED; // (2)
              RB_tree_rotate_left(w, root); // (3)
              w = x_parent->M_left; // (4)
            }
            /**
             * Case 8. w가 BLACK, w의 왼쪽 자식이 RED인 경우
             * (5) right-rotate 대상인 w와 p[x] 색을 서로 교환
             * (6) w의 오른쪽 자식 노드의 색을 BLACK
             * (7) p[x]를 기준으로 left-rotate한다.
             **/
            w->M_color = x_parent->M_color; // (5)
            x_parent->M_color = BLACK; // (5)
            if (w->M_left)
              w->M_left->M_color = BLACK; // (6)
            RB_tree_rotate_right(x_parent, root); // (7)
            break;
          }
        }
	    }
    	if (x) x->M_color = BLACK;
    }
    return y;
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc = std::allocator<Val> >
  class RB_tree
  {
    typedef typename Alloc::template rebind<RB_tree_node<Val> >::other
            Node_allocator;

  protected:
    typedef RB_tree_node_base*        Base_ptr;
    typedef const RB_tree_node_base*  Const_Base_ptr;
    typedef RB_tree_node<Val>         RB_tree_node;

  public:
    typedef Key                       key_type;
    typedef Val                       value_type;
    typedef value_type*               pointer;
    typedef const value_type*         const_pointer;
    typedef value_type&               reference;
    typedef const value_type&         const_reference;
    typedef RB_tree_node*             Link_type;
    typedef const RB_tree_node*       Const_Link_type;
    typedef size_t                    size_type;
    typedef ptrdiff_t                 difference_type;
    typedef Alloc                     allocator_type;

    Node_allocator&
      M_get_Node_allocator()
    { return *static_cast<Node_allocator*>(&this->M_impl); }

    const Node_allocator&
      M_get_Node_allocator() const
    { return *static_cast<const Node_allocator*>(&this->M_impl); }

    allocator_type
      get_allocator() const
    { return allocator_type(M_get_Node_allocator()); }

  protected:
    RB_tree_node*
      M_get_node()
    { return M_impl.Node_allocator::allocate(1); }

    void
      M_put_node(RB_tree_node* p)
    { M_impl.Node_allocator::deallocate(p, 1); }

    Link_type
      M_create_node(const value_type& x)
    {
      Link_type tmp = M_get_node();
      get_allocator().construct(&tmp->M_value_field, x);
      return tmp;
    }

    Link_type
      M_clone_node(Const_Link_type x)
    {
      Link_type tmp = M_create_node(x->M_value_field);
      tmp->M_color = x->M_color;
      tmp->M_left = 0;
      tmp->M_right = 0;
      return tmp;
    }

    void
      M_destroy_node(Link_type p)
    {
      get_allocator().destroy(&p->M_value_field);
      M_put_node(p);
    }

  protected:
    template<typename Key_compare,
             bool Is_pod_comparator = std::is_pod<Key_compare>::value>
    struct RB_tree_impl : public Node_allocator
    {
      Key_compare         M_key_compare;
      RB_tree_node_base   M_header;
      size_type           M_node_count; // keeps track of size of tree.

      RB_tree_impl()
      : Node_allocator(), M_key_compare(), M_header(), M_node_count(0)
      {
        this->M_header.M_color = RED;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }

      RB_tree_impl(const Node_allocator& comp, const Key_compare& a)
        : Node_allocator(a), M_key_compare(comp), M_header(), M_node_count(0)
      {
        this->M_header.M_color = RED;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }
    };

    // Specialization for Comparision types that are not capable of
    // being base classes / super classes.
    template<typename Key_compare>
    struct RB_tree_impl<Key_compare, true> : public Node_allocator
    {
      Key_compare         M_key_compare;
      RB_tree_node_base   M_header;
      size_type           M_node_count; // Keeps track of size of tree.

      RB_tree_impl()
      : Node_allocator(), M_key_compare(), M_header(), M_node_count(0)
      {
        this->M_header.M_color = RED;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }

      RB_tree_impl(const Key_compare& comp, const Node_allocator& a)
      : Node_allocator(a), M_key_compare(comp), M_header(), M_node_count(0)
      {
        this->M_header.M_color = RED;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }
    };

  private:
    RB_tree_impl<Compare> M_impl;

  protected:
    Base_ptr&
      M_root()
    { return this->M_impl.M_header.M_parent; }

    Const_Base_ptr
      M_root() const
    { return this->M_impl.M_header.M_parent; }

    Base_ptr&
      M_leftmost()
    { return this->M_impl.M_header.M_left; }

    Const_Base_ptr
      M_leftmost() const
    { return this->M_impl.M_header.M_left; }

    Base_ptr&
      M_rightmost()
    { return this->M_impl.M_header.M_right; }

    Const_Base_ptr
      M_rightmost() const
    { return this->M_impl.M_header.M_right; }

    Link_type
      M_begin()
    { return static_cast<Link_type>(this->M_impl.M_header.M_parent); }

    Const_Link_type
      M_begin() const
    { return static_cast<Const_Link_type>(this->M_impl.M_header.M_parent); }

    Link_type
      M_end()
    { return static_cast<Link_type>(&this->M_impl.M_header); }

    Const_Link_type
      M_end() const
    { return static_cast<Const_Link_type>(&this->M_impl.M_header); }

    // pair에서 value를 반환
    static const_reference
      S_value(Const_Link_type x)
    { return x->M_value_field; }

    static const Key&
      S_key(Const_Link_type x)
    { return KeyOfValue()(S_value(x)); }

    static Link_type
      S_left(Base_ptr x)
    { return static_cast<Link_type>(x->M_left); }

    static Const_Link_type
      S_left(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x->M_left); }

    static Link_type
      S_right(Base_ptr x)
    { return static_cast<Link_type>(x->M_right); }

    static Const_Link_type
      S_right(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x->M_right); }

    static const_reference
      S_value(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x)->M_value_field; }

    static const Key&
      S_key(Const_Base_ptr x)
    { return KeyOfValue()(S_value(x)); }

    static Base_ptr
      S_minimum(Base_ptr x)
    { return RB_tree_node_base::S_minimum(x); }

    static Const_Base_ptr
      S_minimum(Const_Base_ptr x)
    { return RB_tree_node_base::S_minimum(x); }

    static Base_ptr
      S_maximum(Base_ptr x)
    { return RB_tree_node_base::S_maximum(x); }

    static Const_Base_ptr
      S_maximum(Const_Base_ptr x)
    { return RB_tree_node_base::S_maximum(x); }

  public:
    typedef RB_tree_iterator<value_type>       iterator;
    typedef RB_tree_const_iterator<value_type> const_iterator;

    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
    iterator
      M_insert(Base_ptr x, Base_ptr y, const value_type& v);

    iterator
      M_insert_lower(Base_ptr x, Base_ptr y, const value_type& v);

    const_iterator
      M_insert(Const_Base_ptr x, Const_Base_ptr y, const value_type& v);
    
    Link_type
      M_copy(Const_Link_type x, Link_type p);

    void
      M_erase(Link_type x);

  public:
    // allocation/deallocation
    RB_tree()
    { }

    // LLVM LOCAL begin mainline 129013
    RB_tree(const Compare& comp,
            const allocator_type& a = allocator_type())
    : M_impl(comp, a)
    { }

    RB_tree(const RB_tree& x)
    {
    	if (x.M_root() != 0)
  	  {
  	    M_root() = M_copy(x.M_begin(), M_end());
  	    M_leftmost() = S_minimum(M_root());
  	    M_rightmost() = S_maximum(M_root());
  	    M_impl.M_node_count = x.M_impl.M_node_count;
  	  }
    }

    /* map에 소멸자가 없는 이유가 map은 껍데기일 뿐이고, 
       알맹이인 tree에서 소멸시켜주기 때문 */
    ~RB_tree()
    { M_erase(M_begin()); }

    RB_tree&
      operator=(const RB_tree& x)
    {
      if (this != &x)
      {
        clear(); // 기존 데이터 삭제
        M_impl.M_key_compare = x.M_impl.M_key_compare;
        if (x.M_root() != 0)
        {
          M_root() = M_copy(x.M_begin(), M_end());
          M_leftmost() = S_minimum(M_root());
          M_rightmost() = S_maximum(M_root());
          M_impl.M_node_count = x.M_impl.M_node_count;
        }
      }
      return *this;
    }

    // Accessors.
    Compare
      key_comp() const
    { return M_impl.M_key_compare; }

    iterator
      begin()
    { return static_cast<Link_type>(this->M_impl.M_header.M_left); }

    const_iterator
      begin() const
    { return static_cast<Const_Link_type>(this->M_impl.M_header.M_left); }

    iterator
      end()
    { return static_cast<Link_type>(&this->M_impl.M_header); }

    const_iterator
      end() const
    { return static_cast<Const_Link_type>(&this->M_impl.M_header); }

    reverse_iterator
      rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator
      rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator
      rend()
      { return reverse_iterator(begin()); }

    const_reverse_iterator
      rend() const
      { return const_reverse_iterator(begin()); }

    bool
      empty() const
    { return M_impl.M_node_count == 0; }

    size_type
      size() const
    { return M_impl.M_node_count; }

    size_type
      max_size() const
    { return get_allocator().max_size(); }

    void
      swap(RB_tree& t);

    // Insert/erase.
    ft::pair<iterator,bool>
      M_insert_unique(const value_type& x);

    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // 233. Insertion hints in associative containers.
    
    iterator
      M_insert_unique(iterator position, const value_type& x);

    const_iterator
      M_insert_unique(const_iterator position, const value_type& x);

    template<typename InputIterator>
    void
      M_insert_unique(InputIterator first, InputIterator last);

    void
      erase(iterator position);

    void
      erase(const_iterator position);

    size_type
      erase(const key_type& x);

    void
      erase(iterator first, iterator last);

    void
      erase(const_iterator first, const_iterator last);

    void
      erase(const key_type* first, const key_type* last);

    void
      clear()
    {
      M_erase(M_begin());
      M_leftmost() = M_end();
      M_root() = 0;
      M_rightmost() = M_end();
      M_impl.M_node_count = 0;
    }

    // Set operations.
    iterator
      find(const key_type& x);

    const_iterator
      find(const key_type& x) const;

    size_type
      count(const key_type& x) const;

    iterator
      lower_bound(const key_type& x);

    const_iterator
      lower_bound(const key_type& x) const;

    iterator
      upper_bound(const key_type& x);

    const_iterator
      upper_bound(const key_type& x) const;

    ft::pair<iterator,iterator>
      equal_range(const key_type& x);

    ft::pair<const_iterator, const_iterator>
      equal_range(const key_type& x) const;
  };
  

  // p는 parent, Base_ptr에 0을 넣으면 insert_left를 0으로 하려는 의도다.
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_insert(Base_ptr x, Base_ptr p, const Val& v)
  {
    Link_type z = M_create_node(v);
    bool insert_left;

    insert_left = x != 0 || p == M_end()
                         || M_impl.M_key_compare(KeyOfValue()(v),
					                                       S_key(p));

    RB_tree_insert_and_rebalance(insert_left, z, p,
			                           this->M_impl.M_header); // v가 안들어가네?->새로운 z노드안에 있음
    ++M_impl.M_node_count;
    return iterator(z);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_insert_lower(Base_ptr x, Base_ptr p, const Val& v)
  {
    bool insert_left = (x != 0 || p == M_end()
                        || !M_impl.M_key_compare(S_key(p),
                                                 KeyOfValue()(v)));

    Link_type z = M_create_node(v);

    RB_tree_insert_and_rebalance(insert_left, z, p,  
                                 this->M_impl.M_header);
    ++M_impl.M_node_count;
    return iterator(z);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::const_iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_insert(Const_Base_ptr x, Const_Base_ptr p, const Val& v)
  {
    bool insert_left = (x != 0 || p == M_end()
                        || M_impl.M_key_compare(KeyOfValue()(v), 
                                                S_key(p)));

    Link_type z = M_create_node(v);

    RB_tree_insert_and_rebalance(insert_left, z,
                                 const_cast<Base_ptr>(p),  
                                 this->M_impl.M_header);
    ++M_impl.M_node_count;
    return const_iterator(z);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  swap(RB_tree<Key,Val,KeyOfValue,Compare,Alloc>& t)
  {
    if (M_root() == 0)
    {
    	if (t.M_root() != 0)
    	{
    	  M_root() = t.M_root();
    	  M_leftmost() = t.M_leftmost();
    	  M_rightmost() = t.M_rightmost();
        M_root()->M_parent = M_end();

    	  t.M_root() = 0;
    	  t.M_leftmost() = t.M_end();
    	  t.M_rightmost() = t.M_end();
    	}
    }
    else if (t.M_root() == 0)
    {
    	t.M_root() = M_root();
    	t.M_leftmost() = M_leftmost();
    	t.M_rightmost() = M_rightmost();
      t.M_root()->M_parent = t.M_end();

    	M_root() = 0;
    	M_leftmost() = M_end();
    	M_rightmost() = M_end();
    }
    else
    {
    	std::swap(M_root(),t.M_root());
    	std::swap(M_leftmost(),t.M_leftmost());
    	std::swap(M_rightmost(),t.M_rightmost());

    	M_root()->M_parent = M_end();
    	t.M_root()->M_parent = t.M_end();
    }
    // No need to swap header's color as it does not change.
    std::swap(this->M_impl.M_node_count, t.M_impl.M_node_count);
    std::swap(this->M_impl.M_key_compare, t.M_impl.M_key_compare);

  }

  // std::map::insert
  // single element (1) pair<iterator, bool> insert(const value_type& val);
  // Compare는 map에서 default값으로 std::less로 되어있다. (오름차순으로 정렬)
  // 가장 기본적인 insert로 iterator 처음부터 v값이 들어갈 곳을 찾는다.
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  ft::pair<typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator,
                    bool>
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_insert_unique(const Val& v)
  {
    Link_type _begin = M_begin(); // Link_type -> node_ptr
    Link_type _end = M_end();
    bool _comp = true;
    while (_begin != NULL)
  	{
  	  _end = _begin;
  	  _comp = M_impl.M_key_compare(KeyOfValue()(v), S_key(_begin));
  	  _begin = _comp ? S_left(_begin) : S_right(_begin);
  	}
    iterator _tmp = iterator(_end);
    if (_comp)
    {
      if (_tmp == begin())
        return ft::pair<iterator,bool>(M_insert(_begin, _end, v), true);
      else
        --_tmp;
    }
    if (M_impl.M_key_compare(S_key(_tmp.M_node), KeyOfValue()(v)))
      return ft::pair<iterator,bool>(M_insert(_begin, _end, v), true);
    return ft::pair<iterator,bool>(_tmp, false); // 이미 동일한 v값이 있어 false로 pair를 리턴한다.
  }

  // std::map::insert
  // with hint (2) iterator insert(iterator position, const value_type& val);
  // Compare의 default는 std::less
  // 최대한 position 앞, 뒤로 v값의 적절한 위치를 찾고 앞, 뒤에도 없으면 최적화 의미 없이 노가다로 삽입할 곳 찾는다.
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_insert_unique(iterator position, const Val& v)
  {
    // 주어진 position이 끝 iterator 였다면? 맨 앞이거나, 맨 뒤일 것이다.
    if (position.M_node == M_end())
	  {
	    if (size() > 0 // tree가 비어있지 않고
	        && M_impl.M_key_compare(S_key(M_rightmost()), 
					                        KeyOfValue()(v))) // v의 값이 트리에서 가장 큰값이라면
	      return M_insert(0, M_rightmost(), v); // 0을 넣으면 트리의 오른쪽에 새 노드를 넣는다.
        // 트리에 새로운 가장 큰 값이 들어가므로 예전 큰 값을 부모로해서 예전 큰 값의 오른쪽 자식으로 새 노드가 들어간다.
  	  else // First argument just needs to be non-null.
	      return M_insert_unique(v).first; // tree가 비어있거나 position이 더 큰 경우(최적화 도움안됨)
	  }
    else if (M_impl.M_key_compare(KeyOfValue()(v),
				                          S_key(position.M_node))) // v < position
	  {
	    // First, try before...
      iterator before = position;
      if (position.M_node == M_leftmost()) // begin()
        return M_insert(M_leftmost(), M_leftmost(), v); // 가장 왼쪽에 있는 케이스일 때
      else if (M_impl.M_key_compare(S_key((--before).M_node), 
                                          KeyOfValue()(v))) // position의 이전 노드 < v
      {
        if (S_right(before.M_node) == 0) // 이전 노드의 오른쪽 노드 자리가 비었을 때
          return M_insert(0, before.M_node, v);
        else
          return M_insert(position.M_node,
                          position.M_node, v); // 그게 아니라면, position의 왼쪽 자식에 넣는다.
      }
      else
        return M_insert_unique(v).first; // 기존 노가다 방식
  	}
    else if (M_impl.M_key_compare(S_key(position.M_node),
				                          KeyOfValue()(v))) // position < v 일 때
    {
      iterator after = position;
      if (position.M_node == M_rightmost()) // position이 가장 오른쪽이면,
        return M_insert(0, M_rightmost(), v);
      else if (M_impl.M_key_compare(KeyOfValue()(v),
                                    S_key((++after).M_node))) // v < ++after
      {
        if (S_right(position.M_node) == 0) // position의 오른쪽 자식이 비었다면
          return M_insert(0, position.M_node, v);
        else
          return M_insert(after.M_node, after.M_node, v);
      }
      else // Position 근처에 없다면, 노가다
        return M_insert_unique(v).first;
    }
    else
      return position; // Equivalent keys.
  }

  // std::map::insert
  // with hint (2) iterator insert(const_iterator position, const value_type& val);
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::const_iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_insert_unique(const_iterator position, const Val& v)
  {
    // end()
    if (position.M_node == M_end())
    {
      if (size() > 0
          && M_impl.M_key_compare(S_key(M_rightmost()), 
                                  KeyOfValue()(v)))
        return M_insert(0, M_rightmost(), v);
      else
        return const_iterator(M_insert_unique(v).first);
    }
    else if (M_impl.M_key_compare(KeyOfValue()(v),
                                  S_key(position.M_node)))
    {
      // First, try before...
      const_iterator before = position;
      if (position.M_node == M_leftmost()) // begin()
        return M_insert(M_leftmost(), M_leftmost(), v);
      else if (M_impl.M_key_compare(S_key((--before).M_node), 
              KeyOfValue()(v)))
        {
          if (S_right(before.M_node) == 0)
            return M_insert(0, before.M_node, v);
          else
            return M_insert(position.M_node,
          position.M_node, v);
        }
      else
        return const_iterator(M_insert_unique(v).first);
    }
    else if (M_impl.M_key_compare(S_key(position.M_node),
				                          KeyOfValue()(v)))
    {
      // ... then try after.
      const_iterator after = position;
      if (position.M_node == M_rightmost())
        return M_insert(0, M_rightmost(), v);
      else if (M_impl.M_key_compare(KeyOfValue()(v),
                                    S_key((++after).M_node)))
      {
        if (S_right(position.M_node) == 0)
          return M_insert(0, position.M_node, v);
        else
          return M_insert(after.M_node, after.M_node, v);
      }
      else
        return const_iterator(M_insert_unique(v).first);
    }
    else
	    return position; // Equivalent keys.
  }

  // std::map::insert
  // range (3) template<class InputIterator>
  //           void insert(InputIterator first, InputIterator last);
  template<typename Key, typename Val, typename KoV,
           typename Cmp, typename Alloc>
  template<class II>
  void
    RB_tree<Key,Val,KoV,Cmp,Alloc>::
    M_insert_unique(II first, II last)
  {
    for ( ; first != last; ++first)
      M_insert_unique(end(), *first);
  }

  //4
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  inline void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::erase(iterator position)
  {
    Link_type y =
      static_cast<Link_type>(RB_tree_rebalance_for_erase(position.M_node,
						                                             this->M_impl.M_header));
    M_destroy_node(y);
    --M_impl.M_node_count;
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  inline void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
    erase(const_iterator position)
  {
    Link_type y =
      static_cast<Link_type>(
        RB_tree_rebalance_for_erase(
                                    const_cast<Base_ptr>(position.M_node),
                                                        this->M_impl.M_header));
    M_destroy_node(y);
    --M_impl.M_node_count;
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::size_type
  RB_tree<Key, Val, KeyOfValue, Compare, Alloc>::
  erase(const Key& x)
  {
    ft::pair<iterator, iterator> p = equal_range(x);
    const size_type old_size = size();
    erase(p.first, p.second);
    return old_size - size();
  }

  template<typename Key, typename Val, typename KoV,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val, KoV, Compare, Alloc>::Link_type
  RB_tree<Key,Val,KoV,Compare,Alloc>::
  M_copy(Const_Link_type x, Link_type p)
  {
    // Structural copy.  x and p must be non-null.
    Link_type top = M_clone_node(x);
    top->M_parent = p;

    if (x->M_right)
      top->M_right = M_copy(S_right(x), top);
    p = top;
    x = S_left(x);

    while (x != 0)
    {
      Link_type y = M_clone_node(x);
      p->M_left = y;
      y->M_parent = p;
      if (x->M_right)
        y->M_right = M_copy(S_right(x), y);
      p = y;
      x = S_left(x);
    }

    return top;
  }

  //5
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  M_erase(Link_type x)
  {
    // Erase without rebalancing.
    while (x != 0)
  	{
  	  M_erase(S_right(x));
  	  Link_type y = S_left(x);
  	  M_destroy_node(x);
  	  x = y;
  	}
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  erase(iterator first, iterator last)
  {
    if (first == begin() && last == end())
	    clear();
    else
	    while (first != last) erase(first++);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  erase(const_iterator first, const_iterator last)
  {
    if (first == begin() && last == end())
	    clear();
    else
	    while (first != last) erase(first++);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  void
    RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  erase(const Key* first, const Key* last)
  {
    while (first != last) erase(*first++);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  find(const Key& k)
  {
    Link_type x = M_begin(); // Current node.
    Link_type y = M_end(); // Last node which is not less than k.

    while (x != 0)
    {
      if (!M_impl.M_key_compare(S_key(x), k))
        y = x, x = S_left(x);
      else
        x = S_right(x);
    }

    iterator j = iterator(y);
    return (j == end()
            || M_impl.M_key_compare(k, S_key(j.M_node))) ? end() : j;
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::const_iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  find(const Key& k) const
  {
    Const_Link_type x = M_begin(); // Current node.
    Const_Link_type y = M_end(); // Last node which is not less than k.

    while (x != 0)
    {
	    if (!M_impl.M_key_compare(S_key(x), k))
	      y = x, x = S_left(x);
	    else
	      x = S_right(x);
    }
    const_iterator j = const_iterator(y);
    return (j == end()
	          || M_impl.M_key_compare(k, S_key(j.M_node))) ? end() : j;
  }

  //6
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::size_type
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  count(const Key& k) const
  {
    ft::pair<const_iterator, const_iterator> p = equal_range(k);
    const size_type n = std::distance(p.first, p.second);
    return n;
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  lower_bound(const Key& k)
  {
    Link_type x = M_begin(); // Current node.
    Link_type y = M_end(); // Last node which is not less than k.

    while (x != 0)
      if (!M_impl.M_key_compare(S_key(x), k))
        y = x, x = S_left(x);
      else
        x = S_right(x);

    return iterator(y);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::const_iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  lower_bound(const Key& k) const
  {
    Const_Link_type x = M_begin(); // Current node.
    Const_Link_type y = M_end(); // Last node which is not less than k.

    while (x != 0)
    {
      if (!M_impl.M_key_compare(S_key(x), k))
        y = x, x = S_left(x);
      else
        x = S_right(x);
    }

    return const_iterator(y);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  upper_bound(const Key& k)
  {
    Link_type x = M_begin(); // Current node.
    Link_type y = M_end(); // Last node which is greater than k.

    while (x != 0)
    {
      if (M_impl.M_key_compare(k, S_key(x)))
        y = x, x = S_left(x);
      else
        x = S_right(x);
    }

    return iterator(y);
  }

  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::const_iterator
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  upper_bound(const Key& k) const
  {
    Const_Link_type x = M_begin(); // Current node.
    Const_Link_type y = M_end(); // Last node which is greater than k.

    while (x != 0)
    {
      if (M_impl.M_key_compare(k, S_key(x)))
    	  y = x, x = S_left(x);
    	else
    	  x = S_right(x);
    }

    return const_iterator(y);
  }
  //7
  template<typename Key, typename Val, typename KeyOfValue,
           typename Compare, typename Alloc>
  inline
  ft::pair<typename RB_tree<Key,Val,KeyOfValue,
		                    Compare,Alloc>::iterator,
           typename RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::iterator>
  RB_tree<Key,Val,KeyOfValue,Compare,Alloc>::
  equal_range(const Key& k)
  { return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }

  template<typename Key, typename Val, typename KoV,
           typename Compare, typename Alloc>
  inline
  ft::pair<typename RB_tree<Key, Val, KoV,
		                    Compare, Alloc>::const_iterator,
	         typename RB_tree<Key, Val, KoV, Compare, Alloc>::const_iterator>
  RB_tree<Key, Val, KoV, Compare, Alloc>::
  equal_range(const Key& k) const
  { return ft::pair<const_iterator, const_iterator>(lower_bound(k),
					                                          upper_bound(k)); }

  unsigned int
    RB_tree_black_count(const RB_tree_node_base* node,
                        const RB_tree_node_base* root)
  {
    if (node == 0)
      return 0;

    unsigned int sum = 0;
    do
    {
    	if (node->M_color == BLACK)
    	  ++sum;
    	if (node == root)
    	  break;
    	node = node->M_parent;
    } while (1);

    return sum;
  }
}

#include "tree_inline_operator.tcc"

#endif