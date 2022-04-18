//
// Created by Zachary on 4/14/2022.
//

#include "Recipe.h"

Recipe::Recipe(string curr) {
    auto s = curr.find(',');
    name = curr.substr(0,s);
    curr = curr.substr(s+1,curr.length());
    s = curr.find(',');
    ID = stoi(curr.substr(0,s));
    curr = curr.substr(s+1,curr.length());
    s = curr.find(',');
    time = stoi(curr.substr(0,s));
    curr = curr.substr(s+3, curr.length());
    s = curr.find(']');
    string tags = curr.substr(0,s);
    curr = curr.substr(s+5, curr.length());
    s = curr.find(']');
    string nutrients = curr.substr(0,s);
    curr = curr.substr(s+3,curr.length());
    setNutrients(nutrients);
    setIngredients(curr);
    setTags(tags);
}

void Recipe::printRecipe() {
    //cout<<"Name: "<<name<<"\nID: "<<stoi(ID)<<"\nTime:"<<time<<"\nTags: "<<tags<<"\nNutrients: "<<nutrients <<"\nIngredients: " <<ingredients<<endl;
}

void Recipe::setNutrients(string nutrients) {
    auto s = nutrients.find(',');
    string k = nutrients;
    nutrientsList.push_back(stof(k.substr(0,s)));
    k = k.substr(s+1,k.length());
    s = k.find(',');
    nutrientsList.push_back(stof(k.substr(0,s)));
    k = k.substr(s+1,k.length());
    s = k.find(',');
    nutrientsList.push_back(stof(k.substr(0,s)));
    k = k.substr(s+1,k.length());
    s = k.find(',');
    nutrientsList.push_back(stof(k.substr(0,s)));
    k = k.substr(s+1,k.length());
    s = k.find(',');
    nutrientsList.push_back(stof(k.substr(0,s)));
    k = k.substr(s+1,k.length());
    s = k.find(',');
    nutrientsList.push_back(stof(k.substr(0,s)));
    k = k.substr(s+1,k.length());
    s = k.find(',');
    nutrientsList.push_back(stof(k.substr(0,s)));
}

void Recipe::setIngredients(string ingredients) {
    string k = ingredients;
    string s;
    bool state = false;
    for(char ingredient : ingredients) {
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
    numIngredients = ingredientsList.size();
}

void Recipe::writeToFile(ofstream& s) {
    s<<"Name: "<<name<<endl;
    s<<"ID: "<<ID<<endl;
    s<<"Time: "<<time<<endl;
    s<<"#Tags: "<<numTags<<endl;
    s<<"Tags: ";
    for(auto & i : tagsList) {
        s<<" '"<<i<<"'";
    }
    s<<endl;
    s<<"Nutrients: '"<<nutrientsList[0]<<" Calories' '"<<nutrientsList[1]<<"% Sugar' '";
    s<<nutrientsList[2]<<"% Total Fat' '"<<nutrientsList[3]<<"% Sodium' '"<<nutrientsList[4];
    s<<"% Protein' '"<<nutrientsList[5]<<"% Saturated Fat' '"<<nutrientsList[6]<<"% Carbohydrates'"<<endl;
    s<<"# Ingredients: "<<numIngredients<<endl;
    s<<"Ingredients:";
    for(auto & i : ingredientsList) {
        s<<" '"<<i<<"'";
    }
    s<<endl;
    s<<endl;
}

string Recipe::getName() const{
    return name;
}

int Recipe::getID() const {
    return ID;
}

int Recipe::getTime() const {
    return time;
}

vector<string> Recipe::getTags() const {
    return tagsList;
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
    //Compares the string values of each name, might be used by B Tree
}

bool operator>(const Recipe &recipe1, const Recipe &recipe2) {
    return recipe1.name > recipe2.name;
    //All four of these operator overloaded functions might be unused, added just in case
}
