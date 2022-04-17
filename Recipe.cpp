//
// Created by Zachary on 4/14/2022.
//

#include "Recipe.h"

Recipe::Recipe(string curr) {
    auto s = curr.find(',');
    name = curr.substr(0,s);
    curr = curr.substr(s+1,curr.length());
    s = curr.find(',');
    ID = curr.substr(0,s);
    curr = curr.substr(s+1,curr.length());
    s = curr.find(',');
    time = curr.substr(0,s);
    curr = curr.substr(s+3, curr.length());
    s = curr.find(']');
    tags = curr.substr(0,s);
    curr = curr.substr(s+5, curr.length());
    s = curr.find(']');
    string nutrients = curr.substr(0,s);
    curr = curr.substr(s+3,curr.length());
    setNutrients(nutrients);
    setIngredients(curr);
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
    s<<"Tags: "<<tags<<endl;
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
