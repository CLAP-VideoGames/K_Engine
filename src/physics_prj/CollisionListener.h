#pragma once
#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

class btManifoldPoint;

/// <summary>
/// It doesnt work
/// </summary>
namespace K_Engine {
	class  __declspec(dllexport) CollisionListener {
	public:
		CollisionListener(void(*p_)(void*, void* other, const btManifoldPoint& mnf), void* listener) : p(p_), obj(listener) {};
		~CollisionListener() {};
		void(*p)(void*, void* other, const btManifoldPoint& mnf);
		void* obj;
	};
}
#endif COLLISIONMANAGER_H_