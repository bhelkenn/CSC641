#include <iostream>
#include <math.h>

using namespace std;
double PI = 3.14159265;

int main() {
  double x = 0.0;
  for (int i = 0; i < 10; i++) {
    x = fmod(1.25 * x + (PI / 3.0), PI);
    cout << "\n\nRandom number: " << x;
    cout << "\nProbability of this number: " << 0.5 * sin(x);
  }
  cout << endl;
  return 0;
}
