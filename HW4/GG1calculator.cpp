#include <iostream>
#include <math.h>

using namespace std;

double R, A, VA, S, VS, U, Q;
void DisplayChoices(string);
int DefineParameters(string, double&);
int main() {
  int adist = DefineParameters("interarrival", VA);
  int sdist = DefineParameters("service", VS);

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
int DefineParameters(string type, double &cov) {
  int choice = 0;
  DisplayChoices(type); cin >> choice;
  while (choice < 1 || choice > 3) {
    DisplayChoices(type); cin >> choice;
  }

  if (choice == 1) {
    cov = 0.0;
    if (type == "interarrival") A = 2.0;
    else if (type == "service") S = 1.0;
    else cout << "\noops! problem in DefineParameters()::choice 1\n";
  }
  else if (choice == 2) {
    cov = 1.0;
    if (type == "interarrival") A = 2.0;
    else if (type == "service") S = 1.0;
    else cout << "\noops! problem in DefineParameters()::choice 2\n";
  }
  else {
    int a = 1, b;
    if (type == "interarrival") {b = 3; A = (a + b) / 2.0;}
    else if (type == "service") {b = 2; S = (a + b) / 2.0;}
    else cout << "\noops! problem in DefineParameters()::choice 3\n";
    cov = (b - a) / ((a + b) * sqrt(3.0));
  }

  return choice;
}
