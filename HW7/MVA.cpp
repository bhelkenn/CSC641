#include <iostream>

using namespace std;

int SP = 3, SD = 10, N = 8, VISITS = 40, Z = 0, K = 1;
double X;
double QP = 0, Q1 = 0, Q2 = 0, Q3 = 0, Q4 = 0;
double DP, D1, D2, D3, D4;
double UP, U1, U2, U3, U4;
double RP, R1, R2, R3, R4, R;

void MVA();
void ResidenceCalcs();
void QueueCalcs();
void UtilizationCalcs();
void OutputResults();
int main() {
  for (int i = 0; i < 6; i++) {
    if (i % 2 == 0) D1 = D2 = D3 = D4 = SD * (VISITS * 0.25);
    else {
      D1 = SD * (VISITS * 0.4);
      D2 = SD * (VISITS * 0.3);
      D3 = SD * (VISITS * 0.2);
      D4 = SD * (VISITS * 0.1);
    }
    if (i >= 4) Z = 5000;
    if (i == 2 || i == 3) K = 2;
    if (i == 0) cout << "\nSCENARIO 1 - BALANCED:";
    else if (i == 1) cout << "\nSCENARIO 1 - NON-BALANCED:";
    else if (i == 2) cout << "\nSCENARIO 4 - BALANCED:";
    else if (i == 3) cout << "\nSCENARIO 4 - NON-BALANCED:";
    else if (i == 4) cout << "\nSCENARIO 3 - BALANCED:";
    else cout << "\nSCENARIO 3 - NON-BALANCED:";
    DP = SP * VISITS / K;
    MVA(); OutputResults();
  }
  return 0;
}

void MVA() {
  for (int i = 1; i <= N; i++) {
    ResidenceCalcs();
    R = RP + R1 + R2 + R3 + R4;
    X = i / (Z + R);
    QueueCalcs();
  }
  UtilizationCalcs();
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
  Q1 = X * R1;
  Q2 = X * R2;
  Q3 = X * R3;
  Q4 = X * R4;
}
void UtilizationCalcs() {
  UP = X * DP;
  U1 = X * D1;
  U2 = X * D2;
  U3 = X * D3;
  U4 = X * D4;
}
void OutputResults() {
  cout << "\nThroughput (X):\t\t" << X << " / ms" << endl;
  cout << "Response Time (R):\t" << R << " ms" << endl;
  cout << "Queue Length of CPU:\t" << QP << endl;
  cout << "Queue Length of D1:\t" << Q1 << endl;
  cout << "Queue Length of D2:\t" << Q2 << endl;
  cout << "Queue Length of D3:\t" << Q3 << endl;
  cout << "Queue Length of D4:\t" << Q4 << endl;
  cout << "Utilization of CPU:\t" << UP * 100 << " %" << endl;
  cout << "Utilization of D1:\t" << U1 * 100 << " %" << endl;
  cout << "Utilization of D2:\t" << U2 * 100 << " %" << endl;
  cout << "Utilization of D3:\t" << U3 * 100 << " %" << endl;
  cout << "Utilization of D4:\t" << U4 * 100 << " %" << endl;
}
