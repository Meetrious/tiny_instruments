#ifndef QM_SPLINE_H_
#define  QM_SPLINE_H_

#include <vector>
#include <array>

// Quasi_Monotonous
namespace QMSpline {

using IniData_t = std::vector<std::array<double, 2>>;
using SplineData_t = std::array<double, 5>;

/** \brief функция по исходным данным интерполяции переданным в матрице (N х 2)
 * возвращает матрицу (N-1 x 5) с коэффициентами сплайна для соответствующего
 * промежутка интерполяции.
 * \param ini матрица (N х 2) из данных (x, y). Для корректной отработки
 * данные x необходимо передавать по возрастанию вместе с индексом строки
 * \returns матрица (N x 5), где первая строка фиктивная,
 * остальные соответствуют коэффициентам 3-степенного полинома,
 * интерполирующего соответствующий промежуток между данными из ini.
 * [i][0] - левый край текущего промежутка интерполяции
 * [i][j]: j = 1,2,3,4 - коэффициенты полинома от переменной (x - res[i][0]);
 * 
 * Побочно стреляет в stdout пояснение к решённой задачи интерполяции.
*/
std::vector<SplineData_t> get_coefs(IniData_t const& ini);

}  // namespace QMSpline

#endif  // QM_SPLINE_H_
