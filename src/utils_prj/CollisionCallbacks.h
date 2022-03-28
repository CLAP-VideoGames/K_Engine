#pragma once
#ifndef COLLISIONCALLBACKS_H
#define COLLISIONCALLBACKS_H

#include <functional>

namespace K_Engine {
	struct CollisionInfo {
		void* entity_;
		std::function<void(void*)> collisionEnter;
		std::function<void(void*)> collisionStay;
		std::function<void(void*)> collisionExit;
		CollisionInfo() : entity_(nullptr), collisionEnter(nullptr), collisionStay(nullptr), collisionExit(nullptr) {};
		CollisionInfo(void* entity, std::function<void(void*)> collisionEnter0 = nullptr, std::function<void(void*)> collisionStay0 = nullptr, std::function<void(void*)> collisionExit0 = nullptr)
			: entity_(entity), collisionEnter(collisionEnter0), collisionStay(collisionStay0), collisionExit(collisionExit0) {};
	};
}


#endif // COLLISIONCALLBACKS_H