#include <iostream>
#include "BTree.h"
#include "Recipe.h"
#include "heap.cpp"
#include <vector>
#include <fstream>
#include <chrono>

#define timeUnitName " microseconds"
#define timeUnit std::chrono::microseconds
using namespace std;
using namespace std::chrono;
void parseData(vector<Recipe *>& recipes, string fileName) {
    ifstream input(fileName, ios::in);
    string curr;
    getline(input, curr);
    while (getline(input, curr)) {
        recipes.push_back(new Recipe(curr));
    }
}

void calorieRecipes(vector<Recipe *>& recipes, BTree<pair<float, Recipe*>>& BTree, minHeap& Heap) {
    time_point<system_clock> start, end;
    start = system_clock::now();
    for(auto & recipe : recipes)
    {
        Heap.insertCal(recipe);
    }
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap Constructed in: "<<ms.count()<<timeUnitName<<endl;

    start = system_clock::now();
    for(auto & recipe : recipes) {
        BTree.insert(make_pair(recipe->getNutrients()[0],recipe));
    }
    end = system_clock::now();
    ms = duration_cast<timeUnit>(end-start);
    cout<<"BTree Constructed in: "<<ms.count()<<timeUnitName<<endl;
}

void nameRecipes(vector<Recipe *>& recipes, BTree<pair<string, Recipe*>>& BTree, minHeap& Heap) {
    time_point<system_clock> start, end;
    start = system_clock::now();
    if(Heap.getSize() == 0) {
        for(auto & recipe : recipes)
        {
            Heap.insertCal(recipe);
        }
    }
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap Constructed in: "<<ms.count()<<timeUnitName<<endl;

    start = system_clock::now();
    for(auto & recipe : recipes) {
        BTree.insert(make_pair(recipe->getName(),recipe));
    }
    end = system_clock::now();
    ms = duration_cast<timeUnit>(end-start);
    cout<<"BTree Constructed in: "<<ms.count()<<timeUnitName<<endl;
}

void timeRecipes(vector<Recipe *>& recipes, BTree<pair<float, Recipe*>>& BTree,minHeap& Heap ) {
    time_point<system_clock> start, end;
    //minHeap Heap = minHeap(recipes.size());
    start = system_clock::now();
    for(auto & recipe : recipes)
    {
        Heap.insertTime(recipe);
    }
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap Constructed in: "<<ms.count()<<timeUnitName<<endl;

    start = system_clock::now();
    for(auto & recipe : recipes) {
        BTree.insert(make_pair(recipe->getTime(),recipe));
    }
    end = system_clock::now();
    ms = duration_cast<timeUnit>(end-start);
    cout<<"BTree Constructed in: "<<ms.count()<<timeUnitName<<endl;
}

void Option1or2(minHeap& Heap, BTree<pair<float, Recipe*>>& BTree, string calTimeChoice) {
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
                    cout<<"Returning to main menu"<<endl;
                    return ;
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
        time_point<system_clock> start, end;
        start = system_clock::now();
        if(userOption != -1) {
            while(true) {
                if(q.front().first >= userOption) {
                    break;
                }
                q.pop();
            }
        }
        end = system_clock::now();
        auto ms = duration_cast<timeUnit>(end-start);
        cout<<"Descending constructed in "<<ms.count()<<timeUnitName<<endl;
        while(!q.empty()) {
            q.front().second->printRecipe();
            q.pop();
            cout<<"Would you like to view another recipe?"<<endl;
            cout<<"1 = Another\t 2 = No";
            string viewAnother;
            cin>>viewAnother;
            if(viewAnother != "1") {
                cout<<"Okay, no more recipes"<<endl;
                break;
            }
        }
        if(q.empty()) {
            cout<<"There are no more recipes to display, returning to main menu"<<endl;
        }
    } else if(order == 2){
        stack<pair<float, Recipe*>> s;
        BTree.revorder(s);
        time_point<system_clock> start, end;
        start = system_clock::now();
        if(userOption != -1) {
            while(true) {
                if(s.top().first <= userOption) {
                    break;
                }
                s.pop();
            }
        }
        end = system_clock::now();
        auto ms = duration_cast<timeUnit>(end-start);
        cout<<"Descending constructed in "<<ms.count()<<timeUnitName<<endl;
        while(!s.empty()) {
            s.top().second->printRecipe();
            s.pop();
            cout<<endl;
            cout<<"Would you like to view another recipe?"<<endl;
            cout<<"1 = Another\t 2 = No";
            string viewAnother;
            cin>>viewAnother;
            if(viewAnother != "1") {
                cout<<"Okay, no more recipes"<<endl;
                break;
            }
        }
        if(s.empty()) {
            cout<<"There are no more recipes to display, returning to main menu"<<endl;
        }
    }
}

