#include <iostream>
#include "BTree.h"
#include "Recipe.h"
#include "heap.cpp"
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

bool number(const string& string)
{
    for (char const i : string) {
        if (std::isdigit(i) == 0) 
        {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream input("RecipeDataset.csv", ios::in);
    string curr;
    getline(input, curr);
    vector<Recipe *> recipes;
    while (getline(input, curr)) {
        recipes.push_back(new Recipe(curr));
    }
    cout << "Welcome to Cooking by the Book!" << endl;
    cout << "We have over 200,000 recipes are our disposal, fit for your needs! What are you looking for today?" << endl;
    cout << "Enter in 1 if you would like to: Get a list of the fastest recipes to cook!" << endl;
    cout << "Enter in 2 if you would like to: Get a list of the healthiest recipes to cook!" << endl;

    string option;
    cin >> option;

    if(number(option) == false)
    {
        cout << "Oh oh you input an unrecoginzable value, please re-run Cooking by the Book!" << endl;
        return 0;
    }else
    {
        if(option != "1" && option != "2")
        {
            cout << "Oh oh you input an unrecoginzable value, please re-run Cooking by the Book!" << endl;
            return 0;
        }
    }
    minHeap Heap = minHeap(recipes.size());
    BTree<pair<float, Recipe*>> BTree;
    time_point<system_clock> start, end;
    string calTimeChoice;
    if(option == "1")
    {
        calTimeChoice = "minutes";
        //minHeap Heap = minHeap(recipes.size());
        start = system_clock::now();
        for(int i = 0; i < recipes.size(); i++)
        {
            Heap.insertTime(recipes[i]);
        }
        end = system_clock::now();
        auto ms = duration_cast<milliseconds>(end-start);
        cout<<"Heap Constructed in: "<<ms.count()<<"ms"<<endl;

        start = system_clock::now();
        for(auto & recipe : recipes) {
            BTree.insert(make_pair(recipe->getTime(),recipe));
        }
        end = system_clock::now();
        ms = duration_cast<milliseconds>(end-start);
        cout<<"BTree Constructed in: "<<ms.count()<<"ms"<<endl;

    }
    else
    {
        //minHeap Heap = minHeap(recipes.size());
        calTimeChoice = "calories";
        start = system_clock::now();
        for(int i = 0; i < recipes.size(); i++)
        {
            Heap.insertCal(recipes[i]);
        }
        end = system_clock::now();
        auto ms = duration_cast<milliseconds>(end-start);
        cout<<"Heap Constructed in: "<<ms.count()<<"ms"<<endl;

        start = system_clock::now();
        for(auto & recipe : recipes) {
            BTree.insert(make_pair(recipe->getNutrients()[0],recipe));
        }
        end = system_clock::now();
        ms = duration_cast<milliseconds>(end-start);
        cout<<"BTree Constructed in: "<<ms.count()<<"ms"<<endl;
    }
    int order;
    string userInput;
    float userOption;
    while (true) {
        cout<<"Would you like to sort ascending or descending?"<<endl;
        cout<<"1: Ascending"<<endl;
        cout<<"2: Descending"<<endl;
        cout<<"3: Exit"<<endl;
        cin>>userInput;
        try {
           order = stoi(userInput);
           if(order == 1 || order == 2 || order == 3) {
               if(order == 3) {
                   cout<<"Well, I suppose this is Goodbye"<<endl;
                   return 0;
               }
               if(order == 1) {
                   cout<<"Sorting ascending"<<endl;
               }else {
                   cout<<"Sorting descending"<<endl;
               }
               break;
           } else{
               throw std::invalid_argument("Invalid Command");
           }
        } catch (exception& e){
            cout<<"Unrecognized Command"<<endl;
        }
    }
    cout<<"What is the ";
    if(order == 1) {
        cout<<"minimum";
    } else {
        cout<<"maximum";
    }
    cout<< " number of "<<calTimeChoice<<"?"<<endl;
    cin>>userInput;
    try {
        userOption = stof(userInput);
    } catch (exception& e) {
        cout<<"Unrecognized value, defaulting to ";
        if(order == 1) {
            cout<<"minimum ";
        } else {
            cout<<"maximum ";
        }
        userOption = -1;
        cout<<calTimeChoice<<endl;
    }
    if(order == 1) {
        queue<pair<float, Recipe*>> q;
        BTree.inorder(q);
        if(userOption != -1) {
            while(true) {
                if(q.front().first >= userOption) {
                    break;
                }
                q.pop();
            }
        }
        while(!q.empty()) {
            q.front().second->printRecipe();
            q.pop();
            cout<<"Would you like to view another recipe?"<<endl;
            cout<<"Y: Yes"<<endl;
            cout<<"N: No"<<endl;
            string viewAnother;
            cin>>viewAnother;
            if(viewAnother != "Yes") {
                cout<<"Okay, no more recipes"<<endl;
                break;
            }
        }
    } else {
        stack<pair<float, Recipe*>> s;
        BTree.revorder(s);
        if(userOption != -1) {
            while(true) {
                if(s.top().first <= userOption) {
                    break;
                }
                s.pop();
            }
        }
        while(!s.empty()) {
            s.top().second->printRecipe();
            s.pop();
            cout<<endl;
            cout<<"Would you like to view another recipe?"<<endl;
            cout<<"1: Yes";
            cout<<"\t2: No"<<endl;
            string viewAnother;
            cin>>viewAnother;
            if(viewAnother != "1") {
                cout<<"Okay, no more recipes"<<endl;
                break;
            }
        }
    }
    //Heap.printTop();
    //BTree.inorder();
}