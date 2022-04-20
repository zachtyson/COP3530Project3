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
    int cap;

    public:
    minHeap(int cap); //creates a minHeap vector with an initial size of 0 and a max size of all the recipes in the data base
    vector<Recipe*> searchName(string name); // Added signature for search by name to heap
    void insertGen(type recipe);// insert function for minheap sorted alphabetically
    void searchIngredient(vector<string>& ingredients, vector<Recipe *>& recipes);
    vector<type> extract();
private:
    bool leaf(int position);
    int parent(int position);
    int leftC(int position);
    int RightC(int position);
    void minHeapify2(vector<type>& h, int i);
};




template <typename type>
int minHeap<type>::RightC(int position) {
    return (2*position)+2;
}
template <typename type>
int minHeap<type>::leftC(int position) {
    return 2*position+1;
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
vector<Recipe *> minHeap<type>::searchName(string name) {
    for (int i = 0; i < size; i++) {
        if (Heap[i].first.find(name) != string::npos) {
            littleGuy.push_back(Heap[i]);
        }
    }
    vector<Recipe*> copy;
    for(int i = 0; i < littleGuy.size(); i++) {
        copy.push_back(littleGuy[i].second);
    }
    littleGuy.clear(); //clears the subHeap for when search is called again
    return copy;
}
template <typename type>
minHeap<type>::minHeap(int _cap) {
    cap = _cap;
    size = 0;
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
void minHeap<type>::searchIngredient(vector<string> &ingredients, vector<Recipe *> &recipes) {
    for(int i = 0; i < size; i++) {
        vector<string> ingredientsCurr = Heap[i].second->getIngredients();
        if (std::includes(ingredientsCurr.begin(), ingredientsCurr.end(), ingredients.begin(),ingredients.end())) {
            recipes.push_back(Heap[i].second);
        }
    }
}


template<typename type>
vector<type> minHeap<type>::extract() {
    vector<type> t;
    vector<type> k = Heap;

    while(!k.empty()) {
        t.push_back(k[0]);
        k[0] = k[k.size()-1];
        k.pop_back();

        minHeapify2(k,0);

    }

    return t;
}

template<typename type>
void minHeap<type>::minHeapify2(vector<type>& h, int i) {
    int l = leftC(i);
    int r = RightC(i);
    int smallest = i;
    if((l < h.size()) && (h[l] < h[smallest])) {
        smallest = l;
    }
    if((r < h.size()) && (h[r] < h[smallest])) {
        smallest = r;
    }
    if(smallest != i) {
        type t = h[i];
        h[i] = h[smallest];
        h[smallest] = t;
        minHeapify2(h,smallest);
    }
}
