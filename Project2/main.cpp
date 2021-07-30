#include <iostream>
#include <vector>
#include <list>

int main() {
	std::vector<int> num;
	num.reserve(6);
	num.emplace_back(4);
	num.emplace_back(5);
	num.emplace_back(6);

	auto itr = num.begin();
	std::cout << *itr << std::endl;
	num.insert(++num.begin(),2);
	std::cout << *itr << std::endl;
	num.insert(++num.begin(), 3);
	std::cout << *itr << std::endl;
	num.insert(++num.begin(), 4);
	std::cout << *itr << std::endl;

}