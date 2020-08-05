#include <iostream>

#include "MovingAverage.h"

using namespace std;

int main() {
  unsigned size = 0;
  cin >> size;

  MovingAverage<int> test(size);
  int in = 1;

  while (in != 0) {
    cin >> in;
    // Pushes the input in the moving average object
    test.push(in);

    // Prints each value stored in the moving average
    cout << "[ ";
    for (uint8_t i = 0; i < test.size(); i++) {
      cout << test[i] << " ";
    }
    // Prints the result of the average
    cout << "] = " << test.get();
    // Prints the value stored in the first and last indexes
    cout << " | f: " << test.front() << " b: " << test.back() << endl;

    cout << "[ ";
    for (uint8_t i = 0; i < test.size(); i++) {
      cout << test.atIndex(i) << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}
