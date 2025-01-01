#include "MergeSort.hpp"

namespace MergeSort {

int merge(int arr[], int aux[], int low, int mid, int high) {
  int k = low, i = low, j = mid + 1;
  int inversionCount = 0;
  while (i <= mid && j <= high) {
    if (arr[i] <= arr[j]) {
      aux[k++] = arr[i++];
    } else {
      aux[k++] = arr[j++];
      inversionCount += (mid - i + 1); // NOTE
    }
  }
  while (i <= mid) {
    aux[k++] = arr[i++];
  }
  for (i = low; i <= high; i++) {
    arr[i] = aux[i];
  }
  return inversionCount;
};

int mergesort(int arr[], int aux[], int low, int high) {
  // base case
  if (high <= low) { // if run size <= 1
    return 0;
  }
  int mid = (low + ((high - low)/2));
  int inversionCount = 0;

  inversionCount += mergesort(arr, aux, low, mid);
  inversionCount += mergesort(arr, aux, mid + 1, high);
  inversionCount += merge(arr, aux, low, mid, high);

  return inversionCount;
};

}