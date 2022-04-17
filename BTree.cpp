#include "BTree.h"
 //2-3 Tree
BTree::BTree() {
    L = 2;
    N = 3;
    root == nullptr;
}

NodeB *BTree::search(string name) {
    return nullptr;
}

void BTree::insert(Recipe *recipe) {
    if(root == nullptr) {
        root = new NodeB();
        root->keys.push_back(recipe);
    }
//    } else {
//        if(root->keys.size() > L) {
//            NodeB* newRoot = new NodeB();
//            newRoot->children.push_back(root);
//            newRoot->keys.push_back(root->keys[0]);
//            root->keys.erase(root->keys.begin());
//            newRoot->splitChild(0);
//
//        }
//        root->insert(recipe);
//    }
}
