#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

// 1) A small helper function that runs any callable and returns elapsed µs
template <typename F>
long long measure_us(F&& fn) {
  using Clock = std::chrono::steady_clock;
  using us = std::chrono::microseconds;

  auto start = Clock::now();
  fn();
  auto end = Clock::now();

  return std::chrono::duration_cast<us>(end - start).count();
}

int counter1{0};
int counter2{0};

void increment_counter(int number_increments) {
  for (int i = 0; i < number_increments; ++i) {
    ++counter1;
  }
}

long long p1(int cycles) {
  return measure_us([cycles] { increment_counter(cycles); });
}

int p2(int cycles) { return 0; }

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    return 1;
  }

  int cycles = std::stoi(argv[1]);
  long long time1 = p1(cycles);
  std::cout << "Time elapsed with no concurrency " << time1 << " microseconds! "
            << '\n';

  return 0;
}
