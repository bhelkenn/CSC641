#include <iostream>
#include <time.h>
using namespace std;

void CreateMatrix(double**);
void InvertMatrix(double**);
void DisplayMatrix(double**);
void SwapMatrix(double**);
void CreateArray(int*);
int partition(int*, int, int);
void QuickSort(int*, int, int);
void DisplayArray(int*);
void DOUBLE(double**);
void INTEGER(int*);
double ElapsedTime(clock_t);
void DisplayStats();
static int MSIZE = 475;
static int ASIZE = 120000;
static int TIME = 10;
int NINT = 0, NFLOAT = 0;
double VINT, VFLOAT, AverageSpeed;

int main() {
  double **A = new double*[MSIZE];
  for (int i = 0; i < MSIZE; i++) {
    A[i] = new double[MSIZE * 2];
  }
  int *arr = new int[ASIZE];

  DOUBLE(A);
  INTEGER(arr);

  AverageSpeed = 2 / ((1 / VFLOAT) + (1 / VINT));
  DisplayStats();

  return 0;
}

void CreateMatrix(double **A) {
  int i, j;
  for(i = 0; i < MSIZE; i++) {
    A[i][i] = 2.0;
    for(j = 0; j < MSIZE; j++) {
      if (i != j) A[i][j] = 1.0;
    }
  }

  for(i = 0; i < MSIZE; i++) {
    for(j = MSIZE; j < 2 * MSIZE; j++) {
      if (i == j - MSIZE) A[i][j] = 1.0;
      else A[i][j] = 0.0;
    }
  }
}
void InvertMatrix(double **A) {
  int i, j, k;
  double t;

  for(i = 0; i < MSIZE; i++) {
    t = A[i][i];
    for(j = i; j < 2 * MSIZE; j++) {
      A[i][j] = A[i][j] / t;
    }
    for(j = 0; j < MSIZE; j++) {
      if (i != j) {
        t = A[j][i];
        for(k = 0; k < 2 * MSIZE; k++) {
          A[j][k] = A[j][k] - t * A[i][k];
        }
      }
    }
  }
  SwapMatrix(A);
  //DisplayMatrix(A);
}
void DisplayMatrix(double **A) {
  int i, j;
  for (int i = 0; i < MSIZE; i++) {
    for (int j = 0; j < 2 * MSIZE; j++) {
      cout << A[i][j] << " ";
    }
    cout << endl;
  }
}
void SwapMatrix(double **A) {
  double **T = new double*[MSIZE];
  for (int i = 0; i < MSIZE; i++) {
    T[i] = new double[MSIZE * 2];
  }
  int i, j;
  for (i = 0; i < MSIZE; i++) {
    for (j = 0; j < MSIZE; j++) {
      T[i][j] = A[i][j + MSIZE];
      T[i][j + MSIZE] = A[i][j];
    }
  }
  for (i = 0; i < MSIZE; i++) {
    for (j = 0; j < MSIZE * 2; j++) {
      A[i][j] = T[i][j];
    }
  }
}

void CreateArray(int *arr) {
  int num = 100;
  for (int i = 0; i < ASIZE; i++) {
    num = num % 19 + 2;
    arr[i] = num;
  }
}
int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;
  return i + 1;
}
void QuickSort(int *arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);

    QuickSort(arr, low, pi - 1);
    QuickSort(arr, pi + 1, high);
  }
}
void DisplayArray(int *arr) {
  for (int i = 0; i < ASIZE; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

void DOUBLE(double **A) {
  CreateMatrix(A);
  clock_t start_time = clock();
  while(ElapsedTime(start_time) < TIME) {
    InvertMatrix(A); // invert to A^-1
    InvertMatrix(A); // restore to A
    NFLOAT++;
  }

  VFLOAT = 60 * NFLOAT / ElapsedTime(start_time);
}
void INTEGER(int *arr) {
  clock_t start_time = clock();
  while(ElapsedTime(start_time) < TIME) {
    CreateArray(arr);
    QuickSort(arr, 0, ASIZE - 1);
    NINT++;
  }

  VINT = 60 * NINT / ElapsedTime(start_time);
}
double ElapsedTime(clock_t start_time) {
  clock_t elapsed_time = clock() - start_time;
  double elapsed_sec = elapsed_time * 1.0 / CLOCKS_PER_SEC;
  return elapsed_sec;
}
void DisplayStats() {
  cout << "Matrix Size: " << MSIZE << endl;
  cout << "Matrix Inversion Time (sec): "
      << 60 / VFLOAT << " seconds\n";
  cout << "Matrix Inversions Done (within " << TIME << " seconds): "
      << NFLOAT << endl;
  cout << "Speed of Matrix Inversions: "
      << VFLOAT << " inversion sets / minute\n\n";

  cout << "Array Size: " << ASIZE << endl;
  cout << "QuickSort Time (sec): "
      << 60 / VINT << " seconds\n";
  cout << "QuickSorts Done (within " << TIME << " seconds): "
      << NINT << endl;
  cout << "Speed of QuickSort Sorts: "
      << VINT << " sorts / minute\n\n";

  cout << "Average Processing Speed: "
      << AverageSpeed << " operations / minute\n";
}
