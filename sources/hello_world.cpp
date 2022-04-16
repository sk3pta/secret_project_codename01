#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  std::string name; // We initialize the name variable of type string
  std::cout << "Input user_name"; // Please enter your username
  std::cin >>
    name; // We request the value of the variable name from the I/O stream
  std::cout << "Hello world from " << name << std::endl; // Bringing out the hello
  return 0;
}
