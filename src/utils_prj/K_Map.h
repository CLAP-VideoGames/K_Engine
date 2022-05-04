#pragma once
#ifndef K_Map_H
#define K_Map_H

#include <unordered_map>
#include <stdexcept>
#include <string>
#include <functional>
#include <vector>

#include <script_prj/ScriptManager.h>
#include <utils_prj/Vector3.h>

namespace K_Engine {
	struct Vector3;
	/// <summary>
	/// The purpose of this class is to store the information from the .lua documents
	/// and give it to the components so they can get initialized without creating
	/// any not desireable dependencies
	/// </summary>
	class ScriptManager;
	class __declspec(dllexport) K_Map
	{
	public:
		K_Map();
		~K_Map();

		void addPair(std::string key, std::string value);

		Vector3* valueToVector3(std::string key);
		bool valueToBool(std::string key);
		double valueToNumber(std::string key);
		std::string value(std::string key);
		std::function<void(std::string)> valueToCallback(std::string value); /// Devuelve la función de lua con dicho nombre

		template<typename T>
		std::vector<T> valueToVector(std::string key) {
			auto iterator = information.find(key);
			std::string elements = iterator->second;

			std::istringstream f(elements);
			std::string s;
			std::vector<T> values;

			while (getline(f, s, ','))
				values.push_back(T(s));

			return vector;
		}

		//template<typename ...Ts>
		std::function<void(std::string, float)> valueToFunction(std::string keyValue, float f) {
			std::function<void(std::string, float)> func = [=](std::string keyValue, float f) {
				ScriptManager::GetInstance()->callLuaFunction(keyValue, f);
			};

			return func;
		};
		
		bool hasValue(std::string key);

	private:
		/// <summary>
		/// This map is supposed to contain things like "Position, {1,0,1}""
		/// So fe: Transform can ask for its position and tell to this class
		///  position K_Map.valueToVector3(position);
		/// </summary>
		std::unordered_map<std::string, std::string> information;
	};
}
#endif