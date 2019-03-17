#include <iostream>
#include <math.h>

using namespace std;
int Q, XMAX = 8057, RPM = 7200, XSTAR = 1686, X, TESTS = 10000;
int SEED = 0, SEEKDIST;
double SEEKTIME;
double T = 1.5455, C = 0.3197, R = 0.3868;
double AVGDIST, AVGTIME;

void populateDQ(int *);
void updateIOPosition(int *);
int minDist(int *);
int rng();
void calcAverages(int *, double *);
void displayResults();
int main() {
  int *dq;
  int *seek_distances = new int[TESTS];
  double *seek_times = new double[TESTS];

  for (Q = 1; Q <= 20; Q++) {
    dq = new int[Q]; populateDQ(dq);
    for (int i = 0; i < TESTS; i++) {
      updateIOPosition(dq);
      seek_distances[i] = SEEKDIST;
      seek_times[i] = SEEKTIME;
    }
    calcAverages(seek_distances, seek_times); displayResults();
    delete dq;
  }
  return 0;
}

void populateDQ(int *dq) {
  for (int i = 0; i < Q; i++) {
    dq[i] = rng();
  }
}
void updateIOPosition(int *dq) {
  static int firstcall = 1;
  if (firstcall) {X = rng(); firstcall = 0;} //init IO head
  else {
    SEEKDIST = minDist(dq);
    SEEKTIME = T + C * pow(SEEKDIST - 1, R);
    if (SEEKDIST > XSTAR)
      SEEKTIME += (C * R * (SEEKDIST - XSTAR)) / pow(XSTAR - 1, 1 - R);
  }
}
int minDist(int *dq) {
  int min = X - dq[0]; if (min < 0) min *= -1;
  int pos = 0;
  for (int i = 1; i < Q - 1; i++) {
    int test = X - dq[i]; if (test < 0) test *= -1;
    if (test < min) {min = test; pos = i;}
  }
  X = dq[pos];
  dq[pos] = rng();
  return min;
}
int rng() {
  SEED = ((5 * SEED + 1699) % XMAX) + 1; //num between 1 and XMAX
  return SEED;
}
void calcAverages(int *seek_distances, double *seek_times) {
  double dsum = 0.0, tsum = 0.0;
  for (int i = 0; i < TESTS; i++) {
    dsum += seek_distances[i];
    tsum += seek_times[i];
  }
  AVGDIST = dsum / TESTS; AVGTIME = tsum / TESTS;
}
void displayResults() {
  cout << "\nQueue Length: " << Q << ":\n";
  cout << "Average Distance: " << AVGDIST << " cylinders\n";
  cout << "Average Time: " << AVGTIME << " ms\n";
}
