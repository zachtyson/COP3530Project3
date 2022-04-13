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
    int leftChild;
    int rightChild;
    int parent;

    Node()
    {
        recipeName = "";
        calories = -1;
        cookingTime = -1;
        leftChild = -1; 
        rightChild = -1;
        parent = -1;
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
    }

    private:
    void swap(int first, int second)
    {
        Node temp;
        temp  = Heap[second];
        Heap[first] = Heap[second];
        Heap[second] = temp; 
    }

    void minHeapify(int position)
    {

    }
}