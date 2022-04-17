

#ifndef UNTITLED4_NODEB_H
#define UNTITLED4_NODEB_H
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Recipe.h"
//2-3 Tree
using namespace std;
class NodeB {
private:
    vector<NodeB*> children;
    vector<Recipe*> keys;
    int L; //L = Items per Node
    int N; //N = Children per Node
public:
    NodeB();
    void insert(Recipe* recipe);
    NodeB* search(string recipe);
    void splitChild(int index);
    friend class BTree; //Allows BTree to access NodeB private members
};


#endif //UNTITLED4_NODEB_H
