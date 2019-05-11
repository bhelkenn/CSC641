#include <iostream>

using namespace std;

int SP = 3, SD = 10, N = 8, VISITS = 40, Z = 0;
double X;
double QP = 0, Q1 = 0, Q2 = 0, Q3 = 0, Q4 = 0;
double DP, D1, D2, D3, D4;
double UP, U1, U2, U3, U4;
double RP, R1, R2, R3, R4, R;

void ResidenceCalcs();
void QueueCalcs();
void UtilizationCalcs();
void OutputResults();
int main() {
  DP = SP * VISITS;
  D1 = D2 = D3 = D4 = SD * (VISITS / 4);

  for (int i = 1; i <= N; i++) {
    ResidenceCalcs();
    R = RP + R1 + R2 + R3 + R4;
    X = 1.0 / (Z + R);
    QueueCalcs();
  }
  UtilizationCalcs();
  OutputResults();

  return 0;
}

void ResidenceCalcs() {
  RP = DP * (1 + QP);
  R1 = D1 * (1 + Q1);
  R2 = D2 * (1 + Q2);
  R3 = D3 * (1 + Q3);
  R4 = D4 * (1 + Q4);
}
void QueueCalcs() {
  QP = X * RP;
  Q1 = X * Q1;
  Q2 = X * Q2;
  Q3 = X * Q3;
  Q4 = X * Q4;
}
void UtilizationCalcs() {
  UP = X * DP;
  U1 = X * D1;
  U2 = X * D2;
  U3 = X * D3;
  U4 = X * D4;
}
void OutputResults() {
  cout << "Throughput (X):\t\t" << X << endl;
  cout << "Response Time (R):\t" << R << endl;
  cout << "Utilization of CPU:\t" << UP << endl;
  cout << "Utilization of D1:\t" << U1 << endl;
  cout << "Utilization of D2:\t" << U2 << endl;
  cout << "Utilization of D3:\t" << U3 << endl;
  cout << "Utilization of D4:\t" << U4 << endl;
}
