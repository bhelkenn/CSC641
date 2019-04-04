#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
int DIGITS[4] = {1, 2, 3, 4};
double PROB[4] = {0.1, 0.2, 0.3, 0.4};

void RNG();
int main() {
  srand(time(NULL));

  for (int i = 0; i < 5; i++) {
    RNG();
  }
  return 0;
}

void RNG() {
  int result = 0;
  double probability = 1.0;
  double choice;
  bool firstcall = true;

  for (int i = 0; i < 2; i++) {
    choice = rand() % 10 / 10.0;
    double prob_check = 0.0;
    for (int j = 3; j >= 0; j--) {
      prob_check += PROB[j];
      if (choice < prob_check) {
        probability *= PROB[j]; result += DIGITS[j]; break;
      }
    }
    if (firstcall) result *= 10;
    firstcall = false;
  }

  cout << "\nNumber: " << result;
  cout << "\nProbability: " << probability << endl;
}
