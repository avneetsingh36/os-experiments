#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
  const int N = 10'000'000;   // 10 million integers (way bigger than L1 cache)
  std::vector<int> arr(N, 1); // fill array with 1s

  // Create a random access order
  std::vector<int> indices(N);
  for (int i = 0; i < N; ++i)
    indices[i] = i;
  std::shuffle(indices.begin(), indices.end(),
               std::mt19937{std::random_device{}()});

  int sum = 0;

  // --- Sequential access ---
  auto start_seq = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) {
    sum += arr[i];
  }
  auto end_seq = std::chrono::high_resolution_clock::now();
  std::cout << "Sequential access time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end_seq -
                                                                     start_seq)
                   .count()
            << " ms\n";

  sum = 0; // Reset

  // --- Random access ---
  auto start_rand = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) {
    sum += arr[indices[i]];
  }
  auto end_rand = std::chrono::high_resolution_clock::now();
  std::cout << "Random access time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end_rand -
                                                                     start_rand)
                   .count()
            << " ms\n";

  return 0;
}
