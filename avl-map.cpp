#include "avl-map.h"

#include <iostream>
#include <algorithm>

// static data members
template< typename KEY_TYPE, typename VALUE_TYPE >
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::end_it = CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator(nullptr);

template< typename KEY_TYPE, typename VALUE_TYPE >
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::const_end_it = CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const(nullptr);

template<typename KEY_TYPE, typename VALUE_TYPE>
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::Node
(KEY_TYPE k, VALUE_TYPE val, Node * p, int h, int b, Node * l, Node * r) :
  key(k),
  value(val),
  height(h),
  balance(b),
  parent(p),
  left(l),
  right(r)
{

}
template<typename KEY_TYPE, typename VALUE_TYPE>
KEY_TYPE const & CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::Key() const
{
  return key;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
VALUE_TYPE & CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::Value()
{
  return value;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::first()
{
  Node *temp = this;
  while (temp->left)
  {
    temp = temp->left; // left or right value depending on first or last
  }
  return temp;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::last()
{
  Node *temp = this;
  while (temp->right)
  {
    temp = temp->right; // left or right value depending on first or last
  }
  return temp;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::decrement()
{
  Node *temp = this;
  if (left)
  {
    temp = left;
    while (temp->right)
    {
      temp = temp->right;
    }
    //std::cout << "Predecessor is: " << temp->key << std::endl;
    return temp;
  }
  else
  {
    if (!parent)
    {
      return nullptr;
    }
    while (temp->parent->right != temp)
    {
      //std::cout << "Comparing: " << temp->parent->right->key << " to " << temp->key << std::endl;
      temp = temp->parent;
      if (!temp->parent)
      {
        return nullptr;
      }
    }
  }
  //std::cout << "Predecessor is: " << temp->parent->key << std::endl;
  return temp->parent;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * 
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node::increment()
{
  Node *temp = this;
  if (right)
  {
    temp = right;
    while (temp->left)
    {
      temp = temp->left;
    }
    //std::cout << "Predecessor is: " << temp->key << std::endl;
    return temp;
  }
  else
  {
    if (!parent)
    {
      return nullptr;
    }
    while (temp->parent->left != temp)
    {
      //std::cout << "Comparing: " << temp->parent->right->key << " to " << temp->key << std::endl;
      temp = temp->parent;
      if (!temp->parent)
      {
        return nullptr;
      }
    }
  }
  //std::cout << "Predecessor is: " << temp->parent->key << std::endl;
  return temp->parent;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::AVLmap_iterator(Node * p) :
  p_node(p)
{
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator &
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator=
(const typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator & rhs)
{
  if (*this == rhs)
  {
    return *this;
  }

  p_node = rhs.p_node;
  return *this;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator &
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator++()
{
  p_node = p_node->increment();

  return *this;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator++(int)
{
  AVLmap_iterator temp = *this;

  p_node = p_node->increment();

  return temp;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node &
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator*()
{
  return *p_node;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator->()
{
  return p_node;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
bool CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator!=
(const typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator & rhs)
{
  if (p_node != rhs.p_node)
  {
    return true;
  }
  return false;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
bool CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator::operator==
(const typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator & rhs)
{
  if (p_node == rhs.p_node)
  {
    return true;
  }
  return false;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::AVLmap_iterator_const
(typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * p) :
  p_node(p)
{
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const &
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator=
(const typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const & rhs)
{
  if (*this == rhs)
  {
    return *this;
  }

  p_node = rhs.p_node;
  return *this;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const &
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator++()
{
  p_node = p_node->increment();

  return *this;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator++(int)
{
  AVLmap_iterator_const temp = *this;

  p_node = p_node->increment();

  return temp;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node const &
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator*()
{
  return *p_node;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node const *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator->()
{
  return p_node;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
bool CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator!=(const AVLmap_iterator_const & rhs)
{
  if (rhs.p_node != p_node)
  {
    return true;
  }
  return false;
}
template<typename KEY_TYPE, typename VALUE_TYPE>
bool CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const::operator==
(const typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const & rhs)
{
  if (rhs.p_node == p_node)
  {
    return true;
  }
  return false;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap() :
  pRoot(nullptr),
  size_(0)
{
}

//in implementation file 
//method's name and return value have to be fully qualified with
//all required namespace and class names (like CS280::AVLmap<KEY_TYPE,VALUE_TYPE>::AVLmap)
//but the argument list does not have to be:
//function argument list automatically falls into the method's namespace (Koenig lookup)
template< typename KEY_TYPE, typename VALUE_TYPE >
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap(const AVLmap& rhs)
{
  pRoot = copy_rec(rhs.pRoot);
}

template<typename KEY_TYPE, typename VALUE_TYPE>
CS280::AVLmap<KEY_TYPE, VALUE_TYPE> & CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::operator=(const AVLmap & rhs)
{
  deleteAllTheThings_rec(pRoot);

  pRoot = copy_rec(rhs.pRoot);
  return *this;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::~AVLmap()
{
  deleteAllTheThings_rec(pRoot);
}

template<typename KEY_TYPE, typename VALUE_TYPE>
unsigned int CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::size()
{
  return size_;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
VALUE_TYPE & CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::operator[](KEY_TYPE const & key)
{
  Node *temp = find_rec(key, pRoot);

  if (!temp)
  {
    insert_rec(key, VALUE_TYPE(), pRoot, temp);
    if (!pRoot)
    {
      pRoot = temp;
    }
  }
  return temp->value;
}

////////////////////////////////////////////////////////////
// typename is used to help compiler to parse
template< typename KEY_TYPE, typename VALUE_TYPE >
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::begin()
{
  if (pRoot) return AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator(pRoot->first());
  else       return end_it;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::end()
{
  return end_it;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::find(KEY_TYPE const & key)
{
  return AVLmap_iterator(find_rec(key, pRoot));
}

template<typename KEY_TYPE, typename VALUE_TYPE>
void CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::erase
(typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator it)
{
  erase_rec(pRoot, it->key);
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::begin() const
{
  if (pRoot) return AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const(pRoot->first());
  else       return const_end_it;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::end() const
{
  return const_end_it;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::AVLmap_iterator_const
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::find(KEY_TYPE const & key) const
{
  return AVLmap_iterator_const(find_rec(key, pRoot));
}







////////////////////////////////////////////////////////////
// do not change this code from here to the end of the file
/* figure out whether node is left or right child or root
 * used in print_backwards_padded
 */
template< typename KEY_TYPE, typename VALUE_TYPE >
char CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::getedgesymbol(const Node* node) const {
  const Node* parent = node->parent;
  if (parent == nullptr) return '-';
  else                 return (parent->left == node) ? '\\' : '/';
}

template<typename KEY_TYPE, typename VALUE_TYPE>
int CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::getdepth(typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * node) const
{
  int i;
  for (i = 0; node->parent; ++i)
  {
    node = node->parent;
  }
  return i;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::find_rec
(KEY_TYPE key, typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * node)
{
  // Base Cases: root is null or key is present at root 
  if (node == nullptr || node->key == key)
  {
    return node;
  }

  // Key is greater than root's key 
  if (node->key < key)
    return find_rec(key, node->right);

  // Key is smaller than root's key 
  return find_rec(key, node->left);
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node *
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::makeNode(KEY_TYPE key, VALUE_TYPE value)
{
  ++size_;
  return new Node(key, value, nullptr, 0, 0, nullptr, nullptr);
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::insert_rec
(KEY_TYPE key, VALUE_TYPE value, CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * node, Node *&finalNode)
{
  /* 1. Perform the normal BST insertion */
  if (!node)
  {
    finalNode = makeNode(key, value);
    return finalNode;
  }

  if (key < node->key)
  {
    node->left = insert_rec(key, value, node->left, finalNode);
    node->left->parent = node;
  }
    
  else if (key > node->key)
  {
    node->right = insert_rec(key, value, node->right, finalNode);
    node->right->parent = node;
  }
    
  else // Equal keys are not allowed in BST  
  {
    return node;
  }

  /* 2. Update height of this ancestor node */
  node->height = 1 + std::max(height(node->left), height(node->right));

  /* 3. Get the balance factor of this ancestor
      node to check whether this node became
      unbalanced */
  int balance = getBalance(node);

  // If this node becomes unbalanced, then  
  // there are 4 cases  

  // Left Left Case  
  if (balance > 1 && key < node->left->key)
    return rightRotate(node->left);

  // Right Right Case  
  if (balance < -1 && key > node->right->key)
    return leftRotate(node->right);

  // Left Right Case  
  if (balance > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case  
  if (balance < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  /* return the (unchanged) node pointer */
  return node;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
void CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::erase_rec
(typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * &node, KEY_TYPE key)
{
  if (!node)
  {
    return;
  }
    
  else if (key < node->key)
  {
    erase_rec(node->left, key);
  }
  else if (key > node->key)
  {
    erase_rec(node->right, key);
  }
  else // (Data == tree->data)
  {
    if (!node->left)
    {
      Node * temp = node;
      Node *tempParent = node->parent;
      node = node->right;
      deleteNode(temp);
      if (node)
      {
        node->parent = tempParent;
      }
    }
    else if (!node->right)
    {
      Node * temp = node;
      Node *tempParent = node->parent;
      node = node->left;
      deleteNode(temp);
      node->parent = tempParent;
    }
    else
    {
      Node * pred = node->decrement();
      node->key = pred->key;
      erase_rec(node->left, node->key);
    }
  }
}

template<typename KEY_TYPE, typename VALUE_TYPE>
void CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::deleteNode(Node * node)
{
  --size_;
  delete node;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * 
CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::copy_rec
(typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * node)
{
  if (!node)
    return nullptr;
  else
  {
    Node *newNode = makeNode(node->key, node->value);

    newNode->left  = copy_rec(node->left);
    if (newNode->left)
    {
      newNode->left->parent = newNode;
    }
    newNode->right = copy_rec(node->right);
    if (newNode->right)
    {
      newNode->right->parent = newNode;
    }

    return newNode;
  }
}

template<typename KEY_TYPE, typename VALUE_TYPE>
void CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::deleteAllTheThings_rec(Node * node)
{
  if (!node)
    return;
  else
  {
    deleteAllTheThings_rec(node->left);
    deleteAllTheThings_rec(node->right);
    deleteNode(node);
  }
}

template<typename KEY_TYPE, typename VALUE_TYPE>
int CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::height(Node * node)
{
  if (node == nullptr)
    return 0;
  return node->height;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::rightRotate(Node * node)
{
  Node *nodeLeft = node->left;
  Node *nodeLeftRight = nodeLeft->right;
  Node *baseParent = node->parent;

  // Perform rotation  
  nodeLeft->right = node;
  node->left = nodeLeftRight;

  // Updating parents
  nodeLeft->parent = baseParent;
  node->parent = nodeLeft;

  if (nodeLeftRight)
  {
    nodeLeftRight->parent = node;
  }

  // Update heights  
  node->height = std::max(height(node->left), height(node->right)) + 1;
  nodeLeft->height = std::max(height(nodeLeft->left), height(nodeLeft->right)) + 1;

  // Return new root  
  return nodeLeft;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
typename CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::Node * CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::leftRotate(Node * node)
{
  Node *nodeRight = node->right;
  Node *nodeRightLeft = nodeRight->left;
  Node *baseParent = node->parent;

  // Perform rotation  
  nodeRight->left = node;
  node->right = nodeRightLeft;

  // Updating parents
  nodeRight->parent = baseParent;
  node->parent = nodeRight;

  if (nodeRightLeft)
  {
    nodeRightLeft->parent = node;
  }

  if (baseParent)
  {
    if (baseParent->right == node)
    {
      baseParent->right = nodeRight;
    }
    else
    {
      baseParent->left = nodeRight;
    }
  }
 

  // Update heights  
  node->height = std::max(height(node->left), height(node->right)) + 1;
  nodeRight->height = std::max(height(nodeRight->left), height(nodeRight->right)) + 1;

  // Return new root  
  return nodeRight;
}

template<typename KEY_TYPE, typename VALUE_TYPE>
int CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::getBalance(Node * node)
{
  if (!node)
    return 0;
  return height(node->left) - height(node->right);
}

/* this is another "ASCII-graphical" print, but using
 * iterative function.
 * Left branch of the tree is at the bottom
 */
template< typename KEY_TYPE, typename VALUE_TYPE >
std::ostream& CS280::operator<<(std::ostream& os, AVLmap<KEY_TYPE, VALUE_TYPE> const& map) {
  map.print(os);
  return os;
}

template< typename KEY_TYPE, typename VALUE_TYPE >
void CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::print(std::ostream& os, bool print_value) const {
  if (pRoot) {
    AVLmap<KEY_TYPE, VALUE_TYPE>::Node* b = pRoot->last();
    while (b) {
      int depth = getdepth(b);
      int i;
      /* printf(b); */

      char edge = getedgesymbol(b);
      switch (edge) {
      case '-':
        for (i = 0; i < depth; ++i) std::printf("       ");
        os << b->key;
        if (print_value) { os << " -> " << b->value; }
        os << std::endl;
        break;
      case '\\':
        for (i = 0; i < depth; ++i) std::printf("       ");
        os << edge << std::endl;
        for (i = 0; i < depth; ++i) std::printf("       ");
        os << b->key;
        if (print_value) { os << " -> " << b->value; }
        os << std::endl;
        break;
      case '/':
        for (i = 0; i < depth; ++i) std::printf("       ");
        os << b->key;
        if (print_value) { os << " -> " << b->value; }
        os << std::endl;
        for (i = 0; i < depth; ++i) std::printf("       ");
        os << edge << std::endl;
        break;
      }
      b = b->decrement();
    }
  }
  std::printf("\n");
}

template<typename KEY_TYPE, typename VALUE_TYPE>
bool CS280::AVLmap<KEY_TYPE, VALUE_TYPE>::sanityCheck()
{
  return false;
}

