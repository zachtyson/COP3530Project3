#include <iostream>
#include "Recipe.h"
#include <vector>
#include <fstream>
using namespace std;
int main() {
    ifstream input("reduced.csv", ios::in);
    string curr;
    getline(input,curr);
    vector<Recipe*> recipes;
    while(getline(input,curr)) {
        recipes.push_back(new Recipe(curr));
    }
    cout<<recipes.size()<<endl;
}