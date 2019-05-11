#include <iostream>
#include <math.h>

using namespace std;
#define TESTS 10000
int Q, XMAX = 8057, XSTAR = 1686, X;
int SEED = 0, DIST;
double T = 1.5455, C = 0.3197, R = 0.3868
double TIME, AVGDIST, AVGTIME;
int SEEK_DISTANCES[TESTS];
double SEEK_TIMES[TESTS];

void populateDQ(int *);
void updateIOPosition(int *);
int minDist(int *);
int rng() {return SEED = ((5 * SEED + 1699) % XMAX) + 1;};
void calcAverages();
void displayResults();
int main() {
  int *dq;
  for (Q = 1; Q <= 20; Q++) {
    dq = new int[Q]; populateDQ(dq);
    for (int i = 0; i < TESTS; i++) {
      updateIOPosition(dq);
      SEEK_DISTANCES[i] = DIST;
      SEEK_TIMES[i] = TIME;
    }
    calcAverages(); displayResults();
    delete dq;
  }
  return 0;
}

void populateDQ(int *dq) {
  for (int i = 0; i < Q; i++) {dq[i] = rng();}
}
void updateIOPosition(int *dq) {
  static int firstcall = 1;
  if (firstcall) {X = rng(); firstcall = 0;} //init IO head
  else {
    DIST = minDist(dq);
    TIME = T + C * pow(DIST - 1, R);
    if (DIST > XSTAR)
      TIME += (C * R * (DIST - XSTAR)) / pow(XSTAR - 1, 1 - R);
  }
}
int minDist(int *dq) {
  int min = X - dq[0]; if (min < 0) min *= -1;
  int pos = 0;
  for (int i = 1; i < Q - 1; i++) {
    int test = X - dq[i]; if (test < 0) test *= -1;
    if (test < min) {min = test; pos = i;}
  }
  X = dq[pos]; dq[pos] = rng();
  return min;
}
void calcAverages() {
  double dsum = 0.0, tsum = 0.0;
  for (int i = 0; i < TESTS; i++) {
    dsum += SEEK_DISTANCES[i];
    tsum += SEEK_TIMES[i];
  }
  AVGDIST = dsum / double(TESTS); AVGTIME = tsum / double(TESTS);
}
void displayResults() {
  cout << "\nQueue Length: " << Q << ":\n";
  cout << "Average Distance: " << AVGDIST << " cylinders\n";
  cout << "Average Time: " << AVGTIME << " ms\n";
}
