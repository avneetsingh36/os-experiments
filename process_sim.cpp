#include <unistd.h>

#include <iostream>

int myNumber = 100;

int main() {
  // process ID will be 0 for a successful child process

  pid_t pid = fork();

  if (pid < 0) {
    std::cout << "Fork failed";
  } else if (pid == 0) {
    myNumber = 200;
    std::cout << "I am the child process with PID: " << pid << '\n';
    std::cout << "My number from the child process is: " << myNumber << '\n'
              << '\n';
  } else {
    // will ensure that we wait for the child to go first
    // notice how the VAS is diffferent the second the fork() happens
    int status;
    waitpid(pid, &status, 0);
    std::cout << "Hello from the parent process with PID: " << pid << '\n';
    std::cout << "My number is from the parent process is: " << myNumber
              << '\n';
  }

  return 0;
}
