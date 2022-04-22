#include "ScriptManager.h"

#include <stdio.h>
#include <vector>
#include <iostream>

#include <lua.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <LuaBridge.h>
//Otros proyectos
#include <ecs_prj/EntityManager.h>
#include <ecs_prj/Entity.h>
#include <ecs_prj/ComponentManager.h>
#include <physics_prj/PhysicsManager.h>
#include <components_prj/Transform.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/Animator.h>
#include <components_prj/AudioSource.h>
#include <utils_prj/K_Map.h>

#include <utils_prj/checkML.h>

using namespace std;
using namespace luabridge;

namespace K_Engine {
	std::unique_ptr<ScriptManager> ScriptManager::instance = nullptr;

	ScriptManager::ScriptManager() = default;

	ScriptManager::~ScriptManager() = default;

	ScriptManager* ScriptManager::GetInstance() {
		return instance.get();
	}

	bool ScriptManager::Init(std::string name)
	{
		try {
			instance.reset(new ScriptManager());

			instance.get()->n = name;
			//New state for Lua
			instance.get()->luaState = luaL_newstate();
			luaL_openlibs(instance.get()->luaState); // load default Lua libs

			//Registro de las funciones

			if (instance.get()->luaState) {
				instance.get()->registerClassesandFunctions(instance.get()->luaState);
			}
			else throw exception("ERROR: LUA wasn't compile correctly");
		}
		catch (const std::exception&) {
			return false;
		}

		return true;
	}

	bool ScriptManager::Shutdown()
	{
		try {
			instance.get()->classes_.clear();
			if (instance.get()->luaState)
				lua_close(instance.get()->luaState);
		}
		catch (const std::exception&) {
			return false;
		}

		return true;
	}

	luabridge::LuaRef ScriptManager::getLuaClass(const std::string& c_name)
	{
		luabridge::LuaRef m = luabridge::LuaRef(luaState);//nil
		auto it = classes_.find(c_name);
		if (it != classes_.end()) {
			m = it->second;
		}
		return m;
	}

	void ScriptManager::clean()
	{
		int n = lua_gettop(instance.get()->luaState);
		lua_pop(instance.get()->luaState, n);
	}

	bool ScriptManager::checkLua(lua_State* L, int r)
	{
		if (r != LUA_OK)
		{
			string errormsg = lua_tostring(L, -1);
			cout << errormsg << endl;
			return false;
		}

		return true;
	}

	void ScriptManager::registerClassesandFunctions(lua_State* L)
	{
		//ECS
		getGlobalNamespace(luaState).beginClass<EntityManager>("EntityManager")
			.addFunction("addEntity", &EntityManager::addEntity)
			.endClass();
		/*getGlobalNamespace(luaState).beginClass<Entity>("Entity")
			.addFunction("addComponent", &Entity::addComponent<T>)
			.endClass();*/
		//LUA
		getGlobalNamespace(luaState).beginClass<ScriptManager>("ScriptManager")
			.addStaticFunction("getInstance", &ScriptManager::GetInstance)
			.addFunction("createPlayerbyAtrib", &ScriptManager::createPlayerbyAtrib)
			.addFunction("createPlayerbyObject", &ScriptManager::createPlayerbyObject)
			.endClass();
	}

	bool ScriptManager::reloadLuaScript(const std::string& luafile)
	{
		std::string file = SCRIPTS_FILE_PATH + luafile + ".lua";
		return checkLua(luaState, luaL_dofile(luaState, file.c_str()));
	}

	void ScriptManager::createPlayerbyAtrib(std::string name, float x, float y)
	{
		x_ = x; y_ = y;
		cout << "Player: " << name << "\nIn Position: " << x_ << ", "<< y_ << endl;
	}

	void ScriptManager::createPlayerbyObject(luabridge::LuaRef object)
	{
		try {
			//Casteo del objeto o tabla de lua y sus atributos
			//Rawget devuelve el objeto de nombre x
			//getmetatable devuelve la tabla de nombre x
			cout << "Player: " << object.rawget("name").cast<string>() <<
				"\nIn Position: " << object.rawget("position").getMetatable().rawget("x").cast<float>() << ", " 
				<< object.rawget("position").getMetatable().rawget("y").cast<float>() << endl;
		}
		catch (std::exception e) {
			return;
		}
	}

