#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** 
 * \brief функция, которая умеет перечислять возрастающие сочетания
 *  из k-шт элементов множества {0,1,2, ..., n}
 *  без повторений и выводить их в stdout. 
 * Если перепутать k и n, то не беда.
 * Не возбраняется её модифицировать под свои нужды. В теле 
 * прокомментировано место, в котором этим безопасно заниматься.
 * 
 * \param k длина сочетания
 * 
 * \param n кол-во объектов для составления сочетаний
 * 
 * \param arr указатель на внутренний массив,
 *  содержащий числа, составляющие сочетания.
 * По умолчанию = NULL
 * 
 * \param counter внутренний счётчик.
 * По умолчанию = 0
 * */
void list_asc_perms(int k, int n, int *arr, int counter);

/* макроопределение для безопасного использования рекурсивной функции. */
#define list_ascending_permutations(K,N) list_asc_perms(K, N, NULL, 0)

void list_asc_perms(int k, int n, int *arr, int counter) {
  bool flag = 0;
  if (k > n) {
    int tmp = k;
    k = n;
    n = tmp;
  }
  if (arr == NULL) {
    counter = 1;
    arr = (int *)malloc((k + 1) * sizeof(int));
    arr[0] = -1;
    flag = 1;
  }

  if (counter == k + 1) {
    /* в этом условном блоке готов результат;
     * arr[1], arr[2], ..., arr[k] суть - текущее возрастающее
     * сочетание k элементов из множества {0, 1, ... , n-1}
     * Здесь, к примеру, можно организовать перечисление размещений
     * текущего сочетания по k позициям, но это уже будет новая функция.
     * В остальном, можно стереть ниже представленный вывод в stdout
     * и записать arr[i] - элементы в какой нибудь массив, чтобы использовать
     * результат где-нибудь ещё, соответствующим образом модифицировав сигнатуру. */

    for (int i = 1; i <= k; i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");

  } else {
    for (int i = arr[counter - 1] + 1; i < n - k + counter; i++) {
      arr[counter] = i;
      counter++;
      list_asc_perms(k, n, arr, counter);
      counter--;
    }
  }
  if (flag == 1) free(arr);
}

int main () {
  list_ascending_permutations(4, 5);
}