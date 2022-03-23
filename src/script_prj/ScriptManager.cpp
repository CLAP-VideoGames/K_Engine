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

using namespace std;
using namespace luabridge;

namespace K_Engine {
	std::unique_ptr<ScriptManager> ScriptManager::instance = nullptr;

	ScriptManager::ScriptManager() = default;

	ScriptManager::~ScriptManager() = default;

	ScriptManager* ScriptManager::GetInstance() {
		return instance.get();
	}

	bool ScriptManager::Init(const std::string& filename)
	{
		instance.get()->luaState = luaL_newstate();
		if (luaL_loadfile(instance.get()->luaState, filename.c_str()) || lua_pcall(instance.get()->luaState, 0, 0, 0)) {
			std::cout << "Error: script not loaded (" << filename << ")" << std::endl;
			instance.get()->luaState = 0;
		}
		luaL_openlibs(instance.get()->luaState); // load default Lua libs

		//Registro de las funciones

		if (instance.get()->luaState) {

		}
		else throw exception("ERROR: LUA wasn't compile correctly");

		return true;
	}

	bool ScriptManager::Shutdown()
	{
		instance.get()->classes_.clear();
		if (instance.get()->luaState)
			lua_close(instance.get()->luaState);
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

	//luabridge::LuaRef ScriptManager::getLuaHost(Entity* ent, const std::string& e_name)
	//{
	//    luabridge::LuaRef b = luabridge::LuaRef(luaState);
	//    if (ent->hasComponent((int)ManID::LUA, enum_map_[c_name]))
	//        b = static_cast<LuaComponent*>(ent->getComponent((int)ManID::LUA, enum_map_[c_name]))->getSelf();
	//    return b;
	//}

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
		//INPUT
		//GRAPHICS
		//PHYSICS
		//UI
		//SCENE
		//LUA
		getGlobalNamespace(luaState).beginClass<ScriptManager>("ScriptManager")
			.endClass();
	}

	bool ScriptManager::reloadLuaScript(const std::string& luafile)
	{
		return checkLua(luaState, luaL_dofile(luaState, luafile.c_str()));
	}
}