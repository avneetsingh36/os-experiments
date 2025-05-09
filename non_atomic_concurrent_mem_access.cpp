#include <iostream>
#include <thread>

int counter{0};

void increment(int cycles) {
  for (int i = 0; i < cycles; ++i) {
    ++counter;
  }
}

int main() {
  std::cout << "Counter: " << counter << '\n';

  int cycles;
  std::cout << "How many cycles do you want to run: ";
  std::cin >> cycles;

  std::thread t1(increment, cycles);
  std::thread t2(increment, cycles);

  t1.join();
  t2.join();

  std::cout << "Counter: " << counter << '\n';

  return 0;
}
