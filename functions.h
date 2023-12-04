#pragma once
#include "FoodItem.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std::chrono;
using namespace std;

void readDescription(istream& input, string& field);
int getPreferenceInput(const string& nutrient);

/***Quick Sort***/
int partition(vector<FoodItem>& items, int low, int high);
void quickSort(vector<FoodItem>& items, int low, int high);

/***Merge Sort***/
void merge(vector<FoodItem>& items, int left, int mid, int right);
void mergeSort(vector<FoodItem>& items, int left, int right);