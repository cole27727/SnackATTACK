#include "FoodItem.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


int getPreferenceInput(const std::string& nutrient) {
    int preference;
    std::cout << "Rate the importance of " << nutrient << " (1-5): ";
    while(true) {
        std::cin >> preference;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
        } else
        if (preference >= 1 && preference <= 5) {
            return preference;
        } else {
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
        }
    }
}

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
    float score = 0;
    int count = 0;

    if (prefs.vitaminA > 0) {
        score += item.vitaminA * prefs.vitaminA;
        count++;
    }
    if (prefs.vitaminC > 0) {
        score += item.vitaminC * prefs.vitaminC;
        count++;
    }
    if (prefs.fiber > 0) {
        score += item.fiber * prefs.fiber;
        count++;
    }
    if (prefs.calcium > 0) {
        score += item.calcium * prefs.calcium;
        count++;
    }
    if (prefs.protein > 0) {
        score += item.protein * prefs.protein;
        count++;
    }
    if (prefs.monosaturatedFat > 0) {
        score += item.monosaturatedFat * prefs.monosaturatedFat;
        count++;
    }
    if (prefs.sodium > 0) { //Remember for sodium it is foods low in sodium
        //We do minus here because a lot of sodium should negatively affect score
        score -= item.sodium * prefs.sodium;
        count++;
    }
    if (prefs.iron > 0) {
        score += item.iron * prefs.iron;
        count++;
    }
    if (prefs.cholesterol > 0) {
        //Same logic as sodium here; we want foods low in cholesterol so a high number should negatively affect score
        score -= item.cholesterol * prefs.cholesterol;
        count++;
    }

    return score;
}

void printNutrition(const std::vector<FoodItem>& foodItems, int preference){
    for (const auto& item : foodItems) {
    }

}
