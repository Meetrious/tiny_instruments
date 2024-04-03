#include <tiny_instruments/easy_random.h>
#include <iostream>

// g++ rand_main.cpp easy_random.cc -I path/to/include/dir -o get_rand.out

int main () {
  std::printf("%f\n", my_rand::get(3,5));
}