#include "CustomBtOgre.h"

using namespace Ogre;

namespace BtOgre {

	typedef std::pair<unsigned short, Vector3Array*> BoneKeyIndex;

	btSphereShape* createSphereCollider(const Ogre::MovableObject* mo)
	{
		OgreAssert(mo->getParentSceneNode(), "MovableObject must be attached");

		auto shape = new btSphereShape(mo->getBoundingRadius());
		shape->setLocalScaling(Converter::toBullet(mo->getParentSceneNode()->getScale()));

		return shape;
	}
	btBoxShape* createBoxCollider(const Ogre::MovableObject* mo)
	{
		OgreAssert(mo->getParentSceneNode(), "MovableObject must be attached");

		auto shape = new btBoxShape(Converter::toBullet(mo->getBoundingBox().getHalfSize()));
		shape->setLocalScaling(Converter::toBullet(mo->getParentSceneNode()->getScale()));

		return shape;
	}

	static void onTick(btDynamicsWorld* world, btScalar timeStep)
	{
		int numManifolds = world->getDispatcher()->getNumManifolds();
		auto manifolds = world->getDispatcher()->getInternalManifoldPointer();
		for (int i = 0; i < numManifolds; i++) {
			btPersistentManifold* manifold = manifolds[i];

			for (int j = 0; j < manifold->getNumContacts(); j++)
			{
				const btManifoldPoint& mp = manifold->getContactPoint(j);
				auto body0 = static_cast<CollisionListener*>(manifold->getBody0()->getUserPointer());
				auto body1 = static_cast<CollisionListener*>(manifold->getBody1()->getUserPointer());
				if (body0)
					body0->p(body0->obj, body1->obj, mp);
				if (body1)
					body1->p(body1->obj, body0->obj, mp);
			}
		}
	}

	/// <summary>
	/// Creates a Bullet Physic world with all it's necessary elements
	/// </summary>
	/// <param name="gravity"> Desired world gravity </param>
	DynamicsWorld::DynamicsWorld(const Ogre::Vector3& gravity)
	{
		//Bullet initialisation.
		mCollisionConfig.reset(new btDefaultCollisionConfiguration());
		mDispatcher.reset(new btCollisionDispatcher(mCollisionConfig.get()));
		mSolver.reset(new btSequentialImpulseConstraintSolver());
		mBroadphase.reset(new btDbvtBroadphase());

		mBtWorld = new btDiscreteDynamicsWorld(mDispatcher.get(), mBroadphase.get(), mSolver.get(),
			mCollisionConfig.get());
		mBtWorld->setGravity(Converter::toBullet(gravity));
		mBtWorld->setInternalTickCallback(onTick);
	}

	/// <summary>
	/// Adds a Bullet Rigidbody to the world from a Ogre Entity
	/// </summary>
	/// <param name="mass"> Mass of the object </param>
	/// <param name="ent"> Ogre Entity from which to create the Physic object </param>
	/// <param name="ct"> Collider Type: BOX or SPHERE </param>
	/// <param name="p"> btNearCallback used to detect collisions </param>
	/// <param name="listener"> Bullet listener </param>
	/// <returns></returns>
	btRigidBody* DynamicsWorld::addRigidBody(float mass, const Ogre::Entity* ent, ColliderType ct, void(*p)(void*, void* other, const btManifoldPoint& mnf), void* listener)
	{
		auto node = ent->getParentSceneNode();
		RigidBodyState* state = new RigidBodyState(node);

		btCollisionShape* cs = NULL;
		switch (ct)
		{
		case BOX:
			cs = createBoxCollider(ent);
			break;
		case SPHERE:
			cs = createSphereCollider(ent);
			break;
		}

		btVector3 inertia(0, 0, 0);
		if (mass != 0) // mass = 0 -> static
			cs->calculateLocalInertia(mass, inertia);

		auto rb = new btRigidBody(mass, state, cs, inertia);
		mBtWorld->addRigidBody(rb);
		rb->setUserPointer(new CollisionListener(p, listener));

		// transfer ownership to node
		auto bodyWrapper = std::make_shared<RigidBody>(rb, mBtWorld);
		node->getUserObjectBindings().setUserAny("BtRigidBody", bodyWrapper);

		return rb;
	}

