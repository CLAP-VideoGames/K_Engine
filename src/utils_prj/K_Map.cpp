#include "K_Map.h"
#include <string>

K_Engine::K_Map::K_Map()
{

}

K_Engine::K_Map::~K_Map()
{

}

void K_Engine::K_Map::addPair(std::string key, std::string value)
{
	information.emplace(key, value);
}

bool K_Engine::K_Map::valueToBool(std::string key)
{
	auto iterator = information.find(key);

	if (iterator->second == "false") return false;

	return true;
}

double K_Engine::K_Map::valueToNumber(std::string key)
{
	auto iterator = information.find(key);

	return std::stod(iterator->second);
}

K_Engine::Vector3 K_Engine::K_Map::valueToVector3(std::string key)
{
	auto iterator = information.find(key);

	int x, y, z;


	std::string numbers = iterator->second;

	std::string number;
	int nextDigit = 0;
	for (int i = 0; i < numbers.length(); i++) {
		number = numbers[i];

		if (number == ",")nextDigit++;
		else if (number != " " && number != "{" && number != "}") {
			int digit = std::stod(number);

			if (nextDigit == 0) x = digit;
			else if (nextDigit == 1) y = digit;
			else z = digit;
		}
	}


	K_Engine::Vector3 vector = K_Engine::Vector3(x,y,z);

	return vector;
}


