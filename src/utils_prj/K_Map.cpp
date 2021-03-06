#include "K_Map.h"
#include <utils_prj/Vector3.h>
#include <vector>
#include <script_prj/ScriptManager.h>

namespace K_Engine {

	K_Map::K_Map()
	{

	}

	K_Map::~K_Map()
	{

	}

	void K_Map::addPair(std::string key, std::string value)
	{
		information.emplace(key, value);
	}

	bool K_Map::valueToBool(std::string key)
	{
		auto iterator = information.find(key);

		if (iterator->second == "false") return false;

		return true;
	}

	double K_Map::valueToNumber(std::string key)
	{
		auto iterator = information.find(key);

		return std::stod(iterator->second);
	}

	std::string K_Map::value(std::string key){
		auto iterator = information.find(key);

		//information.find();
		return iterator->second;
	}

	bool K_Map::hasValue(std::string key){
		return (information.find(key) != information.end());
	}

	std::function<void(std::string)> K_Map::valueToCallback(std::string value)
	{
		std::function<void(std::string)> f = [=](std::string value) {
			ScriptManager::GetInstance()->callLuaCallback(value);
		};

		return f;
	}

	Vector3* K_Map::valueToVector3(std::string key)
	{
		auto iterator = information.find(key);
		double x = 0, y = 0, z = 0;
		std::string numbers = iterator->second;

		std::istringstream f(numbers);
		std::string s;
		std::vector<double> digits;

		while (getline(f, s, ','))
			digits.push_back(std::stod(s));
		x = digits[0]; y = digits[1]; z = digits[2];

		K_Engine::Vector3* vector = new K_Engine::Vector3(x, y, z);

		return vector;
	}
}