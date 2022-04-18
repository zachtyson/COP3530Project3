

#ifndef UNTITLED4_BTREE_H
#define UNTITLED4_BTREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
//2-3-4 tree

using namespace std;
template <typename type>
class BTree
{;
    struct NodeB
    {
        vector<type> nodeKeys;
        vector<NodeB*> nodeChildren;
        int keyIndex;
        bool isLeaf;
        explicit NodeB(bool l);
        void insertToNode(type val);
        void balanceTree(int index, NodeB* nodeToBalance);
        void inorderTraversal(queue<type>& q);
        void revorderTraversal(stack<type>& s);
        NodeB* find(type val);
    };
public:
    int totalKeys = 0;
    void inorder(queue<type>& q); // Inorder traversal
    void revorder(stack<type>& s); // Reverse traversal
    NodeB* search(type val); //Search for certain value (doesn't handle duplicates, but the data set shouldn't have any duplicate names)
    void insert(type val); //Insert value into tree
    NodeB* root = nullptr; //Root Node Pointer
};

template<typename type>
void BTree<type>::NodeB::balanceTree(int index, BTree::NodeB *nodeToBalance) {
    auto *newNode = new NodeB(nodeToBalance->isLeaf);
    newNode->keyIndex = 1;
    for (int i = 0; i < 1; i++) {
        newNode->nodeKeys[i] = nodeToBalance->nodeKeys[i + 2];
    }
    if (!nodeToBalance->isLeaf)
    {
        for (int i = 0; i < 2; i++) {
            newNode->nodeChildren[i] = nodeToBalance->nodeChildren[i + 2];
        }
    }

    nodeToBalance->keyIndex = 1;
    for (int i = keyIndex; i >= index + 1; i--){
        nodeChildren[i+1] = nodeChildren[i];
    }
    nodeChildren[index + 1] = newNode;
    for (int i = keyIndex-1; i >= index; i--) {
        nodeKeys[i + 1] = nodeKeys[i];
    }
    nodeKeys[index] = nodeToBalance->nodeKeys[1];
    keyIndex = keyIndex + 1;
}

template<typename type>
BTree<type>::NodeB::NodeB(bool l) {
    isLeaf = l;
    nodeKeys.resize(3);
    nodeChildren.resize(4);
    keyIndex = 0;
}

template<typename type>
void BTree<type>::NodeB::inorderTraversal(queue<type>& q) {

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
typename BTree<type>::NodeB *BTree<type>::NodeB::find(type val) {
    int index = 0;
    while (index < keyIndex && val > nodeKeys[index]) {
        index++;
    }
    if (nodeKeys[index] == val) {
        return this;
    }
    if (isLeaf) {
        return nullptr;
    }
    return nodeChildren[index]->find(val);
}

template<typename type>
void BTree<type>::NodeB::insertToNode(type val) {
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
        if (nodeChildren[middleIndex+1]->keyIndex == 3)
        {
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
    for (int i = 0; i < keyIndex; i++)
    {
        if (!isLeaf)
            nodeChildren[i]->revorderTraversal(s);
        s.push(nodeKeys[i]);
        //cout << " " << nodeKeys[i];
    }

    if (!isLeaf ) {
        nodeChildren[keyIndex]->revorderTraversal(s);
    }
}


template<typename type>
void BTree<type>::insert(type val) {
    totalKeys++;
    if (!root)
    {
        root = new NodeB(true);
        root->nodeKeys[0] = val;
        root->keyIndex = 1;
        return;
    }
    if (root->keyIndex == 3) {
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
    }
}

template<typename type>
typename BTree<type>::NodeB* BTree<type>::search(type val) {
    if(root == nullptr) {
        return nullptr;
    }
    return root->find(val);
}

template<typename type>
void BTree<type>::inorder(queue<type>& q) {
    if (root == nullptr) {
        return;
    }
    root->inorderTraversal(q);
}

template<typename type>
void BTree<type>::revorder(stack<type> &s) {
    if (root == nullptr) {
        return;
    }
    root->revorderTraversal(s);
}

#endif //UNTITLED4_BTREE_H
