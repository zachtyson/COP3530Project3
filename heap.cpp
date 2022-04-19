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
    vector<Recipe*> littleGuy;
    int size = 0;
    int cap;

    public:
    minHeap(int cap) //cookingTime
    {
        this->cap = cap;
        this->size = 0;
    }

    int getSize() {
        return size;
    }

    vector<Recipe*> searchName(string name) { // Added signature for search by name to heap
        for (int i = 0; i < size; i++) {
            if (Heap[i]->getName().find(name) != string::npos) {
                littleGuy.push_back(Heap[i]);
                minHeapifyName(0);
            }
        }
        vector<Recipe*> copy = littleGuy;
        littleGuy.clear();
        return copy;
    }

    void insertTime(Recipe* recipe) //cookingTime insert function
    {
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

    void insertCal(Recipe* recipe) //calories insert function
    {
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
    
    void printTop()
    {
        Heap[0]->printRecipe();
    }

    void removeTime() { // Could very well be wrong. Assuming position is meant to be root.
        Heap[0] = Heap[size - 1];
        Heap.pop_back();
        minHeapifyTime(0);
        size--;
    }

    void removeCal() {
        Heap[0] = Heap[size - 1];
        Heap.pop_back();
        minHeapifyCal(0);
        size--;
    }

    vector<Recipe*> makeMaxHeap(vector<Recipe*> Heap)
    {
        stack<Recipe*> maxHeap;
        for(int i = 0; i < Heap.size(); i++)
        {
            maxHeap.push(Heap[i]);
        }
        vector<Recipe*> max;
        while(maxHeap.empty() == false)
        {
            max.push_back(maxHeap.top());
            maxHeap.pop();
        }
        return max;
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
        temp  = Heap[first];
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

    void minHeapifyCal(int position) //make this based on cookingTime/numIngredients e.g Heap[position].cookingTime
    {
        if(leaf(position == false))
        {
            if(Heap[position]->getNutrients()[0] > Heap[leftC(position)]->getNutrients()[0] || Heap[position]->getNutrients()[0] > Heap[RightC(position)]->getNutrients()[0])
            {
                if(Heap[leftC(position)]->getNutrients()[0] < Heap[RightC(position)]->getNutrients()[0])
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

    void minHeapifyName(int position) //make this based on cookingTime/numIngredients e.g Heap[position].cookingTime
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
};