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
#include <render_prj/RenderManager.h>
#include<sound_prj/AudioManager.h>
#include <scene_prj/SceneManager.h>
#include <log_prj/LogManager.h>

#include <ecs_prj/EntityManager.h>
#include <ecs_prj/Entity.h>

#include <ecs_prj/ComponentManager.h>

#include <physics_prj/PhysicsManager.h>

#include <components_prj/Transform.h>
#include <components_prj/RigidBody.h>
#include <components_prj/MeshRenderer.h>
#include <components_prj/Animator.h>
#include <components_prj/AudioSource.h>

#include <log_prj/LogManager.h>

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

	bool ScriptManager::Init()
	{
		try {
			instance.reset(new ScriptManager());

			//New state for Lua
			instance.get()->luaState = luaL_newstate();
			luaL_openlibs(instance.get()->luaState); // load default Lua libs

			//Registro de las funciones
			if (instance.get()->luaState) 
				instance.get()->registerClassesandFunctions(instance.get()->luaState);
			else throw exception("ERROR: LUA wasn't compile correctly");
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Script manager shutdown success");
	}

	bool ScriptManager::Shutdown()
	{
		try {
			instance.get()->classes_.clear();
			if (instance.get()->luaState)
				lua_close(instance.get()->luaState);

			instance.reset(nullptr);
		}
		catch (const std::exception& e) {
			return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::FATAL, e.what());
		}

		return K_Engine::LogManager::GetInstance()->addLog(K_Engine::LogType::INFO, "Script manager shutdown success");
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
		//AudioManager
		getGlobalNamespace(luaState).beginClass<AudioManager>("AudioManager")
			.addStaticFunction("getAudioMan", &AudioManager::GetInstance)
			.addFunction("setMasterVolume", &AudioManager::setMasterVolume)
			.addFunction("setSFXVolume", &AudioManager::setSFXVolume)
			.addFunction("setMusicVolume", &AudioManager::setMusicVolume)
			.addFunction("getMasterVolume", &AudioManager::getMasterVolume)
			.addFunction("getSFXVolume", &AudioManager::getSFXVolume)
			.addFunction("getMusicVolume", &AudioManager::getMusicVolume)
			.endClass();
		//RenderManager
		getGlobalNamespace(luaState).beginClass<RenderManager>("RenderManager")
			.addStaticFunction("getRenderMan", &RenderManager::GetInstance)
			.addFunction("fullScreen", &RenderManager::setFullScreen)
			.addFunction("exitGame", &RenderManager::exitWindow)
			.endClass();
		//SceneManager
		getGlobalNamespace(luaState).beginClass<SceneManager>("SceneManager")
			.addStaticFunction("getSceneMan", &SceneManager::GetInstance)
			.addFunction("changeScene", &SceneManager::pushSceneStr)
			.addFunction("popScene", &SceneManager::popSceneStr)
			.endClass();
		//ECS
		getGlobalNamespace(luaState).beginClass<EntityManager>("EntityManager")
			.addFunction("addEntity", &EntityManager::addEntity)
			.endClass();
		//LogManager
		getGlobalNamespace(luaState).beginClass<LogManager>("LogManager")
			.addStaticFunction("getLogMan", &LogManager::GetInstance)
			.addFunction("printLog", &LogManager::printLogLua)
			.endClass();
		//LUA
		getGlobalNamespace(luaState).beginClass<ScriptManager>("ScriptManager")
			.addStaticFunction("getScriptMan", &ScriptManager::GetInstance)
			.endClass();
	}

	bool ScriptManager::reloadLuaScript(const std::string& luafile)
	{
		std::string file = SCRIPTS_FILE_PATH + luafile + ".lua";
		return checkLua(luaState, luaL_dofile(luaState, file.c_str()));
	}

	void ScriptManager::loadLuaScene(std::string sceneFile, EntityManager* entMan) {
		if (!reloadLuaScript(sceneFile))
			throw std::string("the scene" + sceneFile + "is not valid\n.");

		std::vector<string> entities;
		//So we can call awake once they all are initialized
		std::vector<Component*> luaComponents;

		//lista de entidades
		luabridge::LuaRef ent = getTable(sceneFile + "_" + "entities");
		int numEntities = ent.length();
		for (size_t i = 1; i <= numEntities; i++)
			entities.push_back(ent[i].cast<string>());

		luabridge::LuaRef prefabs = getTable(sceneFile + "_" + "prefabs"); //esto es donjde los prefabs de verga

		for (size_t i = 0; i < numEntities; i++) {
			Entity* e = entMan->addEntity();
			//
			std::stringstream e_name_full(entities[i]);
			std::string word;
			e_name_full >> word;
			std::string e_name = word;
			e_name_full >> word;
			float e_x = stof(word) / 100;
			e_name_full >> word;
			float e_y = stof(word) / 100;
			e_name_full >> word;
			float e_z = stof(word) / 100;
			//
			luabridge::LuaRef entity = getMetatable(prefabs, e_name);

			lua_pushnil(entity);  /* first key */
			int j = 0;
			//iterates over all components 
			while (lua_next(entity, j) != 0) {
				const char* key = lua_tostring(entity, -2);
				const char* value = lua_tostring(entity, -1);
				std::string key_ = key;
				std::string value_ = "";
				if (value != NULL)value_ = value;

				if (key_ == "Enabled") {
					if (value_ == "false")
						e->setActive(false);
				}
				else {

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
						//printf("%s : %s\n", key_, value_);
						lua_pop(comp, 1);
					}

					c->setEntity(e);
					c->init(&information);
				}

				lua_pop(entity, 1);
			}

			if (e->hasComponent<Transform>())e->getComponent<Transform>()->setPosition(e_x, e_y, e_z);

			printf("\x1b[32m Entity %s loaded succesfully.\n \x1b[0m", entities[i].c_str());
		}
	}

	void ScriptManager::registerCFunctionToLua(std::string name, lua_CFunction(*func)(lua_State* L))
	{
		lua_register(luaState, name.c_str(), func(luaState));
	}


	luabridge::LuaRef ScriptManager::getLuaFunction(std::string funcName)
	{
		return getGlobal(luaState, funcName.c_str());
	}

	void ScriptManager::callLuaFunction(std::string funcName, float value)
	{
		LuaRef f = getLuaFunction(funcName);
		f(value);
	}

	void ScriptManager::callLuaCallback(std::string funcName)
	{
		LuaRef f = getLuaFunction(funcName);
		f();
	}

	luabridge::LuaRef ScriptManager::getTable(const std::string& c_name)
	{
		try {
			luabridge::LuaRef table = getGlobal(luaState, c_name.c_str());
			return table;
		}
		catch (std::exception e) {
			cout << "Can't get lua table, make sure table is accessible or exist";
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
			cout << "Can't get lua metatable, make sure metatable is accessible or exist";
			return NULL;
		}
	}

	template<class T>
	T ScriptManager::getParameter(luabridge::LuaRef table, const std::string& parameterName)
	{
		try {
			return table[parameterName].cast<T>();
		}
		catch (std::exception e) {
			cout << "Can't read parameter, make sure table is properly read and parameter name is correct";
			return NULL;
		}
	}

	template<typename T>
	void ScriptManager::publishCNamespaceFunctionToLua(std::string classTypename, std::string name, lua_CFunction(*func)(lua_State* L))
	{
		getGlobalNamespace(luaState).beginClass<T>(classTypename)
			.addFunction(name, &T::func(name))
			.endClass();
	}
}