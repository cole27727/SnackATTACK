#include "FoodItem.h"

using namespace std;
using namespace std::chrono;

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
//



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
void readDescription(istream& input, string& field) {
    char c;
    field.clear();

    if (input >> c && c == '"') {
        getline(input, field, '"');
        input.ignore();
    }
    else {
        input.putback(c);
        getline(input, field, ',');
    }
}

int getPreferenceInput(const string& nutrient) {
    int preference;
    cout << "Rate the importance of " << nutrient << " (1-5): ";
    while (true) {
        cin >> preference;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid input. Please enter a number between 1 and 5: ";
        }
        else if (preference >= 1 && preference <= 5) {
            return preference;
        }
        else {
            cout << "Invalid input. Please enter a number between 1 and 5: ";
        }
    }
}

int partition(vector<FoodItem>& items, int low, int high) {
    FoodItem pivot = items[high]; // choosing the last element as pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to the pivot
        if (items[j].compatibility <= pivot.compatibility) {
            i++;
            swap(items[i], items[j]);
        }
    }
    swap(items[i + 1], items[high]);
    return (i + 1);
}
void quickSort(vector<FoodItem>& items, int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);

        quickSort(items, low, pi - 1);
        quickSort(items, pi + 1, high);
    }
}
/***Merge Sort *****/
void merge(vector<FoodItem>& items, int left, int mid, int right)
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
void mergeSort(vector<FoodItem>& items, int left, int right)
{
    if(left< right)
    {
        int mid = left+ (right-left)/2;
        mergeSort(items, left, mid);
        mergeSort(items,mid+1, right);
        merge(items, left, mid, right);
    }
}
