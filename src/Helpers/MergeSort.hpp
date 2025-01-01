#include <array>

namespace MergeSort {

int merge(int arr[], int aux[], int low, int mid, int high);  // we don't need the safety of std::array, cause the bounds are written

int mergesort(int arr[], int aux[], int low, int high);

}