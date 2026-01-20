#include "list.h"

int main(void) {
    List l = initList();
    for (int i = 0; i < 10; i++) appendList(&l, i);
    popList(&l);
    popAtList(&l, 3);
    insertList(&l, 3, 3);
    for (int i = 0; i < l.len; i++) printf("%d ", (int)getList(l, i));
}