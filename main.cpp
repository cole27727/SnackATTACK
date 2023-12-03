#include "FoodItem.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std::chrono;
using namespace std;
//Danielle
void readDescription(std::istream& input, std::string& field) {
    char c;
    field.clear();

    if (input >> c && c == '"') {
        std::getline(input, field, '"');
        input.ignore();
    }
    else {
        input.putback(c);
        std::getline(input, field, ',');
    }
}

int partition(std::vector<FoodItem>& items, int low, int high) {
    FoodItem pivot = items[high]; // choosing the last element as pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (items[j].compatibility < pivot.compatibility) {
            i++;
            std::swap(items[i], items[j]);
        }
    }
    std::swap(items[i + 1], items[high]);
    return (i + 1);
}

void quickSort(std::vector<FoodItem>& items, int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);

        quickSort(items, low, pi - 1);
        quickSort(items, pi + 1, high);
    }
}

int main()
{


    UserPreferences userPrefs{};

    std::cout << "Rank the following options based on what’s most important to you using 1-5 \n";
    userPrefs.vitaminA = getPreferenceInput("Foods High in Vitamin A");
    userPrefs.vitaminC = getPreferenceInput("Foods High in Vitamin C");
    userPrefs.fiber = getPreferenceInput("Foods High in Fiber");
    userPrefs.calcium = getPreferenceInput("Foods High in Calcium");
    userPrefs.protein = getPreferenceInput("Foods High in Protein");
    userPrefs.monosaturatedFat = getPreferenceInput("Foods High in Monosaturated Fats");
    userPrefs.sodium = getPreferenceInput("Foods Low in Sodium");
    userPrefs.iron = getPreferenceInput("Foods High in Iron");
    userPrefs.cholesterol = getPreferenceInput("Foods Low in Cholesterol");


    std::vector<FoodItem> foodItems; //we are loading here boys

    std::ifstream inFile("food_data.csv");
    std::string line;

    // Skip the header line
    std::getline(inFile, line);

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        FoodItem item;

        // Use a temporary variable for the unused columns
        std::string temp;

        // Assuming the CSV columns are ordered as in the file and are comma-separated
        std::getline(iss, temp, ','); //
        std::getline(iss, temp, ','); // Skip 'Category'

        //Read the description of the food, using "" to denote the beginning and end of the description
        readDescription(iss, item.name);

        iss >> item.cholesterol; iss.ignore();
        iss >> item.vitaminA; iss.ignore();
        iss >> item.vitaminC; iss.ignore();
        iss >> item.fiber; iss.ignore();
        iss >> item.calcium; iss.ignore();
        iss >> item.protein; iss.ignore();
        iss >> item.monosaturatedFat; iss.ignore();
        iss >> item.sodium; iss.ignore();
        iss >> item.iron; iss.ignore();
        iss >> temp; // Skip the last cholesterol column if it's not needed

        foodItems.push_back(item);
    }

/*====================Conversion to Grams???====================*/
    for (auto& item : foodItems) {
        convertNutrientValuesToGrams(item);
    }

    // Calculate compatibility for each food item
    for (auto& item : foodItems) {
        item.compatibility = calculateCompatibility(item, userPrefs);
    }
    auto start = high_resolution_clock::now();

    quickSort(foodItems, 0, foodItems.size());

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Quick Sort Time: " << duration.count() << " microseconds" << endl;
    // Print the compatibility of each food item
    int j = 1;
    for (int i = foodItems.size(); i > foodItems.size()-10; i--) {
        std::cout << j << ". " << foodItems[i].name << " - Compatibility: " << foodItems[i].compatibility << std::endl;
        j++;
    }
};



// Sort foodItems based on compatibility
// quickSort(foodItems, 0, foodItems.size() - 1); or mergeSort(foodItems, 0, foodItems.size() - 1);


// float compatibility = calculateCompatibility({vitaminA, vitaminC, fiber, calcium, protien, fats, sodium, iron, cholestrol, userPreferences);


//TODO: Set up object to store data from csv most preferably, an unordred_map // I used vector
//Create function to determine how compatiable a food is based on user specifications //
//Create a function to print out the foods that are compatiable with the user
//Create a function to print out food to avoid