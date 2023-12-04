#ifndef FOODITEM_H
#define FOODITEM_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;

struct FoodItem {
    string name;

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
void readDescription(istream& input, string& field);
int getPreferenceInput(const string& nutrient);
int partition(vector<FoodItem>& items, int low, int high);
void merge(vector<FoodItem>& items, int left, int mid, int right);
void mergeSort(vector<FoodItem>& items, int left, int right);
void quickSort(vector<FoodItem>& items, int low, int high);
#endif // FOODITEM_H
