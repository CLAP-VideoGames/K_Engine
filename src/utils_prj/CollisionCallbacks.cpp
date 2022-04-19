#include "CollisionCallbacks.h"

#include <utils_prj/checkML.h>

namespace K_Engine {
	CollisionInfo::CollisionInfo() : entity_(nullptr), collisionEnter(nullptr), collisionStay(nullptr), collisionExit(nullptr) {};

	CollisionInfo::CollisionInfo(void* entity, std::function<void(void*)> collisionEnter0,
		std::function<void(void*)> collisionStay0, std::function<void(void*)> collisionExit0)
		: entity_(entity), collisionEnter(collisionEnter0), collisionStay(collisionStay0), collisionExit(collisionExit0) {};

	CollisionInfo::~CollisionInfo() = default;;
}