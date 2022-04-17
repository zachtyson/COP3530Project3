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
    ifstream input("reduced.csv", ios::in);
    string curr;
    getline(input, curr);
    vector<Recipe *> recipes;
    //ofstream test2;
    //test2.open("test2.txt");
    //int i = 0;
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    start = std::chrono::system_clock::now();
    
    while (getline(input, curr)) {
        recipes.push_back(new Recipe(curr));
        //recipes[i]->writeToFile(test2);
        //i++;
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
    }
    else
    {
        if(option != "1" || option != "2")
        {
            cout << "Oh oh you input an unrecoginzable value, please re-run Cooking by the Book!" << endl;
            return 0;
        }
    }
    
    if(option == "1")
    {
        minHeap Heap = minHeap(recipes.size());
        for(int i = 0; i < recipes.size(); i++)
        {
            Heap.insertTime(recipes[i]);
        }
    }
    else
    {
        minHeap Heap = minHeap(recipes.size());
        for(int i = 0; i < recipes.size(); i++)
        {
            Heap.insertCal(recipes[i]);
        }
    }

    Heap.printTop();
    
//    end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//    std::cout << "Finished computation at " << std::ctime(&end_time)<< "Time to Parse Data: " << elapsed_seconds.count() << "s\n";

}