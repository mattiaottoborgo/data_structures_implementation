
#ifndef BST_EXTENDED_HEADER
#define BST_EXTENDED_HEADER
enum {PREORDER,INORDER,POSTORDER};
typedef struct binarysearchtree *BST;
#include "Item.h"
BST BSTinit() ;
void BSTfree(BST bst);
int BSTcount(BST bst);
int BSTempty(BST bst);
Item BSTsearch(BST bst, Key k);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmin(BST bst);
Item BSTmax(BST bst);
Item BSTsucc(BST bst, Key k);
void BSTvisit(BST bst, int strategy);
#endif
