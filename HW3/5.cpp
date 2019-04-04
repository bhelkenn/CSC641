#include <iostream>

using namespace std;

int main() {
  int x = 0;
  for (int i = 1; i <= 256; i++) {
    x = (13 * x + 85) % 256;
    cout << x << " ";
    if (i % 16 == 0) cout << endl;
  }
  return 0;
}
