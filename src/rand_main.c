#include <tiny_instruments/easy_random.h>
#include <stdio.h>

// gcc rand_main.c easy_random.c -I path/to/include/dir -o get_rand.out

int main () {
  printf("%f\n",get_random(3,5));
}