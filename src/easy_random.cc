#include <tiny_instruments/easy_random.h>

#include <ctime>
#include <cstdlib>

double my_rand::get(double a, double b) {
  /* поле статическое, потому что нам необходимо, чтобы
   * состояние переменной сохранилось при следующем вызове
   * этой функции */
  static bool is_seed_planted = 0;

  if (!is_seed_planted) {
    /* генерируем псевдорандомный набор
     * на основании значения таймера процессора */
    std::srand(std::time(0));
    is_seed_planted = 1;
  }

  double tmp = (std::rand() % 1000001) / 1000000.0;
  return a + (b - a) * tmp;
}
