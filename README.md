# os-experiments

This repository was designed to test and validate beliefs about operating systems and computer architecture so that I use it for my own reference later down the line.

### Ram vs Cache latency using C++ | raw-vs-l1-latency.cpp

Using my experiment, I found that cache access was about 5x faster - I tested this by using an inorder traversal vs random traversal of a very large array, causing the random approach to have to run to RAM to fetch the values.

### Single vs Multithreaded using C++ | concurrency.cpp

Want to see after how many operations is it actually beneficial to use multithreading over single threaded. I wanted to explore to see if there's a trade off from overhead of locking (through a mutex) the shared memory buffer (counter) that is being updated or not when theres a lot of processes. I want to understand the tradeoffs of multithreading and see when it can truly be useful.
