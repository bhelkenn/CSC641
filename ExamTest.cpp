#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;

int TESTS = 1000000;
int RPM = 7200, DB1 = 1000, DB2 = 2000, DIST, EMPTYCYL = 2000;
double TOTAL = 0.0, P2 = 0.7, T = 1.6, C = 0.39, R = 0.4;

double RNG() {return double(rand()) / RAND_MAX;}

int main() {
  srand(time(NULL));
  double wait = 30.0 / RPM * 1000; int location = RNG() * 4999 + 1;
  cout << "Wait: " << wait << endl;
  for (int i = 0; i < TESTS; i++) {
    int target;
    double rng = RNG();
    if (rng < P2) { // in DB1
      target = RNG() * (DB1 - 1) + 1;
    } // else in DB2
    else {target = RNG() * (DB2 - 1) + 1 + DB1 + EMPTYCYL;}
    DIST = abs(target - location); location = target;
    if (DIST == 0) {
      TOTAL += wait + 1; continue;
    }
    TOTAL += (T + C * pow((DIST - 1), R) + wait + 1) / 1000;
  }
  cout << "Total time (s): " << TOTAL << endl;
  cout << "Average time (ms): " << TOTAL / TESTS * 1000 << endl;

  return 0;
}
