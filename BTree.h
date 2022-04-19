

#ifndef PROJECT3_BTREE_H
#define PROJECT3_BTREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include "Recipe.h"
#include <string>
//2-3-4 tree

using namespace std;
template <typename type>
class BTree //Class definition B Tree
{; //Everything has to be in one header file since we are using templates
//Well, it doesn't have to, but I'll gladly trade compilation time for compatibility
    struct NodeB //NodeB is a subclass of BTree, cannot be accessed from outside this file
    {
        vector<type> nodeKeys; //Vector of nodes, since this is a 2-3-4 tree you could do three variables for keys, but this makes iterating easier
        vector<NodeB*> nodeChildren; //Vector of child nodes, this could also be 4 variables but this makes iterating easier
        int keyIndex; //Number of nodes that are occupied
        bool isLeaf; //returns leaf value, I couldn't figure out how to get this to work without using this variable
        explicit NodeB(bool l); //Constructor, IDK what explicit means but the IDE put it here, and they know more than I do
        void insertToNode(type val); //Insert a value into the node, depending on the value it shifts others over
        void balanceTree(int index, NodeB* nodeToBalance); //Balance Tree splits a node into two, and then sets its pointers relative to its parent
        void inorderTraversal(queue<type>& q); //Traverses the entire tree and pushes into a queue
        void revorderTraversal(stack<type>& s); //Traverses entire tree and pushes into a stack
        void find(string val, vector<Recipe*>& r); //Searches for a given string (name) within the tree, DO NOT USE IF TEMPLATE TYPE IS NOT PAIR<STRING,RECIPE*>
    };
    int totalKeys = 0; //number of keys in the tree
public:
    int getTotalKeys(); //Returns total keys
    void inorder(queue<type>& q); // Inorder traversal
    void revorder(stack<type>& s); // Reverse inorder traversal
    void search(string val, vector<Recipe*>& r); //Search for all keys containing val
    void insert(type val); //Insert value into tree
    NodeB* root = nullptr; //Root Node Pointer
};

template<typename type>
void BTree<type>::NodeB::balanceTree(int index, BTree::NodeB *nodeToBalance) { //Splits child node into two nodes and attaches to parent
    auto *newNode = new NodeB(nodeToBalance->isLeaf);
    newNode->keyIndex = 1;
    for (int i = 0; i < 1; i++) {
        newNode->nodeKeys[i] = nodeToBalance->nodeKeys[i + 2];
    }
    //Child one stores first two keys
    if (!nodeToBalance->isLeaf)
    {
        for (int i = 0; i < 2; i++) {
            newNode->nodeChildren[i] = nodeToBalance->nodeChildren[i + 2];
        }
    }
    //Child two gets next two keys

    nodeToBalance->keyIndex = 1;
    for (int i = keyIndex; i >= index + 1; i--){
        nodeChildren[i+1] = nodeChildren[i];
    }
    nodeChildren[index + 1] = newNode;
    for (int i = keyIndex-1; i >= index; i--) {
        nodeKeys[i + 1] = nodeKeys[i];
    } //Shift keys over if necessary
    nodeKeys[index] = nodeToBalance->nodeKeys[1];
    keyIndex = keyIndex + 1;
}

template<typename type>
BTree<type>::NodeB::NodeB(bool l) {
    //Constructor for node
    //if this node gets a child then isLeaf changes to false
    isLeaf = l;
    nodeKeys.resize(3);
    nodeChildren.resize(4);
    //nodeChildren and nodeKeys are resizes since I honestly couldn't figure out how to do this without
    //wasting memory like this
    //Keeping track of the used index was so much easier than figuring out how to shift things when pushing to vector
    keyIndex = 0;
}

template<typename type>
void BTree<type>::NodeB::inorderTraversal(queue<type>& q) { //Inorder traversal of the tree
    //Uses recursion to do inorder
    //Goes as far left as possible, pushes queue
    //Then goes root then right
    for (int i = 0; i < keyIndex; i++)
    {
        if (!isLeaf) {
            nodeChildren[i]->inorderTraversal(q);
        }
        q.template emplace(nodeKeys[i]);
    }
    if (!isLeaf) {
        nodeChildren[keyIndex]->inorderTraversal(q);
    }
}



