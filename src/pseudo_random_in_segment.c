#include <stdbool.h>
#include <time.h>

float get_random(float a, float b) {
  /* поле статическое, потому что нам необходимо, чтобы
   * состояние переменной сохранилось при следующем вызове
   * этой функции */
  static bool is_seed_planted = 0;

  if (!is_seed_planted) {
    /* генерируем псевдорандомный набор
     * на основании значения таймера процессора */
    srand(time(0));
    is_seed_planted = 1;
  }

  float tmp = (rand() % 10001) / 10000.0;
  return a + (b - a) * tmp;
}
