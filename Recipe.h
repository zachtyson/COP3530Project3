//
// Created by Zachary on 4/14/2022.
//

#ifndef PROJECT3_RECIPE_H
#define PROJECT3_RECIPE_H
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
    string getName() const;
    __attribute__((unused)) int getID() const;
    int getTime() const ;
    __attribute__((unused)) vector<string> getTags() const;
    vector<float> getNutrients() const;
    vector<string> getIngredients()const;
    friend bool operator==(const Recipe& recipe1, const Recipe& recipe2);
    friend bool operator!=(const Recipe& recipe1, const Recipe& recipe2);
    friend bool operator<(const Recipe& recipe1, const Recipe& recipe2);
    friend bool operator>(const Recipe& recipe1, const Recipe& recipe2);
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

#endif //PROJECT3_RECIPE_H
