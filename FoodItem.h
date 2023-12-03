#ifndef FOODITEM_H
#define FOODITEM_H
#include <vector>

#include <string>

struct FoodItem {
    std::string name;
    float cholesterol = 0;
    float vitaminA = 0;
    float vitaminC = 0;
    float fiber = 0;
    float calcium = 0;
    float protein = 0;
    float monosaturatedFat = 0;
    float sodium = 0;
    float iron = 0;
    float sugar = 0;
    float compatibility = 0;
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
    float sugar;
};

float calculateCompatibility(const FoodItem& item, const UserPreferences& prefs);

int getPreferenceInput(const std::string& nutrient);

void convertNutrientValuesToGrams(FoodItem& item);

//Quick Sort
int partition(std::vector<FoodItem>& items, int low, int high);
//Merge Sort

#endif // FOODITEM_H
