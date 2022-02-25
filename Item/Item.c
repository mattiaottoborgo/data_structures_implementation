#include "Item.h"
#include "string.h"
struct location{
    char *shelf[LENGTH_SHELF_NAME];
    int row,column;
};

struct item{
    char *id[LENGTH_PRODUCT_ID];
    LOCATION loc;
};
Key KEYget(Item item){
    return item->id;
}
int KEYcmp(Key key1,Key key2){
    return strcmp(key1,key2);
}