#include <iostream>
#include "Recipe.h"
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;
int main() {
    ifstream input("reduced.csv", ios::in);
    string curr;
    getline(input,curr);
    vector<Recipe*> recipes;
    //ofstream test2;
    //test2.open("test2.txt");
    //int i = 0;
    while(getline(input,curr)) {
        recipes.push_back(new Recipe(curr));
        //recipes[i]->writeToFile(test2);
        //i++;
    }

}