#include <iostream>

#include "transform.hpp"

using namespace GLRT;

int main() {
	auto t = Transform::scale_matrix({{2, 1, 3}});
	std::cout << t.to_string() << std::endl;

	auto t2= Transform::translation_matrix({{10, 2 ,4}});
	std::cout << t2.to_string() << std::endl;

	auto t3 = Transform::rotation_matrix({{0, 0, 1}}, 0);
	std::cout << t3.to_string() << std::endl;

	std::cout << (t * t2 * t3).to_string() << std::endl;
}
