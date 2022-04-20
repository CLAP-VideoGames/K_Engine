#pragma once
#ifndef K_Map_H
#define K_Map_H

#include <unordered_map>
#include <stdexcept>
#include <string>
//#include <utils_prj/Vector3.h>


namespace K_Engine {
	struct Vector3;
	/// <summary>
	/// The purpose of this class is to store the information from the .lua documents
	/// and give it to the components so they can get initialized without creating
	/// any not desireable dependencies
	/// </summary>
	class __declspec(dllexport) K_Map
	{

	public:
		K_Map();
		~K_Map();

		void addPair(std::string key, std::string value);

		Vector3* valueToVector3(std::string key);

		bool valueToBool(std::string key);

		double valueToNumber(std::string key);

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