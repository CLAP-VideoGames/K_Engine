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

	bool ScriptManager::Init(std::string name)
	{
		try {
			instance->name = name;
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
    //UI
    //LUA
    getGlobalNamespace(luaState).beginClass<ScriptManager>("ScriptManager")
		
        .endClass();
}

	bool ScriptManager::reloadLuaScript(const std::string& luafile)
	{
		return checkLua(luaState, luaL_dofile(luaState, luafile.c_str()));
	}
}