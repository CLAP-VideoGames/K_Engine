#ifndef _DEBUG_DRAWER_BULLET_H
#define _DEBUG_DRAWER_BULLET_H

#include "OgreFrameListener.h"
#include "OgreVector.h"
#include "OgreColourValue.h"

#include "btBulletCollisionCommon.h"

namespace K_Engine {
	class OgreDebugDrawer : public btIDebugDraw, public Ogre::FrameListener {
	public:
		OgreDebugDrawer(Ogre::SceneManager* scm);
		~OgreDebugDrawer();
		virtual void     drawLine(const btVector3& from_, const btVector3& to_, const btVector3& color_);
		virtual void     drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color_, btScalar);
		virtual void     drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color_);
		virtual void     reportErrorWarning(const char* warningString);
		virtual void     draw3dText(const btVector3& location, const char* textString);
		virtual void     setDebugMode(int debugMode);
		virtual int      getDebugMode() const;

		void setUpModes();
	protected:
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);
	private:
		struct ContactPoint {
			Ogre::Vector3 from_;
			Ogre::Vector3 to_;
			Ogre::ColourValue   color_;
			size_t        dieTime_;
		};
		DebugDrawModes               mDebugModes_;
		Ogre::ManualObject* mLines_;
		Ogre::ManualObject* mTriangles_;
		std::vector< ContactPoint >* mContactPoints_;
		std::vector< ContactPoint >  mContactPoints1_;
		std::vector< ContactPoint >  mContactPoints2_;
	};
}


#endif _DEBUG_DRAWER_BULLET_H