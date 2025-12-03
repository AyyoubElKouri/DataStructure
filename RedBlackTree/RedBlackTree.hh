/*--------------------------------------------------------------------------------------------------
 *                       Copyright (c) Ayyoub EL Kouri. All rights reserved
 *     Becoming an expert won't happen overnight, but with a bit of patience, you'll get there
 *------------------------------------------------------------------------------------------------*/

#ifndef RED_BLACK_TREE_HH
#define RED_BLACK_TREE_HH

#include <functional>

// Color enumeration for nodes
enum class Color {
   RED,
   BLACK
};

template<typename T>
class Node {
public:
   T data;
   Color color;
   Node* parent;
   Node* left;
   Node* right;
   
   // Constructor for regular nodes
   Node(const T& value) 
      : data(value), color(Color::RED), 
      parent(nullptr), left(nullptr), right(nullptr) {}
};

// Template class for Red-Black Tree
template<typename T, typename Compare = std::less<T>>
class RedBlackTree {
private:
   Node<T>* root;
   Node<T>* NIL;
   Compare comp;
   size_t nodeCount;
   
   // Helper methods for tree operations
   void rotateLeft(Node<T>* x);
   void rotateRight(Node<T>* x);
   void insertFixup(Node<T>* z);
   void deleteFixup(Node<T>* x);
   void transplant(Node<T>* u, Node<T>* v);
   
   // Utility methods
   Node<T>* minimum(Node<T>* node) const;
   Node<T>* maximum(Node<T>* node) const;
   Node<T>* search(Node<T>* node, const T& value) const;
   void destroyTree(Node<T>* node);
   
   // Traversal helpers
   void inorderHelper(Node<T>* node, void (*callback)(const T&)) const;

public:
   RedBlackTree();
   ~RedBlackTree();
   
   // Disable copy
   RedBlackTree(const RedBlackTree&) = delete;
   RedBlackTree& operator=(const RedBlackTree&) = delete;
   
   // Core operations
   void insert(const T& value);
   bool remove(const T& value);
   bool contains(const T& value) const;
   
   // Utility operations
   bool isEmpty() const { return root == NIL; }
   size_t size() const { return nodeCount; }
   void clear();
   
   // Traversal
   void inorder(void (*callback)(const T&)) const;
};

// ======================================== IMPLEMENTATION =========================================

// CONSTRUCTOR & DESTRUCTOR
template<typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree() : nodeCount(0) {
   // Create sentinel NIL node (represents all leaves)
   NIL = new Node<T>(T());
   NIL->color = Color::BLACK;  // NIL is always black
   NIL->parent = nullptr;
   NIL->left = nullptr;
   NIL->right = nullptr;
   
   // Empty tree: root points to NIL
   root = NIL;
}

template<typename T, typename Compare>
RedBlackTree<T, Compare>::~RedBlackTree() {
   destroyTree(root);
   delete NIL;
}


// UTILITY: Destroy tree recursively (post-order)
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::destroyTree(Node<T>* node) {
   if (node == NIL) return;

   // Delete children first, then parent
   destroyTree(node->left);
   destroyTree(node->right);
   delete node;
}

// UTILITY: Clear entire tree
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::clear() {
   destroyTree(root);
   root = NIL;
   nodeCount = 0;
}

// SEARCH: Find node with given value
template<typename T, typename Compare>
Node<T>* RedBlackTree<T, Compare>::search(Node<T>* node, const T& value) const {
   // Base case: not found (NIL) or found (equal)
   if (node == NIL || node->data == value) {
      return node;
   }

   // Recursive search: left or right based on comparison
   if (comp(value, node->data)) {
      return search(node->left, value);
   } else {
      return search(node->right, value);
   }
}

template<typename T, typename Compare>
bool RedBlackTree<T, Compare>::contains(const T& value) const {
   return search(root, value) != NIL;
}

// UTILITY: Find minimum/maximum in subtree
template<typename T, typename Compare>
Node<T>* RedBlackTree<T, Compare>::minimum(Node<T>* node) const {
   while (node->left != NIL) {
      node = node->left;
   }
   return node;
}

template<typename T, typename Compare>
Node<T>* RedBlackTree<T, Compare>::maximum(Node<T>* node) const {
   while (node->right != NIL) {
      node = node->right;
   }
   return node;
}

