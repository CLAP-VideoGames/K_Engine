#pragma once
#ifndef _COLLISIONLAYERS_H_
#define _COLLISIONLAYERS_H_

#include <string>
#include <unordered_map>

namespace K_Engine {
	/// <summary>
	/// Manager for collision layers
	/// </summary>
	class  __declspec(dllexport) CollisionLayers
	{
	public:
		CollisionLayers();
		~CollisionLayers();
		/// <summary>
		/// Add a new layer to the set. If already exists, it's not inserted
		/// </summary>
		/// <param name="name">Key name</param>
		/// <returns>if it has been inserted</returns>
		bool addLayer(std::string name);

		/// <summary>
		/// Returns the value given by its index position
		/// It determines the collision layer in powers of two
		/// </summary>
		/// <param name="name">Key name</param>
		/// <returns>integer multiple of 2</returns>
		int getLayer(std::string name) const;

	private:
		//last index free
		int lastPos_;
		std::unordered_map<std::string, int> layers;
	};
}
#endif _COLLISIONLAYERS_H_