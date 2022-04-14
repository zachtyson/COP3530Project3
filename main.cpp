#include <iostream>
#include "Recipe.h"
#include <vector>
#include <fstream>
using namespace std;
int main() {
    ifstream input("reduced.csv", ios::in);
    string curr;
    //ofstream output("output.csv");
    int i = 0;
    getline(input,curr);
    //output<<curr<<"\n";
    vector<Recipe*> recipes;
    while(getline(input,curr)) {
        recipes.push_back(new Recipe(curr));
    }
    cout<<recipes.size();
}