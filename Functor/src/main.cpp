#include <iostream>
using namespace std;

class myFunc {
 private:
  int _count;

 public:
  myFunc(int a) : _count(a) {}

  int operator()(int x) { return x + _count; }
};

int main() {
  myFunc obj(10);
  cout << obj(2) << endl;
  return 0;
}