template<typename type>
void BTree<type>::NodeB::insertToNode(type val) {
    //Black magic
    int middleIndex = keyIndex-1;
    if (isLeaf)
    {
        while (middleIndex >= 0 && nodeKeys[middleIndex] > val) {
            nodeKeys[middleIndex+1] = nodeKeys[middleIndex];
            middleIndex--;
        }
        nodeKeys[middleIndex+1] = val;
        keyIndex = keyIndex+1;
    }
    else {
        while (middleIndex >= 0 && nodeKeys[middleIndex] > val) {
            middleIndex--;
        }
        if (nodeChildren[middleIndex+1]->keyIndex == 3) {
            balanceTree(middleIndex+1, nodeChildren[middleIndex+1]);
            if (nodeKeys[middleIndex+1] < val) {
                middleIndex++;
            }
        }
        nodeChildren[middleIndex+1]->insertToNode(val);
    }
}

template<typename type>
void BTree<type>::NodeB::revorderTraversal(stack<type> &s) {
    //Identical to inorder traversal
    //Except it pushes to a stack instead of a queue
    for (int i = 0; i < keyIndex; i++)
    {
        if (!isLeaf)
            nodeChildren[i]->revorderTraversal(s);
        s.push(nodeKeys[i]);
    }

    if (!isLeaf ) {
        nodeChildren[keyIndex]->revorderTraversal(s);
    }
}

template<typename type>
void BTree<type>::NodeB::find(string val, vector<Recipe*>& r) {
    //Compares string val to all keys within this node
    //          B  D   F
    //        A  C   E  G
    //If it finds the value in one of the keys it returns the pointer to the recipe
    //If it's not found AND this node is a leaf, return null
    //Otherwise, it recursively calls find() on the child
    //that best matches

    for (int i = 0; i < keyIndex; i++)
    {
        if (!isLeaf) {
            nodeChildren[i]->find(val,r);
        }
        if (nodeKeys[i].second->getName().find(val) != string::npos) {
            r.push_back(nodeKeys[i].second);
        }
    }
    if (!isLeaf) {
        nodeChildren[keyIndex]->find(val,r);
    }
}


template<typename type>
void BTree<type>::insert(type val) {
    totalKeys++;
    if (!root) { //If root is null, just make a new node
                //O(1) time obviously
        root = new NodeB(true);
        root->nodeKeys[0] = val;
        root->keyIndex = 1;
        return;
    }
    if (root->keyIndex == 3) { //If root is full then that means that likely the entire tree will need to grow in height

        auto* newRoot = new NodeB(false);
        newRoot->nodeChildren[0] = root;
        newRoot->balanceTree(0, root);
            if (newRoot->nodeKeys[0] < val) {
                newRoot->nodeChildren[1]->insertToNode(val);
            } else {
                newRoot->nodeChildren[0]->insertToNode(val);
            }
        root = newRoot;
    } else {
        root->insertToNode(val);
        //Otherwise, just call insert function which can figure it out from there
    }
}



template<typename type>
void BTree<type>::inorder(queue<type>& q) {
    //Calls inorder on root node
    if (root == nullptr) {
        return;
    }
    root->inorderTraversal(q);
}

template<typename type>
void BTree<type>::revorder(stack<type> &s) {
    //Calls reverse order on root node
    if (root == nullptr) {
        return;
    }
    root->revorderTraversal(s);
}

template<typename type>
void BTree<type>::search(string val, vector<Recipe*>& r) {
    if(root == nullptr) {
        return;
    }
    //Return recipe pointer from find function
    return root->find(val,r);
}

template<typename type>
int BTree<type>::getTotalKeys() {
    return totalKeys;
    //Return total keys
}

#endif //PROJECT3_BTREE_H
