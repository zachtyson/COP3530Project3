#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <math.h>
#include <stack>
#include "Recipe.h"
using namespace std;  

//Heap structure and associated functions.
template <typename type>
class minHeap
{
    private:
    vector<type> Heap;
    vector<type> littleGuy; //sub heap that contains an input string for searching recipes based on name within the primary minHeap
    int size = 0;
    int sizeLG = 0;
    int cap;

    public:
    minHeap(int cap); //creates a minHeap vector with an initial size of 0 and a max size of all the recipes in the data base
    int getSize() const;
    vector<Recipe*> searchName(string name); // Added signature for search by name to heap
    void insertGen(type recipe); // insert function for minheap sorted alphabetically
    void printTop();
    void remove();
    vector<type> getHeap();
    vector<type> makeMaxHeap(vector<type> Heap); //uses stack to turn minHeap into maxHeap
    void searchIngredient(vector<string>& ingredients, vector<Recipe *>& recipes);
    vector<type> extract();
private:
    bool leaf(int position);
    int parent(int position);
    int leftC(int position);
    int RightC(int position);
    void swap(int first, int second);
    void swapLG(int first, int second);
    void minHeapify(int position);
    void minHeapify2(vector<type>& h, int i);
};


template <typename type>
void minHeap<type>::swapLG(int first, int second) {
    type temp;
    temp  = littleGuy[first];
    littleGuy[first] = littleGuy[second];
    littleGuy[second] = temp;
}



template <typename type>
void minHeap<type>::swap(int first, int second) {
    type temp;
    temp  = Heap[first];
    Heap[first] = Heap[second];
    Heap[second] = temp;
}

template <typename type>
int minHeap<type>::RightC(int position) {
    return (2*position)+1;
}
template <typename type>
int minHeap<type>::leftC(int position) {
    return 2*position;
}

template <typename type>
int minHeap<type>::parent(int position) {
    return floor(position/2);
}
template <typename type>
bool minHeap<type>::leaf(int position) {
    if (position > (size/2) && position <= size) //g4g indicated that a leaf could be detected with this math
    {
        return true;
    }
    return false;
}
template <typename type>
vector<type> minHeap<type>::makeMaxHeap(vector<type> Heap) {
    stack<type> maxHeap;
    for(auto & i : Heap)
    {
        maxHeap.push(i);
    }
    vector<type> max;
    while(!maxHeap.empty())
    {
        max.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return max;
}


template <typename type>
void minHeap<type>::remove() {
    Heap[0] = Heap[size - 1];
    Heap.pop_back();
    minHeapify(0);
    size--;
}

template <typename type>
void minHeap<type>::printTop() {
    Heap[0].second->printRecipe();
}

template <typename type>
vector<Recipe *> minHeap<type>::searchName(string name) {
    for (int i = 0; i < size; i++) {
        if (Heap[i].first.find(name) != string::npos) {
            littleGuy.push_back(Heap[i]);
        }
    }
    sizeLG = 0;
    vector<Recipe*> copy;
    for(int i = 0; i < littleGuy.size(); i++) {
        copy.push_back(littleGuy[i].second);
    }
    littleGuy.clear(); //clears the subHeap for when search is called again
    return copy;
}
template <typename type>
int minHeap<type>::getSize() const {
    return size;
}
template <typename type>
minHeap<type>::minHeap(int _cap) {
    cap = _cap;
    size = 0;
    sizeLG = 0;
}

template<typename type>
void minHeap<type>::insertGen(type recipe) {
    if (size >= cap){
        return;
    }
    Heap.push_back(recipe);
    int lastNode = size;
    size++;

    while (Heap[lastNode] < Heap[parent(lastNode)])
    {
        type t = Heap[lastNode];
        Heap[lastNode] = Heap[parent(lastNode)];
        Heap[parent(lastNode)] = t;
        lastNode = parent(lastNode);
    }
}

template<typename type>
void minHeap<type>::minHeapify(int position) {
    if(!leaf(position))
    {
        if(Heap[position] > Heap[leftC(position)] || Heap[position] > Heap[RightC(position)])
        {
            if(Heap[leftC(position)] < Heap[RightC(position)])
            {
                type t = Heap[position];
                Heap[position] = Heap[leftC(position)];
                Heap[leftC(position)] = t;
                minHeapify(leftC(position));
            }
            else
            {
                type t = Heap[position];
                Heap[position] = Heap[RightC(position)];
                Heap[RightC(position)] = t;
                minHeapify(RightC(position));
            }
        }
    }
}

template<typename type>
void minHeap<type>::searchIngredient(vector<string> &ingredients, vector<Recipe *> &recipes) {
    for(int i = 0; i < size; i++) {
        vector<string> ingredientsCurr = Heap[i].second->getIngredients();
        if (std::includes(ingredientsCurr.begin(), ingredientsCurr.end(), ingredients.begin(),ingredients.end())) {
            recipes.push_back(Heap[i].second);
        }
    }
}

template <typename type>
vector<type> minHeap<type>::getHeap() {
    return Heap;
}

template<typename type>
vector<type> minHeap<type>::extract() {
    vector<type> t;
    vector<type> k = Heap;
    while(!k.empty()) {
        t.push_back(k[0]);
        k[0] = k[k.size()-1];
        minHeapify2(k,0);
        k.pop_back();

    }
    return t;
}

template<typename type>
void minHeap<type>::minHeapify2(vector<type>& h, int i) {
    if(!leaf(i))
    {
        if(h[i] > h[leftC(i)] || h[i] > h[RightC(i)])
        {
            if(h[leftC(i)] < h[RightC(i)])
            {
                type temp = h[i];
                h[i] = h[leftC(i)];
                h[leftC(i)] = temp;
                minHeapify2(h,leftC(i));
            }
            else
            {
                type temp = h[i];
                h[i] = h[RightC(i)];
                h[RightC(i)] = temp;
                minHeapify2(h,RightC(i));
            }
        }
    }
}
