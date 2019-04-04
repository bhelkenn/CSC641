#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;
int N = 1000000;

double RNG() {return double(rand()) / double(RAND_MAX);}
int main() {
  srand(time(NULL));
  int tests_sum = 0;
  for (int i = 0; i < N; i++) {
    double sum = 0.0; int count = 0;
    while (sum < 1.0) {
      sum += RNG(); count++;
    }
    tests_sum += count;
  }

  cout << "Test Average: " << double(tests_sum) / double(N);
  cout << "\nAnalytic (1 + A(1) = e): " << exp(1.0) << endl;
  return 0;
}
