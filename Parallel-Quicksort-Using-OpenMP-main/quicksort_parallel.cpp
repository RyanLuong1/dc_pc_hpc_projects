#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>


double elaspedTime = 0.0;
//partitioning procedure
int partition(int arr[], int l, int r){
  int pivot = arr[l];

  int count = 0;
  for (int i = l + 1; i <= r; i++) {
      if (arr[i] <= pivot)
          count++;
  }

  // Giving pivot element its correct position
  int pivotIndex = l + count;
  int temp = 0;
  temp = arr[pivotIndex];
  arr[pivotIndex] = arr[l];
  arr[l] = temp;


  // Sorting left and right parts of the pivot element
  int i = l, j = r;

  while (i < pivotIndex && j > pivotIndex) {

      while (arr[i] <= pivot) {
          i++;
      }

      while (arr[j] > pivot) {
          j--;
      }

      if (i < pivotIndex && j > pivotIndex) {
          temp = arr[i];
          arr[i++] = arr[j];
          arr[j--] = temp;

      }
  }

  return pivotIndex;
}

void quickSort(int arr[], int l, int r){
  if(l < r) {
    int p = partition(arr, l, r);
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        double begin, end;
        begin = omp_get_wtime();
        quickSort(arr, l, p-1);
        end = omp_get_wtime();
        elaspedTime += end - begin;
      }
      #pragma omp section
      {
        double begin, end;
        begin = omp_get_wtime();
        quickSort(arr, p+1, r);
        end = omp_get_wtime();
        elaspedTime += end - begin;
      }
    }
  }
}

void printArr(int arr[], int n){
  for(int i = 0; i < n; i++) {
    printf("%d\n", arr[i]);
  }
}


int main(){
  int arrSize = 0;
  srand(time(NULL));
  printf("Enter how big you want the array to be: \n");
  scanf("%d", &arrSize);
  int arr[arrSize];
  int n = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < arrSize; ++i) {
    int rando = rand() % arrSize + 1;
    arr[i] = rando;
  }
  quickSort(arr, 0, n-1);
  if (elaspedTime < 3600000) {
    printArr(arr, n);
    printf("Elapsed time: %f", elaspedTime);
}
  else {
    printf("Elapsed time is exceeding 60 minutes. Program ending.");
  }
  return 0;
}