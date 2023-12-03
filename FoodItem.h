#ifndef FOODITEM_H
#define FOODITEM_H
#include <vector>

#include <string>

struct FoodItem {
    std::string name;
    int cholesterol;
    int vitaminA;
    float vitaminC;
    float fiber;
    int calcium;
    float protein;
    float monosaturatedFat;
    int sodium;
    float iron;
    float compatibility;
};

struct UserPreferences {
    int cholesterol;
    int vitaminA;
    float vitaminC;
    float fiber;
    int calcium;
    float protein;
    float monosaturatedFat;
    int sodium;
    float iron;
};

float calculateCompatibility(const FoodItem& item, const UserPreferences& prefs);

int getPreferenceInput(const std::string& nutrient);

void convertNutrientValuesToGrams(FoodItem& item);

//Quick Sort
int partition(std::vector<FoodItem>& items, int low, int high);
//Merge Sort

#endif // FOODITEM_H
