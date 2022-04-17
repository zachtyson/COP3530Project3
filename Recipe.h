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
    void setIngredients();
    void writeToFile(ofstream& s); //Testing purposes only
private:
    string name;
    string ID;
    string time;
    string tags;
    string nutrients;
    vector<float> nutrientsList;
    string ingredients;
    vector<string> ingredientsList;
    int numIngredients;
};
//NutrientsList: Calories,Sugar (%DV), Total Fat(%DV), Sodium (%DV)
//Protein (%DV), Saturated Fat (%DV), Carbohydrates (%DV)

#endif //UNTITLED4_RECIPE_H
