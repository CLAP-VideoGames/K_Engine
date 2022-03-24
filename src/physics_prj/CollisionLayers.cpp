#include "CollisionLayers.h"
#include <string>
#include <unordered_map>

#define BIT(x) (1<<(x))

CollisionLayers::CollisionLayers() {
	lastPos_ = 1;
}

CollisionLayers::~CollisionLayers() {

}

bool CollisionLayers::addLayer(std::string name){
	if (layers.find(name) != layers.end())
		return false;
	layers.insert({ name, BIT(lastPos_++) });
	return true;
}

int CollisionLayers::getLayer(std::string name) const {
	if (layers.find(name) == layers.end())
		return -1;
	auto layer = layers.find(name);
	return layer->second;
}
