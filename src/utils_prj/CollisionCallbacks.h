#pragma once
#ifndef COLLISIONCALLBACKS_H
#define COLLISIONCALLBACKS_H

#include <functional>

namespace K_Engine {
	struct  __declspec(dllexport) CollisionInfo {
		CollisionInfo();
		CollisionInfo(void* entity, std::function<void(void*)> collisionEnter0 = nullptr, std::function<void(void*)> collisionStay0 = nullptr,
			std::function<void(void*)> collisionExit0 = nullptr);
		~CollisionInfo();

		void* entity_;
		std::function<void(void*)> collisionEnter, collisionStay, collisionExit;
	};
}
#endif // COLLISIONCALLBACKS_H