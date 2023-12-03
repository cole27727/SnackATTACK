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

template <typename T>
T getPreferenceInput(const std::string& nutrient) {
    T preference;
    std::cout << "Rate the importance of " << nutrient << " (1-5): ";
    while (true) {
        std::cin >> preference;
        if (preference >= 1 && preference <= 5) {
            return preference;
        } else {
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
        }
    }
}

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
void merge(std::vector<FoodItem>& items, int left, int mid, int right)
{
    int n1 = mid-left+1;
    int n2 = right -mid;
    FoodItem X[n1], Y[n2];
    for(int i = 0; i<n1; i++)
        X[i] = items[left+i];
    for(int j =0; j<n2;j++)
        Y[j] = items[mid+1+j];
    int i, j,k;
    i=0;
    j=0;
    k=left;
    while (i<n1 && j<n2)
    {
        if (X[i].compatibility <= Y[j].compatibility)
        {
            items[k] = X[i];
            i++;
        }
        else
        {
            items[k] = Y[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        items[k] = X[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        items[k] = Y[j];
        j++;
        k++;
    }
}


void mergeSort(std::vector<FoodItem>& items, int left, int right)
{
    if(left< right)
    {
        int mid = left+ (right-left)/2;
        mergeSort(items, left, mid);
        mergeSort(items,mid+1, right);
        merge(items, left, mid, right);
    }
}

int main()
{


    UserPreferences userPrefs{};

    std::cout << "Rank the following options based on what’s most important to you using 1-5 (5 being the most important) \n";
    userPrefs.vitaminA = getPreferenceInput<int>("Foods High in Vitamin A");
    userPrefs.vitaminC = getPreferenceInput<float>("Foods High in Vitamin C");
    userPrefs.fiber = getPreferenceInput<float>("Foods High in Fiber");
    userPrefs.calcium = getPreferenceInput<int>("Foods High in Calcium");
    userPrefs.protein = getPreferenceInput<float>("Foods High in Protein");
    userPrefs.monosaturatedFat = getPreferenceInput<float>("Foods High in Monosaturated Fats");
    userPrefs.sodium = getPreferenceInput<int>("Foods Low in Sodium");
    userPrefs.iron = getPreferenceInput<float>("Foods High in Iron");
    userPrefs.cholesterol = getPreferenceInput<int>("Foods Low in Cholesterol");
    userPrefs.sugar = getPreferenceInput<float>("Foods Low in Sugar");



    std::vector<FoodItem> foodItems; //we are loading here boys

    std::ifstream inFile("food_data.csv");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }


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
        iss >> item.sugar; iss.ignore();


        foodItems.push_back(item);
    }

///*====================Conversion to Grams???====================*/
//    for (auto& item : foodItems) {
//        convertNutrientValuesToGrams(item);
//    }

    // Calculate compatibility for each food item
    for (auto& item : foodItems) {
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
