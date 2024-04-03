#ifndef EASY_RANDOM_H_
#define EASY_RANDOM_H_

#ifdef __cplusplus
namespace my_rand {
double get(double a, double b);
}

#else
double get_random(double a, double b);
#endif  //  __cplusplus

#endif  // EASY_RANDOM_H_
