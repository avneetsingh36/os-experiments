# os-experiments

This repository was designed to test and validate beliefs about operating systems and computer architecture so that I use it for my own reference later down the line.

### Ram vs Cache latency using C++ | raw-vs-l1-latency.cpp

Using my experiment, I found that cache access was about 5x faster - I tested this by using an inorder traversal vs random traversal of a very large array, causing the random approach to have to run to RAM to fetch the values.

### Single vs Multithreaded using C++ | concurrency.cpp

**Goal**  
Find out after how many increments multithreading (4 threads + one atomic add per thread) actually outperforms a single-threaded loop.

**Key Results**

| Total Increments | Single-thread (µs) | 4-threaded (µs) |
|-----------------:|-------------------:|----------------:|
| 10⁵              | 249                | 555             |
| 10⁶              | 958                | 991             |
| 10⁷              | 16 195             | 3 572           |
| 10⁸              | 100 519            | 20 793          |

**Takeaways**  
- **Overhead dominates** for small N (multithread > single).  
- **Break-even** at around ~10⁶–10⁷ iterations.  
- **Clear win** beyond ~10⁷ increments, as work amortizes thread and atomic costs.  
- For a perfectly fair comparison, pre-spawn threads or align thread-count with `hardware_concurrency()`.  

### Race Condition with Non-Atomic Counter | mem.cpp

**Goal**  
Show how two threads incrementing a shared non-atomic counter lose updates due to data races.

**Results**

| Cycles per Thread | Expected Total | Observed Total |
|------------------:|---------------:|---------------:|
| 10²               | 200            | 200            |
| 10³               | 2 000          | 2 000          |
| 10⁴               | 20 000         | 20 000         |
| 10⁵               | 200 000        | 127 858        |
| 10⁶               | 2 000 000      | 1 018 846      |

**Takeaways**  
- For small N, the race rarely manifests—both threads see most increments.  
- Past ~10⁵ increments, lost updates spike (≈36% lost at 10⁵, ≈49% at 10⁶).  
- To avoid this, use `std::atomic<int>` or synchronize access (e.g., a mutex), so increments become thread-safe.

