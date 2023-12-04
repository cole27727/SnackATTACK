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
    float carbs = 0;
    float sodium = 0;
    float iron = 0;
    float sugar = 0;

    float compatibility = 0;
};

struct UserPreferences {
    int cholesterol;
    int vitaminA;
    int vitaminC;
    int fiber;
    int calcium;
    int protein;
    int monosaturatedFat;
    int carbs;
    int sodium;
    int iron;
    int sugar;
};

float calculateCompatibility(const FoodItem& item, const UserPreferences& prefs);

void convertNutrientValuesToGrams(FoodItem& item);

//Quick Sort
int partition(std::vector<FoodItem>& items, int low, int high);
//Merge Sort

#endif // FOODITEM_H
