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
    void setNutrients(string nutrients);
    void setIngredients(string ingredients);
    void setTags(string tags);
    void writeToFile(ofstream& s); //Testing purposes only
    string getName() const;
    int getID() const;
    int getTime() const ;
    vector<string> getTags() const;
    vector<float> getNutrients() const;
    vector<string> getIngredients()const;
private:
    string name;
    int ID;
    int time;
    vector<string> tagsList;
    vector<float> nutrientsList;
    vector<string> ingredientsList;
    int numIngredients;
    int numTags;
};
//NutrientsList: Calories,Sugar (%DV), Total Fat(%DV), Sodium (%DV)
//Protein (%DV), Saturated Fat (%DV), Carbohydrates (%DV)

#endif //UNTITLED4_RECIPE_H
