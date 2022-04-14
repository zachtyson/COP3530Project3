//
// Created by Zachary on 4/14/2022.
//

#ifndef UNTITLED4_RECIPE_H
#define UNTITLED4_RECIPE_H
#include <iostream>
#include <fstream>
using namespace std;
class Recipe {
public:
    Recipe(string curr);
    void printRecipe();
private:
    string name;
    string ID;
    string time;
    string tags;
    string nutrients;
    string ingredients;
};


#endif //UNTITLED4_RECIPE_H
