#include <iostream>
#include <math.h>

using namespace std;

double R, A, VA, S, VS, U, Q;
void DisplayChoices(string);
int DefineParameters(string, double &, double &);
int main() {
  int adist = DefineParameters("interarrival", A, VA);
  int sdist = DefineParameters("service", S, VS);

  U = S / A; //S * X, X = 1 / A
  double gi_g = ((VS*VS + 1.0) * (VA*VA - 1.0) / (U*U * VS*VS + 1.0));
  R = (S / (1.0 - U)) * (1.0 - 0.5*U * (1.0 - VS*VS - gi_g));
  if (adist == 1 && sdist == 1) Q = U;
  else Q = U / (1.0 - U);

  cout << "\nServer utilization (U): " << U;
  cout << "\nMean response time (R): " << R;
  cout << "\nMean queue length (Q): " << Q;
  cout << "\nTime spent waiting (W): " << R - S << endl;
  return 0;
}

void DisplayChoices(string type) {
  cout << "\nThe available " << type << " time distributions are:";
  cout << "\n\t(1) Constant";
  cout << "\n\t(2) Exponential";
  cout << "\n\t(3) Uniform";
  cout << "\nEnter your choice: ";
}
int DefineParameters(string type, double &value, double &cov) {
  int choice = 0;
  DisplayChoices(type); cin >> choice;
  while (choice < 1 || choice > 3) {
    DisplayChoices(type); cin >> choice;
  }

  if (choice == 1) {
    cov = 0.0;
    cout << "Constant " << type << " time: "; cin >> value;
  }
  else if (choice == 2) {
    cov = 1.0;
    cout << "Mean " << type << " time: "; cin >> value;
  }
  else {
    int a, b;
    cout << "Enter min and max " << type << " times: "; cin >> a >> b;
    value = (a + b) / 2.0;
    cov = (b - a) / ((a + b) * sqrt(3.0));
  }

  return choice;
}