void Option3(BTree<pair<string, Recipe*>>& BTree, minHeap& Heap) {
    string searchKey;
    cout<<"Enter the name of the food you are trying to search"<<endl;
    cin>>searchKey;
    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);
    time_point<system_clock> start, end;
    start = system_clock::now();
    vector<Recipe*> find;
    BTree.search(searchKey,find);
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"BTree searched in: "<<ms.count()<<timeUnitName<<endl;
    start = system_clock::now();
    vector<Recipe*> nameHeap = Heap.searchName(searchKey);
    end = system_clock::now();
    ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap searched in: "<<ms.count()<<timeUnitName<<endl;
    if(!find.empty()) {
        cout<< "Recipe found: "<<endl;
        cout<<find.size()<<" results"<<endl;
        for(int i = 0 ; i < find.size(); i++) {
            cout<<"'"<<find[i]->getName()<<"' ";
        }
        cout<<endl;
        cout<<endl;
        cout<<nameHeap.size()<<" results"<<endl;
        for(int i = 0 ; i < nameHeap.size(); i++) {
            cout<<"'"<<nameHeap[i]->getName()<<"' ";
        }
    } else {
        cout<<"Recipe not found, unfortunately :("<<endl;
    }
}

int main() {
    vector<Recipe *> recipes;
    parseData(recipes,"RecipeDataset.csv");
    cout << "Welcome to Cooking by the Book!" << endl;
    cout << "We have over 200,000 recipes are our disposal, fit for your needs! What are you looking for today?" << endl;
    cout << "Enter in 1 if you would like to: Get a list of the fastest recipes to cook!" << endl;
    cout << "Enter in 2 if you would like to: Get a list of the healthiest recipes to cook!" << endl;
    cout << "Enter in 3 if you would like to: Search for a recipe" << endl;

    minHeap HeapT = minHeap(recipes.size());
    BTree<pair<float, Recipe*>> BTreeT;
    bool initializedT = false;
    minHeap HeapC = minHeap(recipes.size());
    bool initializedC = false;
    BTree<pair<float, Recipe*>> BTreeC;
    bool initializedN = false;
    BTree<pair<string, Recipe*>> BTreeN;
    minHeap HeapN = minHeap(recipes.size());
    string calTimeChoice;
    while (true) {
        string option;
        cin >> option;
        if(option == "1")
        {
            calTimeChoice = "minutes";
            if(!initializedT) {
                timeRecipes(recipes,BTreeT,HeapT);
                initializedT= true;
            }
            Option1or2(HeapT,BTreeT,calTimeChoice);
        }
        else if (option == "2") {
            calTimeChoice = "calories";
            if(!initializedC) {
                calorieRecipes(recipes, BTreeC, HeapC);
                initializedC= true;
            }
            Option1or2(HeapC,BTreeC,calTimeChoice);
        } else if(option == "-1") {
            cout<<"Goodbye"<<endl;
            break;
        } else if(option == "3"){
            if(!initializedN) {
                nameRecipes(recipes, BTreeN, HeapC);
                initializedN= true;
            }
            Option3(BTreeN, HeapC);
        } else {
            cout<<"Unrecognized command"<<endl;
        }
        cout << "1 = Calory Search" << endl;
        cout << "2 = Time Search" << endl;
        cout << "3 = Name Search" << endl;
        cout << "-1 = Exit" << endl;
    }

    //Heap.printTop();
    //BTree.inorder();
}