#include <tiny_instruments/qm_spline.h>

// g++ spl_main.cpp qm_spline.cc -I path/to/include/dir -o 3_spline_builder.out

int main() {
	QMSpline::get_coefs({{0, 0}, {1,9}, {5,5}, {7,2}, {17, 11}, {19,9}});
}
