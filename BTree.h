

#ifndef UNTITLED4_BTREE_H
#define UNTITLED4_BTREE_H



#include "NodeB.h"
//2-3 Tree
class BTree {
private:
    NodeB* root;
    int L; //At most L keys
    int N; //At most N children
public:
    BTree();
    NodeB* search(string name);
    void insert(Recipe* recipe);
};


#endif //UNTITLED4_BTREE_H
