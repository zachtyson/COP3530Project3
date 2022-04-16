//
// Created by Zachary on 4/14/2022.
//

#ifndef UNTITLED4_RECIPE_H
#define UNTITLED4_RECIPE_H
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Recipe {
public:
    Recipe(string curr);
    void printRecipe();
    void setNutrients();
private:
    string name;
    string ID;
    string time;
    string tags;
    string nutrients;
    vector<float> nutrientsList;
    string ingredients;
};
//NutrientsList: Calories, Total Fat(%DV), Sodium (%DV)
//Protein (%DV), Saturated Fat (%DV), Carbohydrates (%DV)

#endif //UNTITLED4_RECIPE_H
