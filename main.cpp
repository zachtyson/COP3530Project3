#include <iostream>
#include "BTree.h"
#include "Recipe.h"
#include "heap.cpp"
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

bool number(const string& string)
{
    for (char const i : string) {
        if (std::isdigit(i) == 0) 
        {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream input("RecipeDataset.csv", ios::in);
    string curr;
    getline(input, curr);
    vector<Recipe *> recipes;
    while (getline(input, curr)) {
        recipes.push_back(new Recipe(curr));
    }
    cout << "Welcome to Cooking by the Book!" << endl;
    cout << "We have over 200,000 recipes are our disposal, fit for your needs! What are you looking for today?" << endl;
    cout << "Enter in 1 if you would like to: Get a list of the fastest recipes to cook!" << endl;
    cout << "Enter in 2 if you would like to: Get a list of the healthiest recipes to cook!" << endl;

    string option;
    cin >> option;

    if(number(option) == false)
    {
        cout << "Oh oh you input an unrecoginzable value, please re-run Cooking by the Book!" << endl;
        return 0;
    }else
    {
        if(option != "1" && option != "2")
        {
            cout << "Oh oh you input an unrecoginzable value, please re-run Cooking by the Book!" << endl;
            return 0;
        }
    }
    minHeap Heap = minHeap(recipes.size());
    if(option == "1")
    {
        //minHeap Heap = minHeap(recipes.size());
        for(int i = 0; i < recipes.size(); i++)
        {
            Heap.insertTime(recipes[i]);
        }
    }
    else
    {
        //minHeap Heap = minHeap(recipes.size());
        for(int i = 0; i < recipes.size(); i++)
        {
            Heap.insertCal(recipes[i]);
        }
    }

    Heap.printTop();
}