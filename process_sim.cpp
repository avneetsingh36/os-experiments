#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

int myNumber = 100;

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    std::perror("fork");
    return 1;
  }

  if (pid == 0) {
    // Child
    myNumber = 200;
    std::cout << "I am the child process with PID: " << getpid() << '\n';
    std::cout << "My number from the child process is: " << myNumber << '\n'
              << '\n';
    return 0;

  } else {
    // will ensure that we wait for the child to go first
    // notice how the VAS is diffferent the second the fork() happens
    int status;
    if (waitpid(pid, &status, 0) < 0) {
      std::perror("waitpid");
    }

    std::cout << "Hello from the parent process with PID: " << getpid() << '\n';
    std::cout << "My number is from the parent process is: " << myNumber
              << '\n';
  }

  return 0;
}
