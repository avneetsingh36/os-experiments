#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

int counter1{0};
std::atomic<int> counter2{0};

std::mutex mtx;

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

void threaded_counter(int number_increments) {
  int local = 0;
  for (int i = 0; i < number_increments; ++i) local++;
  counter2.fetch_add(local, std::memory_order_relaxed);
}

long long p1(int cycles) {
  return measure_us([cycles] { increment_counter(cycles); });
}

long long p2(int cycles) {
  return measure_us([cycles] {
    int half = cycles / 4;
    std::thread t1(threaded_counter, half);
    std::thread t2(threaded_counter, half);
    std::thread t3(threaded_counter, half);
    std::thread t4(threaded_counter, half);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
  });
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
