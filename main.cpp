#include <iostream>
#include "Recipe.h"
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;
int main() {
    ifstream input("reduced.csv", ios::in);
    string curr;
    getline(input, curr);
    vector<Recipe *> recipes;
    //ofstream test2;
    //test2.open("test2.txt");
    //int i = 0;
//    std::chrono::time_point<std::chrono::system_clock> start, end;
//    start = std::chrono::system_clock::now();
    while (getline(input, curr)) {
        recipes.push_back(new Recipe(curr));
        //recipes[i]->writeToFile(test2);
        //i++;
    }
//    end = std::chrono::system_clock::now();
//    std::chrono::duration<double> elapsed_seconds = end - start;
//    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//    std::cout << "Finished computation at " << std::ctime(&end_time)<< "Time to Parse Data: " << elapsed_seconds.count() << "s\n";

}