#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include "Recipe.h"
using namespace std;  

//Heap structure and associated functions.

class minHeap
{
    private:
    vector<Recipe*> Heap;
    int size;
    int cap;

    public:
    minHeap(int cap) //cookingTime
    {
        this->cap = cap;
        this->size = 0;
    }

    void insertTime(Recipe* recipe) //cookingTime insert function
    {
        if (size >= cap)
        {
            return;
        }
        Heap.push_back(recipe);
        int lastNode = size;

        //code to do
        while (Heap[lastNode]->getTime() < Heap[parent(lastNode)]->getTime()) //make this based on cookingTime/numIngredients e.g Heap[lastNode].cookingTime
        {
            swap(lastNode, parent(lastNode));
            lastNode = parent(lastNode);
        }
    }

    private:
    bool leaf(int position)
    {
        if (position > (size/2) && position <= size) //g4g indicated that a leaf could be detected with this math
        {
            return true;
        }
        return false;
    }
    
    int parent(int position)
    {
        return floor(position/2);
    }

    int leftC(int position)
    {
        return 2*position;
    }

    int RightC(int position)
    {
        return (2*position)+1;
    }

    void swap(int first, int second)
    {
        Recipe* temp;
        temp  = Heap[second];
        Heap[first] = Heap[second];
        Heap[second] = temp; 
    }

    void minHeapifyTime(int position) //make this based on cookingTime/numIngredients e.g Heap[position].cookingTime
    {
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
}