#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int counter1{0};
int counter2{0};

template <typename F>
long long measure_us(F&& fn) {
  using Clock = std::chrono::steady_clock;
  using us = std::chrono::microseconds;

  auto start = Clock::now();
  fn();
  auto end = Clock::now();

  return std::chrono::duration_cast<us>(end - start).count();
}

void increment_counter(int number_increments) {
  for (int i = 0; i < number_increments; ++i) {
    ++counter1;
  }
}

void threaded_counter(int cycles) {}

long long p1(int cycles) {
  return measure_us([cycles] { increment_counter(cycles); });
}

long long p2(int cycles) {
  return measure_us([cycles] { threaded_counter(cycles); });
}

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    std::cout << "Hey, you forgot to tell me how many cycles to run!";
    return 1;
  }

  int cycles = std::stoi(argv[1]);

  long long time1 = p1(cycles);
  std::cout << "Time elapsed with no concurrency " << time1 << " microseconds!"
            << '\n';

  long long time2 = p2(cycles);
  std::cout << "Time elapsed with concurrency " << time2 << " microseconds!"
            << '\n';

  return 0;
}
