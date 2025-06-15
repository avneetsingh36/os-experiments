#include <iostream>
#include <typeinfo>

void foo(auto var) {
  std::cout << "The type is " << typeid(var).name() << "." << '\n';
}

int main() {
  std::cout << "We are going to test out the types of certain literals."
            << '\n';

  auto v1 = "Hello!";
  foo(v1);
  return 0;
}
