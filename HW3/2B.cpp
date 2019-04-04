#include <iostream>
#include <math.h>

using namespace std;
int RPM = 7200, CAPACITY = 300 * 1024 /* in KB */, CYLINDERS = 900;

double WaitTime();
double SeekTime(double &);
int main() {
  double filesize = 100 * 1024; // in KB
  double access_time = WaitTime() + SeekTime(filesize);
  cout << "Total access time: " << access_time << endl;
  return 0;
}

double WaitTime() {
  double wait_time = 60.0 / 2.0 / RPM * 1000;
  cout << "Total wait time: " << wait_time << endl;
  return wait_time; //returns as milliseconds
}

double SeekTime(double &filesize) {
  double cyl_traversed = filesize / CAPACITY * CYLINDERS;
  double seek_time = sqrt((cyl_traversed - 1));
  cout << "Total seek time: " << seek_time << endl;
  return seek_time;
}
