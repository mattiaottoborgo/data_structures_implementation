#include <stdlib.h>
#include "Item.h"
#include "BST_extended.h"
typedef struct BSTnode* link;
struct BSTnode { Item item; link l; link r;int N;link p} ;
struct binarysearchtree { link root; link z; };
static void treeFree(link h, link z);

static link NEW(Item item, link p, link l, link r, int N){
link x = malloc(sizeof *x);
x->item = item;
x->p = p; x->l = l; x->r = r; x->N = N;
return x;
}

BST BSTinit( ) {
    BST bst = malloc(sizeof *bst) ;
    bst->root= ( bst->z = NEW(ITEMsetNull(),NULL,NULL, NULL,0));
    return bst;
}
void BSTfree(BST bst){
    if (bst == NULL) return;
        treeFree(bst->root, bst->z);
        free(bst->z);
        free(bst);
}

static void treeFree(link h, link z){
    if (h == z) return;
        treeFree(h->l, z);
        treeFree(h->r, z);
        free(h);
}

static int countR(link h, link z) {
    if (h == z) return 0;
    return countR(h->l, z) + countR(h->r, z) +1;
}
int BSTcount(BST bst) {
    return countR(bst->root, bst->z);
}
int BSTempty(BST bst) {
    if (BSTcount(bst) == 0) return 1;
    return 0;
}

Item searchR(link h, Key k, link z) {
    int cmp;
    if (h == z) return ITEMsetNull();
    cmp = KEYcmp(k, KEYget(h->item));
    if (cmp == 0) return h->item;
    if (cmp == -1) return searchR(h->l, k, z);
    return searchR(h->r, k, z);
}
Item BSTsearch(BST bst, Key k) {
    return searchR(bst->root, k, bst->z);
}
Item minR(link h, link z) {
    if (h == z) return ITEMsetNull();
    if (h->l == z) return (h->item);
    return minR(h->l, z);
}
//wrapper minR
Item BSTmin(BST bst) {
    return minR(bst->root, bst->z);
}

Item maxR(link h, link z) {
    if (h == z) return ITEMsetNull();
    if (h->r == z) return (h->item);
    return maxR(h->r, z);
}
//wrapper maxR
Item BSTmax(BST bst) {
    return maxR(bst->root, bst->z);
}

static link insertR(link h, Item x, link z) {
    if (h == z) return NEW(x, z,z, z,1);
    if (KEYcmp(KEYget(x), KEYget(h->item))==-1){
        h->l = insertR(h->l, x, z); h->l->p=h;
    }
    else{
        h->r = insertR(h->r, x, z); h->r->p=h;
    }
    (h->N)++;
    return h;
}
void BSTinsert_leafR(BST bst, Item x) {
    bst->root = insertR(bst->root, x, bst->z);
}

void BSTinsert_leafI(BST bst, Item x) {
    link p = bst->root, h = p;
    if (bst->root == bst->z) {
        bst->root = NEW(x,bst->z,bst->z, bst->z,1);
        return;
    }
    while (h != bst->z) {
        p = h;
        h=(KEYcmp(KEYget(x),KEYget(h->item))==-1) ? h->l : h->r;
    }
    h = NEW(x,p,bst->z, bst->z,1);
    if (KEYcmp(KEYget(x), KEYget(p->item))==-1)
        p->l = h;
    else
    p->r = h;
}

static void treePrintR(link h, link z, int strategy) {
    if (h == z) return;
    if (strategy == PREORDER)
        ITEMstore(h->item);
    treePrintR(h->l, z, strategy);
    if (strategy == INORDER)
        ITEMstore(h->item);
    treePrintR(h->r, z, strategy);
    if (strategy == POSTORDER)
        ITEMstore(h->item);
}
void BSTvisit(BST bst, int strategy) {
    if (BSTempty(bst))
        return;
    treePrintR(bst->root, bst->z, strategy);
}

link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

//inserzione in radice
static link insertT(link h, Item x, link z) {
    if (h == z)
        return NEW(x, z, z);
    if (KEYcmp(KEYget(x), KEYget(h->item))==-1) {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
    }
    else {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
    }
    return h;
}


void BSTinsert_root(BST bst, Item x) {
    bst->root = insertT(bst->root, x, bst->z);
}

static link balanceR(link h, link z) {
int r;
if (h == z)
return z;
r = (h->N+1)/2-1;
h = partR(h, r);
h->l = balanceR(h->l, z);
h->r = balanceR(h->r, z);
return h;
}
void BSTbalance(BST bst) {
bst->root = balanceR(bst->root, bst->z);
}

Item searchSucc(link h, Key k,link z){
    link p;
    if(h==z) return ITEMsetNull();
    if(KEYcmp(k,KEYget(h->item))==0){
        if(h->r!=z) return minR(h->r,z);
        else{
            p=h->p;
            while(p!=z && h==p->r){
                h=p;p=p->p;
            }
            return p->item;
        }
    }
    if (KEYcmp(k,KEYget(h->item))==-1) return searchSucc(h->l,k,z);
    return searchSucc(h->r,k,z);
}
Item BSTsucc(BST bst, Key k){
    return searchSucc(bst->root,k,bst->z);
}

Item searchPred(link h, Key k,link z){
    link p;
    if(h==z) return ITEMsetNull();
    if(KEYcmp(k,KEYget(h->item))==0){
        if(h->l!=z) return maxR(h->l,z);
        else{
            p=h->p;
            while(p!=z && h==p->l) h=p;p=p->p;
            return p->item;
        }
    }
    if (KEYcmp(k,KEYget(h->item))==-1) return searchPred(h->l,k,z);
    return searchPred(h->r,k,z);
}
Item BSTpred(BST bst, Key k){
    return searchPred(bst->root,k,bst->z);
}