	void ScriptManager::loadLuaMap(std::string sceneFile, EntityManager* entMan){
		if (!reloadLuaScript(sceneFile))
			throw std::string("the scene" + sceneFile + "is not valid\n.");

		//std::vector<string> extraMembers = { "GameObjectType"};
		//dataComponents.insert(dataComponents.end(), extraMembers.begin(), extraMembers.end());

		std::vector<string> entities;
		//So we can call awake once they all are initialized
		std::vector<Component*> luaComponents;

		luabridge::LuaRef ent = getTable("entities"); /*getMetatable(table, "entities");*/
		int numEntities = ent.length();
		for (size_t i = 1; i <= numEntities; i++)
			entities.push_back(ent[i].cast<string>());

		luabridge::LuaRef scene = getTable("scene");

		for (size_t i = 0; i < numEntities; i++) {
			Entity* e = entMan->addEntity();
			luabridge::LuaRef entity = getMetatable(scene, entities[i]);

			lua_pushnil(entity);  /* first key */
			int j = 0;
			//iterates over all components 
			while (lua_next(entity, j) != 0) {
				const char* key = lua_tostring(entity, -2);
				const char* value = lua_tostring(entity, -1);
				std::string key_ = key;
				std::string value_ = "";
				if(value != NULL)value_ = value;

				if (key_ == "Enabled" && value_ == "false") {
					e->setActive(false);
				}
				else{

					//Creates the component
					Component* c = e->addComponentByName(key_);
					luaComponents.push_back(c);

					luabridge::LuaRef comp = getMetatable(entity, key);
					lua_pushnil(comp);

					K_Map information;
					int l = 0;

					while (lua_next(comp, l) != 0) {
						const char* key_ = lua_tostring(entity, -2);
						const char* value_ = lua_tostring(entity, -1);

						std::string key = key_;
						std::string value = "";

						if (value_ != NULL)value = value_;

						if (key == "isEnabled" && value == "false")
							c->setActive(false);

						//Storing the information so the component can initialize
						information.addPair(key_, value_);
						int length = comp.length();
						printf("%s : %s\n", key_, value_);
						lua_pop(comp, 1);
					}

					c->setEntity(e);
					c->init(&information);
				}

				lua_pop(entity, 1);
			}
		}
	}

	void ScriptManager::addComponentbyTable(Entity* e, const std:: string& component, luabridge::LuaRef propert)
	{
		if (component == "Transform") {
			K_Engine::Transform* t = e->addComponent<K_Engine::Transform>();
			t->setPosition(getMetatable(propert, "position")[1], getMetatable(propert, "position")[2], getMetatable(propert, "position")[3]);
			t->setRotation(getMetatable(propert, "rotation")[1], getMetatable(propert, "rotation")[2], getMetatable(propert, "rotation")[3]);
			t->setScale(getMetatable(propert, "scale")[1], getMetatable(propert, "scale")[2], getMetatable(propert, "scale")[3]);
		}
		else if (component == "MeshRenderer") {
			K_Engine::MeshRenderer* m = e->addComponent<K_Engine::MeshRenderer>();
			m->setMesh(getParameter<string>(propert, "MeshFile"));
			m->setMaterial("K_Engine/PrototypeBlue");
		}
		else if (component == "RigidBody") {
			string s = getParameter<string>(propert, "Type");
			BodyType b;
			if (s == "Static")
				b = BodyType::BT_STATIC;
			else if (s == "Dynamic")
				b = BodyType::BT_DYNAMIC;

			s = getParameter<string>(propert, "Collider");
			ColliderType c;
			if (s == "Box")
				c = ColliderType::CT_BOX;
			else if (s == "Hull")
				c = ColliderType::CT_HULL;
			else if (s == "Sphere")
				c = ColliderType::CT_SPHERE;
			else if (s == "TriMesh")
				c = ColliderType::CT_TRIMESH;

			K_Engine::RigidBody* rb = e->addComponent<K_Engine::RigidBody>(c, b, getParameter<float>(propert, "Mass"),
				 K_Engine::PhysicsManager::GetInstance()->getLayerID("Player"), K_Engine::PhysicsManager::GetInstance()->getLayerID("Platform")); //Provisional
			rb->setTrigger(getParameter<bool>(propert, "isTrigger"));
		}
	}

	luabridge::LuaRef ScriptManager::getTable(const std::string& c_name)
	{
		try {
			luabridge::LuaRef table = getGlobal(luaState, c_name.c_str());
			return table;
		}
		catch (std::exception e) {
			cout << "Can�Lt get lua table, make sure table is accessible or exist";
			return NULL;
		}
	}

	luabridge::LuaRef ScriptManager::getMetatable(luabridge::LuaRef table, const std::string& c_name)
	{
		try{
		luabridge::LuaRef meta = table[c_name];
		return meta;
	}
		catch (std::exception e) {
			cout << "Can�Lt get lua metatable, make sure metatable is accessible or exist";
			return NULL;
		}
	}

	void ScriptManager::setDataComponents(std::vector<std::string> components){
		dataComponents = components;
	}

	template<class T>
	T ScriptManager::getParameter(luabridge::LuaRef table, const std::string& parameterName)
	{
		try {
			return table[parameterName].cast<T>();
		}
		catch (std::exception e) {
			cout << "Can�Lt read parameter, make sure table is properly read and parameter name is correct";
			return NULL;
		}
	}
}