	DynamicsWorld::~DynamicsWorld()
	{
		delete mBtWorld;
	}

	/// <summary>
	/// Used to be able to render different type of objects
	/// </summary>
	/// <param name="vertex_data"> The vertex data of the object to render </param>
	void VertexIndexToShape::addStaticVertexData(const VertexData* vertex_data)
	{
		if (!vertex_data)
			return;

		const VertexData* data = vertex_data;

		const unsigned int prev_size = mVertexCount;
		mVertexCount += (unsigned int)data->vertexCount;

		Ogre::Vector3* tmp_vert = new Ogre::Vector3[mVertexCount];
		if (mVertexBuffer)
		{
			memcpy(tmp_vert, mVertexBuffer, sizeof(Vector3) * prev_size);
			delete[] mVertexBuffer;
		}
		mVertexBuffer = tmp_vert;

		// Get the positional buffer element
		{
			const Ogre::VertexElement* posElem = data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			Ogre::HardwareVertexBufferSharedPtr vbuf = data->vertexBufferBinding->getBuffer(posElem->getSource());
			const unsigned int vSize = (unsigned int)vbuf->getVertexSize();

			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			float* pReal;
			Ogre::Vector3* curVertices = &mVertexBuffer[prev_size];
			const unsigned int vertexCount = (unsigned int)data->vertexCount;
			for (unsigned int j = 0; j < vertexCount; ++j)
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);
				vertex += vSize;

				curVertices->x = (*pReal++);
				curVertices->y = (*pReal++);
				curVertices->z = (*pReal++);

				*curVertices = mTransform * (*curVertices);

				curVertices++;
			}
			vbuf->unlock();
		}
	}

	/// <summary>
	/// Used to render animated Ogre objects. Creates bones and all kind of things needed to later animate de object
	/// </summary>
	/// <param name="vertex_data"> Information of the object to render </param>
	/// <param name="blend_data"> Additional data needed, for example for bones </param>
	/// <param name="indexMap"> Indexed map with the bone information </param>
	void VertexIndexToShape::addAnimatedVertexData(const Ogre::VertexData* vertex_data,
		const Ogre::VertexData* blend_data,
		const Ogre::Mesh::IndexMap* indexMap)
	{
		// Get the bone index element
		assert(vertex_data);

		const VertexData* data = blend_data;
		const unsigned int prev_size = mVertexCount;
		mVertexCount += (unsigned int)data->vertexCount;
		Ogre::Vector3* tmp_vert = new Ogre::Vector3[mVertexCount];
		if (mVertexBuffer)
		{
			memcpy(tmp_vert, mVertexBuffer, sizeof(Vector3) * prev_size);
			delete[] mVertexBuffer;
		}
		mVertexBuffer = tmp_vert;

		// Get the positional buffer element
		{
			const Ogre::VertexElement* posElem = data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			assert(posElem);
			Ogre::HardwareVertexBufferSharedPtr vbuf = data->vertexBufferBinding->getBuffer(posElem->getSource());
			const unsigned int vSize = (unsigned int)vbuf->getVertexSize();

			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			float* pReal;
			Ogre::Vector3* curVertices = &mVertexBuffer[prev_size];
			const unsigned int vertexCount = (unsigned int)data->vertexCount;
			for (unsigned int j = 0; j < vertexCount; ++j)
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);
				vertex += vSize;

				curVertices->x = (*pReal++);
				curVertices->y = (*pReal++);
				curVertices->z = (*pReal++);

				*curVertices = mTransform * (*curVertices);

				curVertices++;
			}
			vbuf->unlock();
		}
		{
			const Ogre::VertexElement* bneElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_BLEND_INDICES);
			assert(bneElem);

			Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(bneElem->getSource());
			const unsigned int vSize = (unsigned int)vbuf->getVertexSize();
			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

			unsigned char* pBone;

			if (!mBoneIndex)
				mBoneIndex = new BoneIndex();
			BoneIndex::iterator i;

			Ogre::Vector3* curVertices = &mVertexBuffer[prev_size];

			const unsigned int vertexCount = (unsigned int)vertex_data->vertexCount;
			for (unsigned int j = 0; j < vertexCount; ++j)
			{
				bneElem->baseVertexPointerToElement(vertex, &pBone);
				vertex += vSize;

				const unsigned char currBone = (indexMap) ? (*indexMap)[*pBone] : *pBone;
				i = mBoneIndex->find(currBone);
				Vector3Array* l = 0;
				if (i == mBoneIndex->end())
				{
					l = new Vector3Array;
					mBoneIndex->insert(BoneKeyIndex(currBone, l));
				}
				else
				{
					l = i->second;
				}

				l->push_back(*curVertices);

				curVertices++;
			}
			vbuf->unlock();
		}
	}

	
	void VertexIndexToShape::addIndexData(IndexData* data, const unsigned int offset)
	{
		const unsigned int prev_size = mIndexCount;
		mIndexCount += (unsigned int)data->indexCount;

		unsigned int* tmp_ind = new unsigned int[mIndexCount];
		if (mIndexBuffer)
		{
			memcpy(tmp_ind, mIndexBuffer, sizeof(unsigned int) * prev_size);
			delete[] mIndexBuffer;
		}
		mIndexBuffer = tmp_ind;

		const unsigned int numTris = (unsigned int)data->indexCount / 3;
		HardwareIndexBufferSharedPtr ibuf = data->indexBuffer;
		const bool use32bitindexes = (ibuf->getType() == HardwareIndexBuffer::IT_32BIT);
		unsigned int index_offset = prev_size;

		if (use32bitindexes)
		{
			const unsigned int* pInt = static_cast<unsigned int*>(ibuf->lock(HardwareBuffer::HBL_READ_ONLY));
			for (unsigned int k = 0; k < numTris; ++k)
			{
				mIndexBuffer[index_offset++] = offset + *pInt++;
				mIndexBuffer[index_offset++] = offset + *pInt++;
				mIndexBuffer[index_offset++] = offset + *pInt++;
			}
			ibuf->unlock();
		}
		else
		{
			const unsigned short* pShort = static_cast<unsigned short*>(ibuf->lock(HardwareBuffer::HBL_READ_ONLY));
			for (unsigned int k = 0; k < numTris; ++k)
			{
				mIndexBuffer[index_offset++] = offset + static_cast<unsigned int> (*pShort++);
				mIndexBuffer[index_offset++] = offset + static_cast<unsigned int> (*pShort++);
				mIndexBuffer[index_offset++] = offset + static_cast<unsigned int> (*pShort++);
			}
			ibuf->unlock();
		}

	}

	/// <summary>
	/// Gets the radius of the object
	/// </summary>
	/// <returns> Radius </returns>
	Real VertexIndexToShape::getRadius()
	{
		if (mBoundRadius == (-1))
		{
			getSize();
			mBoundRadius = (std::max(mBounds.x, std::max(mBounds.y, mBounds.z)) * 0.5);
		}
		return mBoundRadius;
	}

	/// <summary>
	/// Gets the size of the object
	/// </summary>
	/// <returns> Object size </returns>
	Vector3 VertexIndexToShape::getSize()
	{
		const unsigned int vCount = getVertexCount();
		if (mBounds == Ogre::Vector3(-1, -1, -1) && vCount > 0)
		{

			const Ogre::Vector3* const v = getVertices();

			Ogre::Vector3 vmin(v[0]);
			Ogre::Vector3 vmax(v[0]);

			for (unsigned int j = 1; j < vCount; j++)
			{
				vmin.x = std::min(vmin.x, v[j].x);
				vmin.y = std::min(vmin.y, v[j].y);
				vmin.z = std::min(vmin.z, v[j].z);

				vmax.x = std::max(vmax.x, v[j].x);
				vmax.y = std::max(vmax.y, v[j].y);
				vmax.z = std::max(vmax.z, v[j].z);
			}

			mBounds.x = vmax.x - vmin.x;
			mBounds.y = vmax.y - vmin.y;
			mBounds.z = vmax.z - vmin.z;
		}

		return mBounds;
	}

	/// <summary>
	/// Vertices from the object
	/// </summary>
	/// <returns> Vertices</returns>
	const Ogre::Vector3* VertexIndexToShape::getVertices()
	{
		return mVertexBuffer;
	}

	unsigned int VertexIndexToShape::getVertexCount()
	{
		return mVertexCount;
	}

	const unsigned int* VertexIndexToShape::getIndices()
	{
		return mIndexBuffer;
	}

	unsigned int VertexIndexToShape::getIndexCount()
	{
		return mIndexCount;
	}

	/// <summary>
	/// Creates a Physic sphere
	/// </summary>
	/// <returns></returns>
	btSphereShape* VertexIndexToShape::createSphere()
	{
		const Ogre::Real rad = getRadius();
		assert((rad > 0.0) &&
			("Sphere radius must be greater than zero"));
		btSphereShape* shape = new btSphereShape(rad);

		shape->setLocalScaling(Converter::toBullet(mScale));

		return shape;
	}

	/// <summary>
	/// Creates a Physic box
	/// </summary>
	/// <returns></returns>
	btBoxShape* VertexIndexToShape::createBox()
	{
		const Ogre::Vector3 sz = getSize();

		assert((sz.x > 0.0) && (sz.y > 0.0) && (sz.z > 0.0) &&
			("Size of box must be greater than zero on all axes"));

		btBoxShape* shape = new btBoxShape(Converter::toBullet(sz * 0.5));

		shape->setLocalScaling(Converter::toBullet(mScale));

		return shape;
	}

	VertexIndexToShape::~VertexIndexToShape()
	{
		delete[] mVertexBuffer;
		delete[] mIndexBuffer;

		if (mBoneIndex)
		{
			for (BoneIndex::iterator i = mBoneIndex->begin();
				i != mBoneIndex->end();
				++i)
			{
				delete i->second;
			}
			delete mBoneIndex;
		}
	}

	VertexIndexToShape::VertexIndexToShape(const Matrix4& transform) :
		mVertexBuffer(0),
		mIndexBuffer(0),
		mVertexCount(0),
		mIndexCount(0),
		mBounds(Vector3(-1, -1, -1)),
		mBoundRadius(-1),
		mBoneIndex(0),
		mTransform(transform),
		mScale(1){}

	StaticMeshToShapeConverter::StaticMeshToShapeConverter() :
		VertexIndexToShape(),
		mEntity(0),
		mNode(0){}

	StaticMeshToShapeConverter::StaticMeshToShapeConverter(const Entity* entity, const Matrix4& transform) :
		VertexIndexToShape(transform),
		mEntity(0),
		mNode(0)
	{
		addEntity(entity, transform);
	}

	StaticMeshToShapeConverter::StaticMeshToShapeConverter(Renderable* rend, const Matrix4& transform) :
		VertexIndexToShape(transform),
		mEntity(0),
		mNode(0)
	{
		RenderOperation op;
		rend->getRenderOperation(op);
		VertexIndexToShape::addStaticVertexData(op.vertexData);
		if (op.useIndexes)
			VertexIndexToShape::addIndexData(op.indexData);

	}

	void StaticMeshToShapeConverter::addEntity(const Entity* entity, const Matrix4& transform)
	{
		// Each entity added need to reset size and radius
		// next time getRadius and getSize are asked, they're computed.
		mBounds = Ogre::Vector3(-1, -1, -1);
		mBoundRadius = -1;

		mEntity = entity;
		mNode = (SceneNode*)(mEntity->getParentNode());
		mTransform = transform;
		mScale = mNode ? mNode->getScale() : Ogre::Vector3(1, 1, 1);

		if (mEntity->getMesh()->sharedVertexData)
		{
			VertexIndexToShape::addStaticVertexData(mEntity->getMesh()->sharedVertexData);
		}

		for (unsigned int i = 0; i < mEntity->getNumSubEntities(); ++i)
		{
			SubMesh* sub_mesh = mEntity->getSubEntity(i)->getSubMesh();

			if (!sub_mesh->useSharedVertices)
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData, mVertexCount);
				VertexIndexToShape::addStaticVertexData(sub_mesh->vertexData);
			}
			else
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData);
			}

		}
	}

	void StaticMeshToShapeConverter::addMesh(const MeshPtr& mesh, const Matrix4& transform)
	{
		// Each entity added need to reset size and radius
		// next time getRadius and getSize are asked, they're computed.
		mBounds = Ogre::Vector3(-1, -1, -1);
		mBoundRadius = -1;

		//_entity = entity;
		//_node = (SceneNode*)(_entity->getParentNode());
		mTransform = transform;

		if (mesh->hasSkeleton())
			Ogre::LogManager::getSingleton().logMessage("MeshToShapeConverter::addMesh : Mesh " + mesh->getName() + " as skeleton but added to trimesh non animated");

		if (mesh->sharedVertexData)
		{
			VertexIndexToShape::addStaticVertexData(mesh->sharedVertexData);
		}

		for (unsigned int i = 0; i < mesh->getNumSubMeshes(); ++i)
		{
			SubMesh* sub_mesh = mesh->getSubMesh(i);

			if (!sub_mesh->useSharedVertices)
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData, mVertexCount);
				VertexIndexToShape::addStaticVertexData(sub_mesh->vertexData);
			}
			else
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData);
			}

		}
	}

	AnimatedMeshToShapeConverter::AnimatedMeshToShapeConverter(Entity* entity, const Matrix4& transform) :
		VertexIndexToShape(transform),
		mEntity(0),
		mNode(0),
		mTransformedVerticesTemp(0),
		mTransformedVerticesTempSize(0)
	{
		addEntity(entity, transform);
	}

	AnimatedMeshToShapeConverter::AnimatedMeshToShapeConverter() :
		VertexIndexToShape(),
		mEntity(0),
		mNode(0),
		mTransformedVerticesTemp(0),
		mTransformedVerticesTempSize(0){}

	AnimatedMeshToShapeConverter::~AnimatedMeshToShapeConverter()
	{
		delete[] mTransformedVerticesTemp;
	}

	void AnimatedMeshToShapeConverter::addEntity(Entity* entity, const Matrix4& transform)
	{
		// Each entity added need to reset size and radius
		// next time getRadius and getSize are asked, they're computed.
		mBounds = Ogre::Vector3(-1, -1, -1);
		mBoundRadius = -1;

		mEntity = entity;
		mNode = (SceneNode*)(mEntity->getParentNode());
		mTransform = transform;

		assert(entity->getMesh()->hasSkeleton());

		mEntity->addSoftwareAnimationRequest(false);
		mEntity->_updateAnimation();

		if (mEntity->getMesh()->sharedVertexData)
		{
			VertexIndexToShape::addAnimatedVertexData(mEntity->getMesh()->sharedVertexData,
				mEntity->_getSkelAnimVertexData(),
				&mEntity->getMesh()->sharedBlendIndexToBoneIndexMap);
		}

		for (unsigned int i = 0; i < mEntity->getNumSubEntities(); ++i)
		{
			SubMesh* sub_mesh = mEntity->getSubEntity(i)->getSubMesh();

			if (!sub_mesh->useSharedVertices)
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData, mVertexCount);

				VertexIndexToShape::addAnimatedVertexData(sub_mesh->vertexData,
					mEntity->getSubEntity(i)->_getSkelAnimVertexData(),
					&sub_mesh->blendIndexToBoneIndexMap);
			}
			else
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData);
			}

		}

		mEntity->removeSoftwareAnimationRequest(false);
	}

	void AnimatedMeshToShapeConverter::addMesh(const MeshPtr& mesh, const Matrix4& transform)
	{
		// Each entity added need to reset size and radius
		// next time getRadius and getSize are asked, they're computed.
		mBounds = Ogre::Vector3(-1, -1, -1);
		mBoundRadius = -1;

		//_entity = entity;
		//_node = (SceneNode*)(_entity->getParentNode());
		mTransform = transform;

		assert(mesh->hasSkeleton());

		if (mesh->sharedVertexData)
		{
			VertexIndexToShape::addAnimatedVertexData(mesh->sharedVertexData,
				0,
				&mesh->sharedBlendIndexToBoneIndexMap);
		}

		for (unsigned int i = 0; i < mesh->getNumSubMeshes(); ++i)
		{
			SubMesh* sub_mesh = mesh->getSubMesh(i);

			if (!sub_mesh->useSharedVertices)
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData, mVertexCount);

				VertexIndexToShape::addAnimatedVertexData(sub_mesh->vertexData,
					0,
					&sub_mesh->blendIndexToBoneIndexMap);
			}
			else
			{
				VertexIndexToShape::addIndexData(sub_mesh->indexData);
			}

		}
	}

	bool AnimatedMeshToShapeConverter::getBoneVertices(unsigned char bone,
		unsigned int& vertex_count,
		Ogre::Vector3*& vertices,
		const Vector3& bonePosition)
	{
		BoneIndex::iterator i = mBoneIndex->find(bone);

		if (i == mBoneIndex->end())
			return false;

		if (i->second->empty())
			return false;

		vertex_count = (unsigned int)i->second->size() + 1;
		if (vertex_count > mTransformedVerticesTempSize)
		{
			if (mTransformedVerticesTemp)
				delete[] mTransformedVerticesTemp;

			mTransformedVerticesTemp = new Ogre::Vector3[vertex_count];

		}

		vertices = mTransformedVerticesTemp;
		vertices[0] = bonePosition;
		//mEntity->_getParentNodeFullTransform() *
		//	mEntity->getSkeleton()->getBone(bone)->_getDerivedPosition();

		//mEntity->getSkeleton()->getBone(bone)->_getDerivedOrientation()
		unsigned int currBoneVertex = 1;
		Vector3Array::iterator j = i->second->begin();
		while (j != i->second->end())
		{
			vertices[currBoneVertex] = (*j);
			++j;
			++currBoneVertex;
		}
		return true;
	}

	btBoxShape* AnimatedMeshToShapeConverter::createAlignedBox(unsigned char bone,
		const Vector3& bonePosition,
		const Quaternion& boneOrientation)
	{
		unsigned int vertex_count;
		Vector3* vertices;

		if (!getBoneVertices(bone, vertex_count, vertices, bonePosition))
			return 0;

		Vector3 min_vec(vertices[0]);
		Vector3 max_vec(vertices[0]);

		for (unsigned int j = 1; j < vertex_count; j++)
		{
			min_vec.x = std::min(min_vec.x, vertices[j].x);
			min_vec.y = std::min(min_vec.y, vertices[j].y);
			min_vec.z = std::min(min_vec.z, vertices[j].z);

			max_vec.x = std::max(max_vec.x, vertices[j].x);
			max_vec.y = std::max(max_vec.y, vertices[j].y);
			max_vec.z = std::max(max_vec.z, vertices[j].z);
		}
		const Ogre::Vector3 maxMinusMin(max_vec - min_vec);
		btBoxShape* box = new btBoxShape(Converter::toBullet(maxMinusMin));

		/*const Ogre::Vector3 pos
			(min_vec.x + (maxMinusMin.x * 0.5),
			min_vec.y + (maxMinusMin.y * 0.5),
			min_vec.z + (maxMinusMin.z * 0.5));*/

			//box->setPosition(pos);

		return box;
	}

	bool AnimatedMeshToShapeConverter::getOrientedBox(unsigned char bone,
		const Vector3& bonePosition,
		const Quaternion& boneOrientation,
		Vector3& box_afExtent,
		Vector3* box_akAxis,
		Vector3& box_kCenter)
	{
		unsigned int vertex_count;
		Vector3* vertices;

		if (!getBoneVertices(bone, vertex_count, vertices, bonePosition))
			return false;

		box_kCenter = Vector3::ZERO;

		{
			for (unsigned int c = 0; c < vertex_count; c++)
			{
				box_kCenter += vertices[c];
			}
			const Ogre::Real invVertexCount = 1.0 / vertex_count;
			box_kCenter *= invVertexCount;
		}
		Quaternion orient = boneOrientation;
		orient.ToAxes(box_akAxis);

		// Let C be the box center and let U0, U1, and U2 be the box axes.  Each
		// input point is of the form X = C + y0*U0 + y1*U1 + y2*U2.  The
		// following code computes min(y0), max(y0), min(y1), max(y1), min(y2),
		// and max(y2).  The box center is then adjusted to be
		//   C' = C + 0.5*(min(y0)+max(y0))*U0 + 0.5*(min(y1)+max(y1))*U1 +
		//        0.5*(min(y2)+max(y2))*U2

		Ogre::Vector3 kDiff(vertices[1] - box_kCenter);
		Ogre::Real fY0Min = kDiff.dotProduct(box_akAxis[0]), fY0Max = fY0Min;
		Ogre::Real fY1Min = kDiff.dotProduct(box_akAxis[1]), fY1Max = fY1Min;
		Ogre::Real fY2Min = kDiff.dotProduct(box_akAxis[2]), fY2Max = fY2Min;

		for (unsigned int i = 2; i < vertex_count; i++)
		{
			kDiff = vertices[i] - box_kCenter;

			const Ogre::Real fY0 = kDiff.dotProduct(box_akAxis[0]);
			if (fY0 < fY0Min)
				fY0Min = fY0;
			else if (fY0 > fY0Max)
				fY0Max = fY0;

			const Ogre::Real fY1 = kDiff.dotProduct(box_akAxis[1]);
			if (fY1 < fY1Min)
				fY1Min = fY1;
			else if (fY1 > fY1Max)
				fY1Max = fY1;

			const Ogre::Real fY2 = kDiff.dotProduct(box_akAxis[2]);
			if (fY2 < fY2Min)
				fY2Min = fY2;
			else if (fY2 > fY2Max)
				fY2Max = fY2;
		}

		box_afExtent.x = ((Real)0.5) * (fY0Max - fY0Min);
		box_afExtent.y = ((Real)0.5) * (fY1Max - fY1Min);
		box_afExtent.z = ((Real)0.5) * (fY2Max - fY2Min);

		box_kCenter += (0.5 * (fY0Max + fY0Min)) * box_akAxis[0] +
			(0.5 * (fY1Max + fY1Min)) * box_akAxis[1] +
			(0.5 * (fY2Max + fY2Min)) * box_akAxis[2];

		box_afExtent *= 2.0;

		return true;
	}

	btBoxShape* AnimatedMeshToShapeConverter::createOrientedBox(unsigned char bone,
		const Vector3& bonePosition,
		const Quaternion& boneOrientation)
	{
		Ogre::Vector3 box_akAxis[3];
		Ogre::Vector3 box_afExtent;
		Ogre::Vector3 box_afCenter;

		if (!getOrientedBox(bone, bonePosition, boneOrientation,
			box_afExtent,
			box_akAxis,
			box_afCenter))
			return 0;

		btBoxShape* geom = new btBoxShape(Converter::toBullet(box_afExtent));
		//geom->setOrientation(Quaternion(box_akAxis[0],box_akAxis[1],box_akAxis[2]));
		//geom->setPosition(box_afCenter);
		return geom;
	}

	/// <summary>
	/// Draws a line in Ogre, used to create more complex forms
	/// </summary>
	/// <param name="from"> Line origin </param>
	/// <param name="to"> Line destination </param>
	/// <param name="color"> Line color </param>
	void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		if (mLines.getSections().empty())
		{
			const char* matName = "Ogre/Debug/LinesMat";
			auto mat = Ogre::MaterialManager::getSingleton().getByName(matName, Ogre::RGN_INTERNAL);
			if (!mat)
			{
				mat = Ogre::MaterialManager::getSingleton().create(matName, Ogre::RGN_INTERNAL);
				auto p = mat->getTechnique(0)->getPass(0);
				p->setLightingEnabled(false);
				p->setVertexColourTracking(Ogre::TVC_AMBIENT);
			}
			mLines.setBufferUsage(Ogre::HBU_CPU_TO_GPU);
			mLines.begin(mat, Ogre::RenderOperation::OT_LINE_LIST);
		}
		else if (mLines.getCurrentVertexCount() == 0)
			mLines.beginUpdate(0);

		Ogre::ColourValue col(color.x(), color.x(), color.z());
		mLines.position(Converter::toOgre(from));
		mLines.colour(col);
		mLines.position(Converter::toOgre(to));
		mLines.colour(col);
	}
}