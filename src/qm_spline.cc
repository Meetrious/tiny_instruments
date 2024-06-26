/* This cpp-module constains non-member function that formulates the shape of
3DEG spline equations depending on initial interpolation data. */

#include <cmath>
#include <iostream>
#include <tiny_instruments/qm_spline.h>

using namespace QMSpline;

std::vector<SplineData_t> 
QMSpline::get_coefs(IniData_t const& ini) {
  double H_e;

  double alp;  // первый угол кусочно-линейного приближения
  double bet;  // второй угол кусочно-линейного приближения

  size_t N_e = ini.size() - 1;  // кол-во промежутков интерполяции

  std::vector<SplineData_t> res(N_e + 1);

  // заполняем начальное условие

  res[0][0] = ini[0][0];
  res[0][1] = ini[0][1];
  res[0][2] = 0;  // первая производная = 0 в начальной точке

  for (size_t i = 1; i <= N_e; ++i) {
    res[i][0] = ini[i][0];
    res[i][1] = ini[i][1];
    H_e = ini[i - 1][0] - ini[i][0];

    if (i == N_e) {  // если мы на последнем промежутке интерполяции
      res[i][2] = 0;  // то первая производная на правом краю зануляется
    } else {
      // Проверяем узел на дискретный экстремум
      bool is_mid_knot_extremum =
          (ini[i][1] >= ini[i - 1][1] && ini[i][1] >= ini[i + 1][1]) ||
          (ini[i][1] <= ini[i - 1][1] && ini[i][1] <= ini[i + 1][1]);

      if (is_mid_knot_extremum) {
        res[i][2] = 0;
      } else {  // иначе усредним угол между узлами, в которых график имеет
                // монотонное поведение, линейной склейкой
        bet = std::atan((ini[i + 1][1] - ini[i][1]) /
                        (ini[i + 1][0] - ini[i][0]));
        alp = std::atan((ini[i][1] - ini[i - 1][1]) /
                        (ini[i][0] - ini[i - 1][0]));

        // вычисляем первую производную в t[i]
        res[i][2] = std::tan(alp - (alp - bet) / 2);
      }
    }

    res[i][4] =  // вычисляем шестую 3й производной в t[i]
        (1.0 / std::pow(H_e, 2)) * (res[i][2] + res[i - 1][2]) +
        (2.0 / std::pow(H_e, 3)) * (res[i][1] - res[i - 1][1]);

    res[i][3] =  // вычисляем половину 2й производной в t[i]
        (1.0 / std::pow(H_e, 2)) * (res[i - 1][1] - res[i][1]) -
        (1.0 / H_e) * res[i][2] - H_e * res[i][4];

    // для отчетности выводим в stdout данные сплайнов на данном i-промежутке
    // (можно удалить)
    std::cout << "[" << ini[i - 1][0] << ", " << res[i][0] << "]"
              << "  ==>  ";  // интерполируемый промежуток

    std::cout << "y = "
			<< res[i][1] << " + "  // свободный член 3DEG сплайна
    	<< res[i][2] << "*(x - " << res[i][0] << ") + "  // коэффициент при первой степени переменной 3DEG сплайна
      << res[i][3] << "*(x - " << res[i][0] << ")^2 + "  // коэффициент при второй степени переменной 3DEG сплайна
    	<< res[i][4] << "*(x - " << res[i][0] << ")^3"  // коэффициент при третьей степени переменной 3DEG сплайна
      << std::endl;

    // Вот всё и готово для построения сплайна на промежутке [x_(i-1), x_i]
  }
  return res;
}
