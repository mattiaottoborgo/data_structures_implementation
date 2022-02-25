#ifndef ITEM_HEADER
#define ITEM_HEADER
#define LENGTH_SHELF_NAME 100
#define LENGTH_PRODUCT_ID 100
typedef char* Key;
typedef struct location *LOCATION;
typedef struct item *Item;
int KEYcmp(Key key1,Key key2);
Key KEYget(Item item);
Item ITEMnull();
int ITEMchecknull(Item item);

#endif