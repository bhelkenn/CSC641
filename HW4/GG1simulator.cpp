#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;
int EVENT = 0, TIME = 0, SYSTEM = 0;
int QUEUE = 0, NEXT_ARRIVAL, NEXT_DEPARTURE;
int NEXT_EVENT = 0, NEXT_TIME = 0;
int ARRIVALS = 0; DEPARTURES = 0;
int QSUM = 0; IDLE = 0;
int N = 10;
// need arrays for standard deviations of each of the 5 averages

double RNG() {return double(rand()) / double(RAND_MAX);}
int ArrivalLookup();
int DepartureLookup();
void UpdateCounters();
void UpdateArrival();
void UpdateDeparture();
void UpdateEvent();
void UpdateTime();
void DisplayStats();
int main() {
  srand(time(NULL));
  for (int i = 0; i < N; i++) {
    UpdateCounters();
    UpdateArrival(); UpdateDeparture();
    UpdateEvent(); UpdateTime();
    DisplayStats();
  }
  double arrival_avg = double(NEXT_ARRIVAL) / double(ARRIVALS);
  double service_avg = double(NEXT_DEPARTURE) / double(DEPARTURES);
  double queue_avg = double(QSUM) / double(N);
  double util_avg = 1.0 - double(IDLE) / double(TIME);
  int processing_time = TIME - IDLE;
  double response_avg = double(processing_time) / double(DEPARTURES);


  return 0;
}
int ArrivalLookup() {
  double rng = RNG();
  if (rng < 0.5) return 3;
  else if (rng < 0.8) return 2;
  else return 4;
}
int DepartureLookup() {
  double rng = RNG();
  if (rng < 0.6) return 2;
  else if (rng < 0.9) return 5;
  else return 1;
}

void UpdateCounters() {
   EVENT = NEXT_EVENT;
   TIME = NEXT_TIME;
   SYSTEM += EVENT;
   if (SYSTEM > 0) {QUEUE = SYSTEM - 1;} QSUM += QUEUE;
}
void UpdateArrival() {
  if (EVENT >= 0) {
    ARRIVALS++;
    NEXT_ARRIVAL = TIME + ArrivalLookup();
  }
}
void UpdateDeparture() {
  if (EVENT <= 0) {
    DEPARTURES++;
    if (SYSTEM > 0) NEXT_DEPARTURE = TIME + DepartureLookup();
    else NEXT_DEPARTURE = NEXT_ARRIVAL + DepartureLookup();
  }
}
void UpdateEvent() {
  if (NEXT_ARRIVAL < NEXT_DEPARTURE) NEXT_EVENT = 1;
  else if (NEXT_DEPARTURE < NEXT_ARRIVAL) NEXT_EVENT = -1;
  else NEXT_EVENT = 0;
}
void UpdateTime() {
  if (NEXT_ARRIVAL <= NEXT_DEPARTURE) NEXT_TIME = NEXT_ARRIVAL;
  else NEXT_TIME = NEXT_DEPARTURE;
  if (SYSTEM == 0) IDLE += NEXT_TIME - TIME;
}
void DisplayStats() {
  cout << "\n\nEvent: " << EVENT << "\tTime: " << TIME;
  cout << "\tSystem: " << SYSTEM << "\tQueue: " << QUEUE;
  cout << "\nNext Arrival: " << NEXT_ARRIVAL;
  cout << "\tNext Departure: " << NEXT_DEPARTURE;
  cout << "\nNext Event: " << NEXT_EVENT
       << "\tNext Time: " << NEXT_TIME;
}
