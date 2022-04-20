#include <iostream>
#include "BTree.h"
#include "Recipe.h"
#include "heap.cpp"
#include <vector>
#include <chrono>

#define timeUnitName " ms"
#define timeUnit std::chrono::milliseconds
using namespace std;
using namespace std::chrono;

void exitProgram(vector<Recipe *>& recipes, BTree<pair<float, Recipe*>>& BTreeT, BTree<pair<float, Recipe*>>& BTreeC,BTree<pair<string, Recipe*>>& BTreeN) {
    BTreeN.exit();
    BTreeC.exit();
    BTreeT.exit();
    for(auto & recipe : recipes) {
        delete recipe;
    }
}

void parseData(vector<Recipe *>& recipes, string fileName) {
    ifstream input(fileName, ios::in);
    string curr;
    time_point<system_clock> start, end;
    start = system_clock::now();
    getline(input, curr);
    while (getline(input, curr)) {
        recipes.push_back(new Recipe(curr));
    }
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"Data set parsed in : "<<ms.count()<<timeUnitName<<endl;
}

void Option1or2(minHeap<pair<float,Recipe*>>& Heap, BTree<pair<float, Recipe*>>& BTree, string calTimeChoice) {
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
        cout<<"B-Tree ascending constructed in "<<ms.count()<<timeUnitName<<endl;
        start = system_clock::now();
        vector<pair<float,Recipe*>> k;
        k = Heap.extract();
        int i = 0;
        if(userOption != -1) {
            while(true) {
                if(k[i].first >= userOption) {
                    break;
                }
                i++;
            }
        }
        end = system_clock::now();
        ms = duration_cast<timeUnit>(end-start);
        cout<<"Heap ascending constructed in "<<ms.count()<<timeUnitName<<endl;
        while(!q.empty()) {
            q.front().second->printRecipe();
            //k[i].second->printRecipe();
            i++;
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
    }
    else if(order == 2){
        stack<pair<float, Recipe*>> s;
        BTree.revorder(s);
        time_point<system_clock> start, end;
        start = system_clock::now();
        if(userOption != -1) {
            while(true) {
                if(s.top().first < userOption) {
                    break;
                }
                s.pop();
            }
        }
        end = system_clock::now();
        auto ms = duration_cast<timeUnit>(end-start);
        cout<<"B-Tree descending constructed in "<<ms.count()<<timeUnitName<<endl;
        start = system_clock::now();
        vector<pair<float,Recipe*>> k;
        k = Heap.extract();
        int i = 0;
//        if(userOption != -1) {
//            while(true) {
//                if(k[i].first < userOption) {
//                    break;
//                }
//                i--;
//            }
//        }
        end = system_clock::now();
        ms = duration_cast<timeUnit>(end-start);
        cout<<"Heap descending constructed in "<<ms.count()<<timeUnitName<<endl;
        while(!s.empty()) {
            s.top().second->printRecipe();
            if(k[i].second == nullptr) {
                cout<<"PROBLEM";
            }
            k[i].second->printRecipe();
            i++;
            s.pop();
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

void Option3(BTree<pair<string, Recipe*>>& BTree,minHeap<pair<string,Recipe*>>& HeapN) {
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
    cout<<"B-Tree searched in: "<<ms.count()<<timeUnitName<<endl;
    start = system_clock::now();
    vector<Recipe*> nameHeap = HeapN.searchName(searchKey);
    end = system_clock::now();
    ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap searched in: "<<ms.count()<<timeUnitName<<endl;
    if(!find.empty()) {
        int i = 0;
        if(find.size() == 1) {
            cout<<"There is only one result matching your search, displaying now"<<endl;
            find[0]->printRecipe();
            return;
        } else {
            cout<<"There are "<<find.size()<<" results, showing the first"<<endl;
            //cout<<"There are "<<nameHeap.size()<<" results, showing the first"<<endl;
        }
        while (i < find.size()) {
            find[i]->printRecipe();
            i++;
            if( i < find.size() ) {
                cout<<"Would you like to view another recipe?"<<endl;
                cout<<"1 = Another\t 2 = No";
                string viewAnother;
                cin>>viewAnother;
                if(viewAnother != "1") {
                    cout<<"Okay, no more recipes"<<endl;
                    break;
                }
            } else {
                cout<<"No more recipes remaining, returning to main menu"<<endl;
            }

        }
    } else {
        cout<<"Recipe not found, unfortunately :("<<endl;
    }
}

void Option4(BTree<pair<string, Recipe*>>& BTree,minHeap<pair<string,Recipe*>>& HeapN) {
    string searchKey;
    cout<<"Enter the ingredients you wish to search for, and type -1 to indicate you are done"<<endl;
    vector<string> ingredientsSearch;
    while(true) {
        cin>>searchKey;
        transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);
        if(searchKey == "-1") {
            break;
        } else {
            ingredientsSearch.push_back(searchKey);
        }
    }
    std::sort(ingredientsSearch.begin(), ingredientsSearch.end());
    time_point<system_clock> start, end;
    vector<Recipe*> find;
    start = system_clock::now();
    BTree.RecipeSearch(ingredientsSearch,find);
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"B-Tree searched in: "<<ms.count()<<timeUnitName<<endl;
    std::sort(ingredientsSearch.begin(), ingredientsSearch.end());
    start = system_clock::now();
    vector<Recipe*> nameHeap;
    HeapN.searchIngredient(ingredientsSearch,nameHeap);
    end = system_clock::now();
    ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap searched in: "<<ms.count()<<timeUnitName<<endl;
    if(!find.empty()) {
        int i = 0;
        if(find.size() == 1) {
            cout<<"There is only one result matching your search, displaying now"<<endl;
            find[0]->printRecipe();
            return;
        } else {
            cout<<"There are "<<find.size()<<" results matching your , showing the first"<<endl;
            //cout<<"There are "<<nameHeap.size()<<" results matching your , showing the first"<<endl;
        }
        while (i < find.size()) {
            find[i]->printRecipe();
            i++;
            if( i < find.size() ) {
                cout<<"Would you like to view another recipe?"<<endl;
                cout<<"1 = Another\t 2 = No";
                string viewAnother;
                cin>>viewAnother;
                if(viewAnother != "1") {
                    cout<<"Okay, no more recipes"<<endl;
                    break;
                }
            } else {
                cout<<"No more recipes remaining, returning to main menu"<<endl;
            }
        }
    } else {
        cout<<"Recipe not found, unfortunately :("<<endl;
    }
}

void constructHeap(vector<Recipe *>& recipes,minHeap<pair<float,Recipe*>>& HeapT, minHeap<pair<float,Recipe*>>& HeapC,minHeap<pair<string,Recipe*>>& HeapN) {
    time_point<system_clock> start, end;
    start = system_clock::now();
    for(auto & recipe : recipes)
    {
        HeapC.insertGen(make_pair(recipe->getNutrients()[0], recipe));
        HeapT.insertGen(make_pair(recipe->getTime(), recipe));
        HeapN.insertGen(make_pair(recipe->getName(), recipe));
    }
    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"Heap Constructed in: "<<ms.count()<<timeUnitName<<endl;
}

void constructBTree(vector<Recipe *>& recipes,BTree<pair<float, Recipe*>>& BTreeT,BTree<pair<float, Recipe*>>& BTreeC, BTree<pair<string, Recipe*>>& BTreeN) {
    time_point<system_clock> start, end;
    start = system_clock::now();
    for(auto & recipe : recipes) {
        BTreeC.insert(make_pair(recipe->getNutrients()[0],recipe));
        BTreeT.insert(make_pair(recipe->getTime(),recipe));
        BTreeN.insert(make_pair(recipe->getName(),recipe));
    }

    end = system_clock::now();
    auto ms = duration_cast<timeUnit>(end-start);
    cout<<"B-Tree Constructed in: "<<ms.count()<<timeUnitName<<endl;
}

int main() {
    vector<Recipe *> recipes;
    cout << "Welcome to Cooking by the Book!" << endl;
    cout << "We have over 200,000 recipes are our disposal, fit for your needs! What are you looking for today?" << endl;
    cout << "Enter in 1 if you would like to: Get a list of the fastest recipes to cook!" << endl;
    cout << "Enter in 2 if you would like to: Get a list of the healthiest recipes to cook!" << endl;
    cout << "Enter in 3 if you would like to: Search for a recipe" << endl;
    cout << "Enter in 4 if you would like to: Search for recipes using ingredients" << endl;
    cout << "Enter in -1 if you would like to: Exit" << endl;
    parseData(recipes,"RecipeDataset.csv");

    minHeap<pair<float,Recipe*>> HeapT = minHeap<pair<float,Recipe*>>(recipes.size());
    minHeap<pair<float, Recipe*>> HeapC = minHeap<pair<float,Recipe*>>(recipes.size());
    minHeap<pair<string, Recipe*>> HeapN = minHeap<pair<string,Recipe*>>(recipes.size());
    constructHeap(recipes,HeapT,HeapC, HeapN);
    BTree<pair<float, Recipe*>> BTreeT;
    BTree<pair<float, Recipe*>> BTreeC;
    BTree<pair<string, Recipe*>> BTreeN;
    constructBTree(recipes,BTreeT,BTreeC,BTreeN);

    string calTimeChoice;
    while (true) {
        string option;
        cin >> option;
        if(option == "1")
        {
            calTimeChoice = "minutes";
            Option1or2(HeapT,BTreeT,calTimeChoice);
        }
        else if (option == "2") {
            calTimeChoice = "calories";
            Option1or2(HeapC,BTreeC,calTimeChoice);
        } else if(option == "-1") {
            cout<<"Goodbye"<<endl;
            break;
        } else if(option == "3"){
            Option3(BTreeN, HeapN);

        } else if(option == "4"){
            Option4(BTreeN, HeapN);

        }else {
            cout<<"Unrecognized command"<<endl;
        }
        cout << endl;
        cout << "1 = Calorie Search" << endl;
        cout << "2 = Time Search" << endl;
        cout << "3 = Name Search" << endl;
        cout << "4 = Ingredient Search" << endl;
        cout << "-1 = Exit" << endl;
    }
    exitProgram(recipes,BTreeC,BTreeT, BTreeN); //Clears heap
    //Heap.printTop();
    //BTree.inorder();
}