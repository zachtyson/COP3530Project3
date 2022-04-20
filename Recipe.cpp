//
// Created by Zachary on 4/14/2022.
//

#include "Recipe.h"
#include <algorithm>

Recipe::Recipe(string curr) {
    auto s = curr.find(',');
    name = curr.substr(0,s); //Grabs name
    curr = curr.substr(s+1,curr.length());
    s = curr.find(',');
    ID = stoi(curr.substr(0,s)); //Grabs ID (unused)
    curr = curr.substr(s+1,curr.length());
    s = curr.find(',');
    time = stoi(curr.substr(0,s)); //Grabs time (minutes)
    curr = curr.substr(s+3, curr.length());
    s = curr.find(']');
    string tags = curr.substr(0,s); //Grabs tags (unused)
    curr = curr.substr(s+5, curr.length());
    s = curr.find(']');
    string nutrients = curr.substr(0,s); //Grabs nutrients
    curr = curr.substr(s+3,curr.length());
    setNutrients(nutrients);
    setIngredients(curr);
    setTags(tags);
}

void Recipe::printRecipe() {
    //NutrientsList: Calories,Sugar (%DV), Total Fat(%DV), Sodium (%DV)
//Protein (%DV), Saturated Fat (%DV), Carbohydrates (%DV)
    cout<<"Name: "<<name<<"\n"<<"Time: "<<time<<" minutes";
//    cout<<"\nTags:";
//    for(auto & i : tagsList) {
//        cout<<" "<<i;
//    }
    cout<<"\nNutrients: ";
    cout<<"\tCalories: "<<nutrientsList[0]<<" kcal";
    cout<<"\tSugar: "<<nutrientsList[1]<<"% DV";
    cout<<"\tTotal Fat: "<<nutrientsList[2]<<"% DV";
    cout<<"\tSodium: "<<nutrientsList[3]<<"% DV";
    cout<<"\tProtein: "<<nutrientsList[4]<<"% DV";
    cout<<"\n\t\tSaturated Fat: "<<nutrientsList[5]<<"% DV";
    cout<<"\tCarbohydrates: "<<nutrientsList[6]<<"% DV";
    cout<<"\nIngredients:";
    for(auto & i : ingredientsList) {
        cout<<" '"<<i<<"'";
    }
    cout<<endl;
}

void Recipe::setNutrients(string nutrients) {
    string k = nutrients;
    auto s = nutrients.find(',');
    //Iterates over entire string searching for commas
    for(int i = 0; i < 7; i++){
        s = k.find(',');
        nutrientsList.push_back(stof(k.substr(0,s)));
        k = k.substr(s+1,k.length());
    }
}

void Recipe::setIngredients(string ingredients) {
    //Iterates over entire string to find all ingredients
    //Honestly looks like black magic
    //O(l) time with l = length
    string s;
    bool state = false;
    for(char ingredient : ingredients) { //Once it finds a ' it adds everything after it to string s until it finds another '
        //Once it finds another ' it pushes the string to the vector
        if(ingredient == '\'') {
            if(state) {
                ingredientsList.push_back(s);
                s = "";
            }
            state = !state;
            continue;
        }
        if(state) {
            s.push_back(ingredient);
        }
    }
    std::sort(ingredientsList.begin(), ingredientsList.end());
    numIngredients = ingredientsList.size();
}

string Recipe::getName() const{
    return name;
}

__attribute__((unused)) int Recipe::getID() const {
    return ID; //unused
}

int Recipe::getTime() const {
    return time;
}

__attribute__((unused)) vector<string> Recipe::getTags() const {
    return tagsList; //unused
}

vector<float> Recipe::getNutrients() const {
    return nutrientsList;
}

vector<string> Recipe::getIngredients() const {
    return ingredientsList;
}

void Recipe::setTags(string tags) {
    string k = tags;
    string s;
    bool state = false;
    //Iterates over entire string to find all tags
    //Honestly looks like black magic
    //O(l) time with l = length
    for(char tag : tags) {
        if(tag == '\'') {
            if(state) {
                tagsList.push_back(s);
                s = "";
            }
            state = !state;
            continue;
        }
        if(state) {
            s.push_back(tag);
        }
    }
    numTags = tagsList.size();
}

bool operator==(const Recipe &recipe1, const Recipe &recipe2) {
    //Compares all attributes
    //This should always return false since there are no duplicate names in the dataset
    if(recipe1.name != recipe2.name) {
        return false;
    }
    if(recipe1.nutrientsList != recipe2.nutrientsList) {
        return false;
    }
    if(recipe1.tagsList != recipe2.tagsList) {
        return false;
    }
    if(recipe1.time != recipe2.time) {
        return false;
    }
    return true;
    //Comparing two recipes, I know they may have different ingredients but this is intended for comparison when
    //inserting elements into B-Tree, and this function may or may not ever be used
}

bool operator!=(const Recipe &recipe1, const Recipe &recipe2) {
    //Compares all attributes
    //This should always return true since there are no duplicate names in the dataset
    if(recipe1.name != recipe2.name) {
        return true;
    }
    if(recipe1.nutrientsList != recipe2.nutrientsList) {
        return true;
    }
    if(recipe1.tagsList != recipe2.tagsList) {
        return true;
    }
    if(recipe1.time != recipe2.time) {
        return true;
    }
    return false;
}

bool operator<(const Recipe &recipe1, const Recipe &recipe2) {
    return recipe1.name < recipe2.name;
    //Compares the string values of each name, used by heap/btree
}

bool operator>(const Recipe &recipe1, const Recipe &recipe2) {
    return recipe1.name > recipe2.name;
}
