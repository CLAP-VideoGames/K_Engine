#include <string>
#include <unordered_map>

class CollisionLayers
{
public:
	CollisionLayers();
	~CollisionLayers();
	bool addLayer(std::string name);
	int getLayer(std::string name) const;
	 
private:
	int lastPos_;
	std::unordered_map<std::string, int> layers;
};