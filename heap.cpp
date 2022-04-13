#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using namespace std;  

//Heap structure and associated functions.
struct Node
{
    string recipeName;
    int calories;
    int cookingTime;
    vector<string> tags;
    vector<string> ingredients;

    Node()
    {
        recipeName = "";
        calories = -1;
        cookingTime = -1;
    }

    Node(string recipeName, int calories, int cookingTime, vector<string> tags, vector<string> ingredients)
    {
        this.recipeName = recipeName;
        this.calories = calories;
        this.cookingTime = cookingTime;
        this.tags = tags;
        this.ingredients = ingredients;
    }
}

class minHeap
{
    private:
    Node[] Heap;
    int size;
    int cap;

    public:
    minHeap(int cap)
    {
        this.cap = cap;
        this.size = 0;
        Heap = new Node[this.cap + 1];
        Heap[0] = Integer.MIN_VALUE;
    }

    insert(Node recipe)
    {
        if (size >= maxSize)
        {
            return;
        }
        Heap[++size] = recipe;
        int lastNode = size;

        //code to do
        while (Heap[lastNode] < Heap[parent(lastNode)])
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
        Node temp;
        temp  = Heap[second];
        Heap[first] = Heap[second];
        Heap[second] = temp; 
    }

    void minHeapify(int position)
    {
        if(leaf(position == false))
        {
            if(Heap[position] > Heap[leftC(position)]) || Heap[position] > Heap[RightC(position)])
            {
                
            }
        }
    }
}