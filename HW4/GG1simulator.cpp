#include <iostream>
#include <math.h>
#include <time.h>

#define N 1000000
using namespace std;
int EVENT = 0, NEXT_EVENT = 0;
double TIME = 0.0, NEXT_TIME = 0.0;
int SYSTEM = 0, QUEUE = 0, ARRIVALS = 0, QSUM = 0, ACTIVE = 0;
double NEXT_ARR, NEXT_DEP;
double INTERARRIVALS[N], SERVICE_TIMES[N], WAIT_TIMES[N];
double TIMES[N], RESPONSE_TIMES[N];
int QUEUE_SIZES[N], ACTIVITY[N];
double AVG_A = 0.0, AVG_S = 0.0, AVG_Q = 0.0, AVG_U = 0.0, AVG_R = 0.0;
double SD_A, SD_S, SD_Q, SD_U, SD_R;
int ADIST, SDIST;

void DisplayChoices(string);
int DefineParameters(string);
double RNG() {return double(rand()) / double(RAND_MAX);}
double ArrivalLookup();
double DepartureLookup();
void UpdateCounters(int);
void UpdateNext(int);
void CalcAVG();
void CalcSD();
void DisplayResults();
int main() {
  srand(time(NULL));
  ADIST = DefineParameters("interarrival");
  SDIST = DefineParameters("service");

  for (int i = 0; i < N; i++) {UpdateCounters(i); UpdateNext(i);}
  CalcAVG(); CalcSD();
  DisplayResults();

  return 0;
}

void DisplayChoices(string type) {
  cout << "\nThe available " << type << " time distributions are:";
  cout << "\n\t(1) Constant";
  cout << "\n\t(2) Exponential";
  cout << "\n\t(3) Uniform";
  cout << "\nEnter your choice: ";
}
int DefineParameters(string type) {
  int choice = 0;
  DisplayChoices(type); cin >> choice;
  while (choice < 1 || choice > 3) {DisplayChoices(type); cin >> choice;}
  return choice;
}
double ArrivalLookup() {
  double rng = RNG();
  if (ADIST == 1) return 2.0;
  else if (ADIST == 2) {
    double mean = 2.0; double lambda = 1.0 / mean;
    for (double i = 0.1; i < 30.0; i += 0.1) {
      if (rng < (1.00 - exp(-1 * lambda * i))) return i;
    }
    return 35.0;
  }
  else return 1.0 + (2 * rng);
}
double DepartureLookup() {
  double rng = RNG();
  if (SDIST == 1) return 1.0;
  else if (SDIST == 2) {
    double mean = 1.0; double lambda = 1.0 / mean;
    for (double i = 0.1; i < 30.0; i += 0.1) {
      if (rng < (1.00 - exp(-1 * lambda * i))) return i;
    }
    return 35.0;
  }
  else return 1.0 + rng;
}

void UpdateCounters(int i) {
   EVENT = NEXT_EVENT; TIME = NEXT_TIME; SYSTEM += EVENT;
   if (SYSTEM > 0) QUEUE = SYSTEM - 1;
   QUEUE_SIZES[i] = QUEUE; QSUM += QUEUE;
}
void UpdateNext(int i) {
  if (EVENT >= 0) {
    ARRIVALS++; double prev_arrival = NEXT_ARR;
    NEXT_ARR = TIME + ArrivalLookup();
    INTERARRIVALS[i] = NEXT_ARR - prev_arrival;
  } else {INTERARRIVALS[i] = 0;}

  if (EVENT > 0) {
    SERVICE_TIMES[i] = NEXT_DEP - TIME;
    WAIT_TIMES[i] = (NEXT_DEP - TIME) * QUEUE;
    RESPONSE_TIMES[i] = SERVICE_TIMES[i] + WAIT_TIMES[i];
  } else {SERVICE_TIMES[i] = 0;}

  if (EVENT <= 0) {
    if (SYSTEM > 0) NEXT_DEP = TIME + DepartureLookup();
    else NEXT_DEP = NEXT_ARR + DepartureLookup();
  }

  if (NEXT_ARR < NEXT_DEP) {NEXT_EVENT = 1; NEXT_TIME = NEXT_ARR;}
  else if (NEXT_DEP < NEXT_ARR) {NEXT_EVENT = -1; NEXT_TIME = NEXT_DEP;}
  else {NEXT_EVENT = 0; NEXT_TIME = NEXT_ARR;}
  TIMES[i] = NEXT_TIME - TIME;
  if (SYSTEM > 0) {
    ACTIVE += NEXT_TIME - TIME; ACTIVITY[i] = 1;
  } else {ACTIVITY[i] = 0;}
}
void CalcAVG() {
  for (int i = 0; i < N; i++) {
    AVG_A += INTERARRIVALS[i];
    AVG_S += SERVICE_TIMES[i];
    AVG_R += RESPONSE_TIMES[i];
  }
  AVG_A /= double(ARRIVALS);
  AVG_S /= double(ARRIVALS);
  AVG_R /= double(ARRIVALS);

  AVG_Q = double(QSUM) / double(N);
  AVG_U = double(ACTIVE) / TIME;
}
void CalcSD() {
  double sos_a = 0, sos_s = 0, sos_q = 0, sos_u = 0, sos_r = 0;
  for (int i = 0; i < N; i++) {
    if (INTERARRIVALS[i] > 0) sos_a += pow(INTERARRIVALS[i] - AVG_A, 2.0);
    if (SERVICE_TIMES[i] > 0) {
      sos_s += pow(SERVICE_TIMES[i] - AVG_S, 2.0);
      sos_r += pow(RESPONSE_TIMES[i] - AVG_R, 2.0);
    }
    sos_q += pow(double(QUEUE_SIZES[i]) - AVG_Q, 2.0);

    if (ACTIVITY[i]) {
      for (int j = 0; j < TIMES[i]; j++) {sos_u += pow(1.0 - AVG_U, 2.0);}
    }
    else sos_u += pow(0.0 - AVG_U, 2.0);
  }

  SD_A = sqrt(sos_a / double(ARRIVALS));
  SD_S = sqrt(sos_s / double(ARRIVALS));
  SD_Q = sqrt(sos_q / double(N));
  SD_U = sqrt(sos_u / TIME);
  SD_R = sqrt(sos_r / double(ARRIVALS));
}
void DisplayResults() {
  cout << "\nAverage Interarrivals: " << AVG_A
      << "\t, Standard Deviation: " << SD_A;
  cout << "\nAverage Service Time: " << AVG_S
      << "\t, Standard Deviation: " << SD_S;
  cout << "\nAverage Queue Length: " << AVG_Q
      << "\t, Standard Deviation: " << SD_Q;
  cout << "\nAverage Utilization: " << AVG_U
      << "\t, Standard Deviation: " << SD_U;
  cout << "\nAverage Response Time: " << AVG_R
      << "\t, Standard Deviation: " << SD_R << endl;
}
