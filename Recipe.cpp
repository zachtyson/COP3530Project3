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
    nutrients = curr.substr(0,s);
    curr = curr.substr(s+3,curr.length());
    ingredients = curr;
}

void Recipe::printRecipe() {
    cout<<"Name: "<<name<<"\nID: "<<stoi(ID)<<"\nTime:"<<time<<"\nTags: "<<tags<<"\nNutrients: "<<nutrients <<"\nIngredients: " <<ingredients<<endl;
}
