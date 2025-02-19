#include <tiny_instruments/iterable_enum.hpp>

#include <iostream>

// g++ src/iterable_enum_main.cpp -std=c++11 -I include

iterable_enum(TCP,
  (name1, 0x2),
   name2,
   name3,
   name4,
  (name5, 0x3)
);

void foo(const TCP tcp) {
  std::cout << "FOO " << int(tcp);
}

int main () {
  TCP my_tcp = TCP(3);
  std::cout << int(my_tcp);

	for (const auto & tcp: TCP_items) {
		std::cout << int(tcp) << "\n";
	}
}