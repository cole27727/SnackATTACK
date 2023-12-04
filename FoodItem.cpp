#include "FoodItem.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

void convertNutrientValuesToGrams(FoodItem& item) {
    const float mgConversionFactor = 0.001; //mg => g
    double mcgConversionFactor = 1e-6; //mcg => g
    item.cholesterol *= mgConversionFactor;
    item.vitaminA *= mcgConversionFactor;
    item.vitaminC *= mgConversionFactor;
    item.calcium *= mgConversionFactor;
    item.sodium *= mgConversionFactor;
    item.iron *= mgConversionFactor;
}

float calculateCompatibility(const FoodItem& item, const UserPreferences& prefs) {
    float score = 0.0f;
    score += item.vitaminA * prefs.vitaminA;
    score += item.vitaminC * prefs.vitaminC;
    score += item.fiber * prefs.fiber;
    score += item.calcium * prefs.calcium;
    score += item.protein * prefs.protein;
    score += item.monosaturatedFat * prefs.monosaturatedFat;
    score += item.carbs * prefs.carbs;
    score += item.iron * prefs.iron;

    score -= item.cholesterol * prefs.cholesterol;
    score -= item.sodium * prefs.sodium;
    score -= item.sugar * prefs.sugar;

    return score;
}

void printNutrition(const std::vector<FoodItem>& foodItems, int preference){
    for (const auto& item : foodItems) {
    }

}
