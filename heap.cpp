#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <math.h>
#include <stack>
#include "Recipe.h"
using namespace std;  

//Heap structure and associated functions.
class minHeap
{
    private:
    vector<Recipe*> Heap;
    vector<Recipe*> littleGuy; //sub heap that contains an input string for searching recipes based on name within the primary minHeap
    int size = 0;
    int sizeLG = 0;
    int cap;

    public:
    minHeap(int cap); //creates a minHeap vector wuth an initial size of 0 and a max size of all the recipes in the data base
    int getSize() const;
    vector<Recipe*> searchName(string name); // Added signature for search by name to heap
    void insertName(Recipe* recipe); // insert function for minheap sorted alphabetically
    void insertTime(Recipe* recipe); //cookingTime insert function
    void insertCal(Recipe* recipe); // insert function for minHeap based on calories
    void printTop();
    void removeTime();
    void removeCal();
    vector<Recipe*> makeMaxHeap(vector<Recipe*> Heap); //uses stack to turn minHeap into maxHeap
private:
    bool leaf(int position);
    int parent(int position);
    int leftC(int position);
    int RightC(int position);
    void swap(int first, int second);
    void swapLG(int first, int second);
    void minHeapifyTime(int position); //minHeapify function that sorts the heap from least time to make to most
    void minHeapifyCal(int position); //minHeapify function that sorts the heap from most nutritious (least calories) to least nutritious (most calories)
    void minHeapifyName(int position); //minHeapify function that sorts the subHeap, the heap made from a searched input string, in alphabetical order
};

void minHeap::minHeapifyName(int position) //minHeapify function that sorts the subHeap, the heap made from a searched input string, in alphabetical order
{
    if(leaf(position == false))
    {
        if(littleGuy[position]->getName() > littleGuy[leftC(position)]->getName() || littleGuy[position]->getName() > littleGuy[RightC(position)]->getName())
        {
            if(littleGuy[leftC(position)]->getName() < littleGuy[RightC(position)]->getName())
            {
                swap(position, leftC(position));
                minHeapifyName(leftC(position));
            }
            else
            {
                swap(position, RightC(position));
                minHeapifyName(RightC(position));
            }
        }
    }
}

void minHeap::minHeapifyCal(int position) {
    if(leaf(position == false)) {
        if(Heap[position]->getNutrients()[0] > Heap[leftC(position)]->getNutrients()[0] || Heap[position]->getNutrients()[0] > Heap[RightC(position)]->getNutrients()[0]){
            if(Heap[leftC(position)]->getNutrients()[0] < Heap[RightC(position)]->getNutrients()[0]){
                swap(position, leftC(position));
                minHeapifyCal(leftC(position));
            }
            else {
                swap(position, RightC(position));
                minHeapifyCal(RightC(position));
            }
        }
    }
}

void minHeap::minHeapifyTime(int position) {
    if(leaf(position == false))
    {
        if(Heap[position]->getTime() > Heap[leftC(position)]->getTime() || Heap[position]->getTime() > Heap[RightC(position)]->getTime())
        {
            if(Heap[leftC(position)]->getTime() < Heap[RightC(position)]->getTime())
            {
                swap(position, leftC(position));
                minHeapifyTime(leftC(position));
            }
            else
            {
                swap(position, RightC(position));
                minHeapifyTime(RightC(position));
            }
        }
    }
}

void minHeap::swapLG(int first, int second) {
    Recipe* temp;
    temp  = littleGuy[first];
    littleGuy[first] = littleGuy[second];
    littleGuy[second] = temp;
}

void minHeap::swap(int first, int second) {
    Recipe* temp;
    temp  = Heap[first];
    Heap[first] = Heap[second];
    Heap[second] = temp;
}

int minHeap::RightC(int position) {
    return (2*position)+1;
}

int minHeap::leftC(int position) {
    return 2*position;
}

int minHeap::parent(int position) {
    return floor(position/2);
}

bool minHeap::leaf(int position) {
    if (position > (size/2) && position <= size) //g4g indicated that a leaf could be detected with this math
    {
        return true;
    }
    return false;
}

vector<Recipe *> minHeap::makeMaxHeap(vector<Recipe *> Heap) {
    stack<Recipe*> maxHeap;
    for(auto & i : Heap)
    {
        maxHeap.push(i);
    }
    vector<Recipe*> max;
    while(!maxHeap.empty())
    {
        max.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return max;
}

void minHeap::removeCal() {
    Heap[0] = Heap[size - 1];
    Heap.pop_back();
    minHeapifyCal(0);
    size--;
}

void minHeap::removeTime() {
    Heap[0] = Heap[size - 1];
    Heap.pop_back();
    minHeapifyTime(0);
    size--;
}

void minHeap::printTop() {
    Heap[0]->printRecipe();
}

void minHeap::insertCal(Recipe *recipe) {
    if (size >= cap)
    {
        return;
    }
    Heap.push_back(recipe);
    int lastNode = size;
    size++;

    while (Heap[lastNode]->getNutrients()[0] < Heap[parent(lastNode)]->getNutrients()[0])
    {
        swap(lastNode, parent(lastNode));
        lastNode = parent(lastNode);
    }
}

void minHeap::insertTime(Recipe *recipe) {
    if (size >= cap)
    {
        return;
    }
    Heap.push_back(recipe);
    int lastNode = size;
    size++;

    while (Heap[lastNode]->getTime() < Heap[parent(lastNode)]->getTime())
    {
        swap(lastNode, parent(lastNode));
        lastNode = parent(lastNode);
    }
}

void minHeap::insertName(Recipe *recipe) {
    littleGuy.push_back(recipe);
    int lastNode = sizeLG;
    sizeLG++;

    while (littleGuy[lastNode]->getName().compare(littleGuy[parent(lastNode)]->getName()) < 0)
    {
        swapLG(lastNode, parent(lastNode));
        lastNode = parent(lastNode);
    }
}

vector<Recipe *> minHeap::searchName(string name) {
    for (int i = 0; i < size; i++) {
        if (Heap[i]->getName().find(name) != string::npos) {
            insertName(Heap[i]);
        }
    }
    sizeLG = 0;
    vector<Recipe*> copy = littleGuy;
    littleGuy.clear(); //clears the subHeap for when search is called again
    return copy;
}

int minHeap::getSize() const {
    return size;
}

minHeap::minHeap(int cap) {
    this->cap = cap;
    this->size = 0;
    this->sizeLG =0;
}

