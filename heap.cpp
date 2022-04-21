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
    vector<type> Heap; //vector based heap representation
    vector<type> littleGuy; //sub heap that contains an input string for searching recipes based on name within the primary minHeap (not in use atm)
    int size = 0; //current size of the heap
    int sizeLG = 0; //current size of the subHeap (not in use atm)
    int cap; //max size of the heap, was initialy intended to be used for an array based heap representation, but now is used to ensure that only the total number of recipes in the csv are input

    public:
    minHeap(int cap); //creates a minHeap vector with an initial size of 0 and a max size of all the recipes in the data base
    int getSize() const; //returns the size of the heap vector
    vector<Recipe*> searchName(string name); // Added signature for search by name to heap
    void insertGen(type recipe);// insert function for minheap sorted alphabetically
    void printTop(); //prints the first recipe in the heap vector
    void remove(); //removes the first recipe and heapifys the heap
    vector<type>& getHeap(); //returns heap vector
    vector<type> makeMaxHeap(vector<type> Heap); //uses stack to turn minHeap into maxHeap
    void searchIngredient(vector<string>& ingredients, vector<Recipe *>& recipes); //input a heap vector and vector of ingredients to get a sorted vector of recipes that contains all the ingredients input
    vector<type> extract(); //extracts the minheap to a vector in ascending order
private:
    bool leaf(int position); //determines if the input index value is a leaf or not
    int parent(int position); //returns the parent of input index value
    int leftC(int position); //returns the left child of input index value
    int RightC(int position); //returns the right child of input index value
    void swap(int first, int second); //swaps the first index with the second
    void swapLG(int first, int second); //used to swap the sub minHeap but not in use atm
    void minHeapify(int position); //used to minheapify the heap so that the root is always the smallest value and all its children are greater than it
    void minHeapify2(vector<type>& h, int i); //same minheapify but now with an input heap rather than the class heap vector 
};


template <typename type>
void minHeap<type>::swapLG(int first, int second) { //not used in current edition of Cooking by the Book
    type temp;
    temp  = littleGuy[first];
    littleGuy[first] = littleGuy[second];
    littleGuy[second] = temp;
}



template <typename type>
void minHeap<type>::swap(int first, int second) { //first value is a vector index and it is swapped with second value, a different vector index
    type temp;
    temp  = Heap[first];
    Heap[first] = Heap[second];
    Heap[second] = temp;
}

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
vector<type> minHeap<type>::makeMaxHeap(vector<type> Heap) { //turns the minHeap to a maxHeap with the use of a stack
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
void minHeap<type>::remove() { //removes first node by making the last node become the root and then heapifying the tree
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
vector<Recipe *> minHeap<type>::searchName(string name) { //creates a vector of recipes that have the input string in their name

    vector<Recipe*> t;
    vector<type> k = Heap;
    while(!k.empty()) {
        if (k[0].first.find(name) != string::npos) {
            t.push_back(k[0].second);
        }
        k[0] = k[k.size() - 1];
        k.pop_back();

        minHeapify2(k, 0);


    }
    return t;
}
template <typename type>
int minHeap<type>::getSize() const {
    return size;
}
template <typename type>
minHeap<type>::minHeap(int _cap) { //initializes heap to a set size, was mainly done for an array based representation but kept when we switched to a vector heap.
    cap = _cap;
    size = 0;
    sizeLG = 0;
}

template<typename type>
void minHeap<type>::insertGen(type recipe) { //inserts a recipe to the end of the heap vector and does swaps as necessary 
    if (size >= cap){
        return;
    }
    Heap.push_back(recipe);
    int lastNode = size;
    size++;
    while (Heap[lastNode] < Heap[parent(lastNode)]) //swapping done here for newly inserted variables 
    {
        type t = Heap[lastNode];
        Heap[lastNode] = Heap[parent(lastNode)];
        Heap[parent(lastNode)] = t;
        lastNode = parent(lastNode);
    }
//    for(int i = 0; i < size; i++) {
//        cout<<size<<" "<<Heap[i].first<<" "<<Heap[i].second->getName()<<endl;
//    }

}

template<typename type>
void minHeap<type>::minHeapify(int position) { //swaps values around as necessary to make sure the heap is a corect heap (heapifys it)
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
void minHeap<type>::searchIngredient(vector<string> &ingredients, vector<Recipe *> &t) { //similar to searchName, but instead searches a vector of ingredients inside each recipe's ingredient list
    vector<type> k = Heap;
    while(!k.empty()) {
        vector<string> ingredientsCurr = k[0].second->getIngredients();
        if (std::includes(ingredientsCurr.begin(), ingredientsCurr.end(), ingredients.begin(),ingredients.end())) {
            t.push_back(k[0].second);
        }
        k[0] = k[k.size()-1];
        k.pop_back();

        minHeapify2(k,0);

    }

}

template <typename type>
vector<type>& minHeap<type>::getHeap() { //function used to return the heap vector representation 
    return Heap;
}

template<typename type>
vector<type> minHeap<type>::extract() { //extracts the heap vector to a vector of recipes in order
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
void minHeap<type>::minHeapify2(vector<type>& h, int i) { //same as heapify but takes input heap rather than the class heap
    int l = leftC(i);
    int r = RightC(i);
    int smallest = i;
    if((l < h.size()) && (h[l] < h[smallest])) {
        smallest = l;
    }
    if((r < h.size()) && (h[r] < h[smallest])) {
        smallest = r;
    }
    if(smallest != i) { //swapping is done here if conditionals are met
        type t = h[i];
        h[i] = h[smallest];
        h[smallest] = t;
        minHeapify2(h,smallest);
    }
}