// TRAVERSAL: Inorder (sorted order)
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::inorderHelper(Node<T>* node, void (*callback)(const T&)) const {
   if (node == NIL) return;

   // Left -> Root -> Right
   inorderHelper(node->left, callback);
   callback(node->data);
   inorderHelper(node->right, callback);
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::inorder(void (*callback)(const T&)) const {
    inorderHelper(root, callback);
}

// ROTATION: Left Rotation
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::rotateLeft(Node<T>* x) {
   // Set y (will become new parent)
   Node<T>* y = x->right; 
   
   // Turn y's left subtree into x's right subtree
   x->right = y->left;
   if (y->left != NIL) {
      y->left->parent = x;
   }
   
   // Link x's parent to y
   y->parent = x->parent;
   if (x->parent == nullptr) {
      root = y;  // y becomes new root
   } else if (x == x->parent->left) {
      x->parent->left = y;  // x was left child
   } else {
      x->parent->right = y;  // x was right child
   }
   
   // Put x on y's left
   y->left = x;
   x->parent = y;
}

// ROTATION: Right Rotation
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::rotateRight(Node<T>* y) {
   Node<T>* x = y->left;  // Set x (will become new parent)
   
   // Turn x's right subtree into y's left subtree
   y->left = x->right;
   if (x->right != NIL) {
      x->right->parent = y;
   }
   
   // Link y's parent to x
   x->parent = y->parent;
   if (y->parent == nullptr) {
      root = x;  // x becomes new root
   } else if (y == y->parent->right) {
      y->parent->right = x;  // y was right child
   } else {
      y->parent->left = x;  // y was left child
   }
   
   // Put y on x's right
   x->right = y;
   y->parent = x;
}

// INSERT: Add new value to tree
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::insert(const T& value) {
   // Create new red node
   Node<T>* z = new Node<T>(value);
   z->left = NIL;
   z->right = NIL;
   
   // Standard BST insertion
   Node<T>* y = nullptr;  // Trailing pointer (will be parent of z)
   Node<T>* x = root;      // Current node
   
   // Find correct position for new node
   while (x != NIL) {
      y = x;
      if (comp(z->data, x->data)) {
         x = x->left;   // Go left
      } else {
         x = x->right;  // Go right
      }
   }
   
   // Set parent of new node
   z->parent = y;
   
   // Insert as root or as child
   if (y == nullptr) {
      root = z;  // Tree was empty
   } else if (comp(z->data, y->data)) {
      y->left = z;   // Insert as left child
   } else {
      y->right = z;  // Insert as right child
   }
   
   nodeCount++;
   
   // Fix Red-Black properties
   insertFixup(z);
}

// INSERT FIXUP: Restore Red-Black properties after insertion
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::insertFixup(Node<T>* z) {
   // Continue while parent is red (violation of property 4)
   while (z->parent != nullptr && z->parent->color == Color::RED) {
      
      // Parent is LEFT child of grandparent
      if (z->parent == z->parent->parent->left) {
         Node<T>* uncle = z->parent->parent->right;  // Uncle is right child
         
         // CASE 1: Uncle is RED
         if (uncle->color == Color::RED) {
            z->parent->color = Color::BLACK;         // Recolor parent
            uncle->color = Color::BLACK;              // Recolor uncle
            z->parent->parent->color = Color::RED;    // Recolor grandparent
            z = z->parent->parent;                    // Move up to grandparent
         }
         // Uncle is BLACK
         else {
            // CASE 2: z is RIGHT child (convert to Case 3)
            if (z == z->parent->right) {
               z = z->parent;
               rotateLeft(z);  // Transform to Case 3
            }
            
            // CASE 3: z is LEFT child
            z->parent->color = Color::BLACK;          // Recolor parent
            z->parent->parent->color = Color::RED;    // Recolor grandparent
            rotateRight(z->parent->parent);           // Rotate right
         }
      }
      // Parent is RIGHT child of grandparent (symmetric)
      else {
         Node<T>* uncle = z->parent->parent->left;  // Uncle is left child
         
         // CASE 1: Uncle is RED
         if (uncle->color == Color::RED) {
            z->parent->color = Color::BLACK;
            uncle->color = Color::BLACK;
            z->parent->parent->color = Color::RED;
            z = z->parent->parent;
         }
         // Uncle is BLACK
         else {
            // CASE 2: z is LEFT child (convert to Case 3)
            if (z == z->parent->left) {
               z = z->parent;
               rotateRight(z);  // Transform to Case 3
            }
            
            // CASE 3: z is RIGHT child
            z->parent->color = Color::BLACK;
            z->parent->parent->color = Color::RED;
            rotateLeft(z->parent->parent);
         }
      }
   }
   
   // Ensure root is always black (property 2)
   root->color = Color::BLACK;
}

// UTILITY: Transplant - Replace subtree u with subtree v
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::transplant(Node<T>* u, Node<T>* v) {
   // Update parent's child pointer
   if (u->parent == nullptr) {
      root = v;  // u was root
   } else if (u == u->parent->left) {
      u->parent->left = v;  // u was left child
   } else {
      u->parent->right = v;  // u was right child
   }
   
   // Update v's parent (even if v is NIL)
   v->parent = u->parent;
}


// DELETE: Remove value from tree
template<typename T, typename Compare>
bool RedBlackTree<T, Compare>::remove(const T& value) {
   // Find node to delete
   Node<T>* z = search(root, value);
   if (z == NIL) {
      return false;  // Value not found
   }
   
   Node<T>* y = z;  // Node to be deleted (or moved)
   Node<T>* x;      // Node that replaces y
   Color yOriginalColor = y->color;
   
   // CASE 1: z has no left child
   if (z->left == NIL) {
      x = z->right;
      transplant(z, z->right);  // Replace z with right child
   }
   // CASE 2: z has no right child
   else if (z->right == NIL) {
      x = z->left;
      transplant(z, z->left);  // Replace z with left child
   }
   // CASE 3: z has two children
   else {
      y = minimum(z->right);  // Find successor (min of right subtree)
      yOriginalColor = y->color;
      x = y->right;
      
      // Successor is direct child of z
      if (y->parent == z) {
         x->parent = y;  // Even if x is NIL
      }
      // Successor is deeper in right subtree
      else {
         transplant(y, y->right);  // Replace y with its right child
         y->right = z->right;       // Move z's right subtree to y
         y->right->parent = y;
      }
      
      // Replace z with y
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;  // Keep z's color
   }
   
   delete z;
   nodeCount--;
   
   // Fix Red-Black properties if we deleted a BLACK node
   if (yOriginalColor == Color::BLACK) {
      deleteFixup(x);
   }
   
   return true;
}

// DELETE FIXUP: Restore Red-Black properties after deletion
template<typename T, typename Compare>
void RedBlackTree<T, Compare>::deleteFixup(Node<T>* x) {
   // Continue while x is not root and x is black (double black)
   while (x != root && x->color == Color::BLACK) {
      
      // x is LEFT child
      if (x == x->parent->left) {
         Node<T>* w = x->parent->right;  // Sibling
         
         // CASE 1: Sibling is RED
         if (w->color == Color::RED) {
            w->color = Color::BLACK;           // Recolor sibling
            x->parent->color = Color::RED;     // Recolor parent
            rotateLeft(x->parent);             // Rotate left
            w = x->parent->right;              // Update sibling
         }
         
         // CASE 2: Sibling BLACK + both children BLACK
         if (w->left->color == Color::BLACK && w->right->color == Color::BLACK) {
            w->color = Color::RED;  // Recolor sibling
            x = x->parent;          // Move problem up
         }
         else {
            // CASE 3: Sibling BLACK + left RED, right BLACK
            if (w->right->color == Color::BLACK) {
               w->left->color = Color::BLACK;   // Recolor left child
               w->color = Color::RED;           // Recolor sibling
               rotateRight(w);                  // Rotate right
               w = x->parent->right;            // Update sibling
            }
            
            // CASE 4: Sibling BLACK + right RED
            w->color = x->parent->color;        // Copy parent's color
            x->parent->color = Color::BLACK;    // Recolor parent
            w->right->color = Color::BLACK;     // Recolor right child
            rotateLeft(x->parent);              // Rotate left
            x = root;                           // Terminate loop
         }
      }
      // x is RIGHT child (symmetric cases)
      else {
         Node<T>* w = x->parent->left;  // Sibling
         
         // CASE 1: Sibling is RED
         if (w->color == Color::RED) {
            w->color = Color::BLACK;
            x->parent->color = Color::RED;
            rotateRight(x->parent);
            w = x->parent->left;
         }
         
         // CASE 2: Sibling BLACK + both children BLACK
         if (w->right->color == Color::BLACK && w->left->color == Color::BLACK) {
            w->color = Color::RED;
            x = x->parent;
         }
         else {
            // CASE 3: Sibling BLACK + right RED, left BLACK
            if (w->left->color == Color::BLACK) {
               w->right->color = Color::BLACK;
               w->color = Color::RED;
               rotateLeft(w);
               w = x->parent->left;
            }
            
            // CASE 4: Sibling BLACK + left RED
            w->color = x->parent->color;
            x->parent->color = Color::BLACK;
            w->left->color = Color::BLACK;
            rotateRight(x->parent);
            x = root;
         }
      }
   }
   
   // Ensure x is black
   x->color = Color::BLACK;
}


#endif // RED_BLACK_TREE_HH
