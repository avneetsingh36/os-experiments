#include <iostream>

unsigned long long factorial(unsigned long long y) {
  if (y <= 1) {
    return 1;
  }
  return y * factorial(y - 1);
}

int main() {
  long long x;
  std::cout << "Which number would you like to see the factorial of: ";
  std::cin >> x;

  if (x < 0) {
    std::cerr << "Error: you cannot enter a negative number\n";
    return 1;
  }

  // cast to unsigned to double the number of positive numbers and remove
  // regatives from consideration
  unsigned long long result = factorial(static_cast<unsigned long long>(x));

  std::cout << "The factorial of " << x << " is " << result << '\n';

  return 0;
}
