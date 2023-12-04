#include "Functions.h"

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