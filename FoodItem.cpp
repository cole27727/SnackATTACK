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
    int count = 0;

    // Function to calculate the score for each nutrient
    auto calcScore = [](float nutrientValue, int preference, float standardValue) {
        // Normalize preference to a percentage (20% to 100%)
        float normPreference = preference * 20.0f;// 20% is the lowest preference

        // Calculate the proportion of the nutrient value to the standard value
        float proportion = (standardValue > 0) ? (nutrientValue / standardValue) * 100.0f : 0.0f;

        // Calculate the score based on how close the proportion is to the normalized preference
        return 100.0f - std::abs(normPreference - proportion); // 100% is a perfect match
    };

    // Standard values for nutrients (example values, adjust according to a standard dietary reference)
    const float standardVitaminA = 900; // mcg (micrograms)
    const float standardVitaminC = 90; // mg   (milligrams)
    const float standardCalcium = 1000; // mg
    const float standardProtein = 50; // g (grams)
    const float standardFiber = 25; // g
    const float standardSodium = 2300; // mg
    const float standardIron = 8; // mg
    const float standardCholesterol = 300; // mg
    const float standardSugar = 50; // g
    const float standardCarbs = 300; // g
    const float standardFats = 65; // g



    // ... Define standard values for other nutrients like the ones above here

    // Calculate score for each nutrient based on user preferences
    if (prefs.vitaminA > 0) {
        score += calcScore(item.vitaminA, prefs.vitaminA, standardVitaminA);
        count++;
    }
    if (prefs.vitaminC > 0) {
        score += calcScore(item.vitaminC, prefs.vitaminC, standardVitaminC);
        count++;
    }
    if (prefs.fiber > 0) {
        score += calcScore(item.fiber, prefs.fiber, standardFiber);
        count++;
    }
    if (prefs.calcium > 0) {
        score += calcScore(item.calcium, prefs.calcium, standardCalcium);
        count++;
    }
    if (prefs.protein > 0) {
        score += calcScore(item.protein, prefs.protein, standardProtein);
        count++;
    }
    if (prefs.monosaturatedFat > 0) {
        score += calcScore(item.monosaturatedFat, prefs.monosaturatedFat, standardFats);
        count++;
    }
    if (prefs.carbs > 0) {
        score += calcScore(item.carbs, prefs.carbs, standardCarbs);
        count++;
    }

    if (prefs.iron > 0) {
        score += calcScore(item.iron, prefs.iron, standardIron);
        count++;
    }
    if (prefs.cholesterol > 0) {
        score += calcScore(item.cholesterol, prefs.cholesterol, standardCholesterol);
        count++;
    }
    if (prefs.sugar > 0) {
        score += calcScore(item.sugar, prefs.sugar, standardSugar);
        count++;
    }
    if (prefs.sodium > 0) {
        score += calcScore(item.sodium, prefs.sodium, standardSodium);
        count++;
    }

      // ... Calculate score for other nutrients here down below


        // Normalize the score
        return (count > 0) ? (score / count) : 0;
    }



void printNutrition(const std::vector<FoodItem>& foodItems, int preference){
    for (const auto& item : foodItems) {
    }

}
