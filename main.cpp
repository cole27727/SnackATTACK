#include "FoodItem.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include "functions.h"
using namespace std::chrono;
using namespace std;

int main()
{
    bool inUse = true;
    while (inUse) {


        UserPreferences userPrefs{};

        cout << "Rank the following options based on what’s most important to you using 1-5 \n";
        userPrefs.vitaminA = getPreferenceInput("Foods High in Vitamin A");
        userPrefs.vitaminC = getPreferenceInput("Foods High in Vitamin C");
        userPrefs.fiber = getPreferenceInput("Foods High in Fiber");
        userPrefs.calcium = getPreferenceInput("Foods High in Calcium");
        userPrefs.protein = getPreferenceInput("Foods High in Protein");
        userPrefs.monosaturatedFat = getPreferenceInput("Foods High in Monosaturated Fats");
        userPrefs.carbs = getPreferenceInput("Foods High in Carbs");
        userPrefs.iron = getPreferenceInput("Foods High in Iron");

        userPrefs.cholesterol = getPreferenceInput("Foods Low in Cholesterol");
        userPrefs.sugar = getPreferenceInput("Foods Low in Sugar");
        userPrefs.sodium = getPreferenceInput("Foods Low in Sodium");

        vector<FoodItem> foodItems; //we are loading here boys

        ifstream inFile("food_data.csv");
        string line;

        // Skip the header line
        getline(inFile, line);

        while (getline(inFile, line)) {
            istringstream iss(line);
            FoodItem item;

            // Use a temporary variable for the unused columns
            string temp;

            // Assuming the CSV columns are ordered as in the file and are comma-separated
            getline(iss, temp, ','); //
            getline(iss, temp, ','); // Skip 'Category'

            //Read the description of the food, using "" to denote the beginning and end of the description
            readDescription(iss, item.name);

            iss >> item.cholesterol;
            iss.ignore();
            iss >> item.vitaminA;
            iss.ignore();
            iss >> item.vitaminC;
            iss.ignore();
            iss >> item.fiber;
            iss.ignore();
            iss >> item.calcium;
            iss.ignore();
            iss >> item.protein;
            iss.ignore();
            iss >> item.monosaturatedFat;
            iss.ignore();
            iss >> item.sodium;
            iss.ignore();
            iss >> item.iron;
            iss.ignore();
            iss >> item.sugar;
            iss.ignore();
            iss >> item.carbs;
            iss.ignore();


            foodItems.push_back(item);
        }

///*====================Conversion to Grams???====================*/
//    for (auto& item : foodItems) {
//        convertNutrientValuesToGrams(item);
//    }

        // Calculate compatibility for each food item
        for (auto &item: foodItems) {
            item.compatibility = calculateCompatibility(item, userPrefs);
        }
        auto mergeItems = foodItems;
        auto startQuick = high_resolution_clock::now();
        quickSort(foodItems, 0, foodItems.size());
        auto stopQuick = high_resolution_clock::now();
        auto durationQuick = duration_cast<microseconds>(stopQuick - startQuick);
        cout << "\n" << "Quick Sort Time: " << durationQuick.count() << " microseconds" << endl;

        auto startMerge = high_resolution_clock::now();
        mergeSort(mergeItems, 0, foodItems.size());
        auto stopMerge = high_resolution_clock::now();
        auto durationMerge = duration_cast<microseconds>(stopMerge - startMerge);
        cout << "Merge Sort Time: " << durationMerge.count() << " microseconds" << "\n" << "\n";

        // Print the compatibility of each food item
        int j = 1;
        for (int i = foodItems.size(); i > foodItems.size()-10; i--) {
            std::cout << std::setprecision(4) << j << ". " << foodItems[i].name << " - Compatibility: " << foodItems[i].compatibility << "%"<< std::endl;
            j++;
        }

        bool choosing = true;
        while (choosing) {
            cout << endl;
            cout << "Press 'r' to restart" << endl;
            cout << "Press 'e' to end" << endl;
            cout << "Or the rank of a food to its specific stats" << endl;
            string userOption;
            cin >> userOption;

            if (userOption == "r") {
                choosing = false;
                cout << endl;
            }
            else if (userOption == "e") {
                inUse = false;
                break;
            }
            else if (isdigit(userOption[0])) {
                int num = stoi(userOption);
                if (num >= 1 && num <= 10) {
                    int num = stoi(userOption) - 1;
                    cout << "Name: " << foodItems[foodItems.size() - num].name << endl;
                    cout << "Cholesterol       | " << "   " << foodItems[foodItems.size() - num].cholesterol << " grams\n";
                    cout << "Vitamin A         | " << "   " << foodItems[foodItems.size() - num].vitaminA << " grams\n";
                    cout << "Vitamin C         | " << "   " << foodItems[foodItems.size() - num].vitaminC << " grams\n";
                    cout << "Fiber             | " << "   " << foodItems[foodItems.size() - num].fiber << " grams\n";
                    cout << "Calcium           | " << "   " << foodItems[foodItems.size() - num].calcium << " grams\n";
                    cout << "Protein           | " << "   " << foodItems[foodItems.size() - num].protein << " grams\n";
                    cout << "MonosaturatedFat  | " << "   " << foodItems[foodItems.size() - num].monosaturatedFat << " grams\n";
                    cout << "Carbohydrates     | " << "   " << foodItems[foodItems.size() - num].carbs << " grams\n";
                    cout << "Sodium            | " << "   " << foodItems[foodItems.size() - num].sodium << " grams\n";
                    cout << "Iron              | " << "   " << foodItems[foodItems.size() - num].iron << " grams\n";
                    cout << "Sugar             | " << "   " << foodItems[foodItems.size() - num].sugar << " grams\n";

                    continue;
                }
                else {
                    cout << "Please enter a number 1-10" << endl << endl;
                    continue;
                }
            }
            else {
                cout << "Please enter a valid input" << endl << endl;
            }
        }
    }
};
