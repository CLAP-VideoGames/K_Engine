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

	void ScriptManager::loadScene(std::string sceneFile, EntityManager* entMan){
		if (!reloadLuaScript(sceneFile))
			throw std::string("the scene" + sceneFile + "is not valid\n.");

		//std::vector<string> extraMembers = { "GameObjectType"};
		//dataComponents.insert(dataComponents.end(), extraMembers.begin(), extraMembers.end());

		std::vector<string> entities;
		luabridge::LuaRef ent = getTable("entities"); /*getMetatable(table, "entities");*/
		int numEntities = ent.length();
		for (size_t i = 1; i <= numEntities; i++)
			entities.push_back(ent[i].cast<string>());

		luabridge::LuaRef scene = getTable("scene");
		
		for (size_t i = 0; i < numEntities; i++){
			luabridge::LuaRef entity = getMetatable(scene, entities[i]);
			for (size_t j = 0; j < dataComponents.size(); j++){
				luabridge::LuaRef property = getMetatable(entity, dataComponents[j]);

				if (!property.isNil()) {

					int hola = 10;
					/*CraeateEntity with components;
					datos1
					datos2
					datos3
					...
					addComponent(dataComponents[j], ts ...);
					addComponent(dataComponents[j], datos1, datos2, datos3, ....);
					*/
				}
			}
			//iterate over extraMembers which are not components

		}
		
		
		/*string name = getParameter<string>(table, "name");
		float x = getParameter<float>(getMetatable(table, "position"), "x");
		float y = getParameter<float>(getMetatable(table, "position"), "y");
		cout << "Player: " << name <<
			"\nIn Position: " << x << ", "
			<< y << endl;*/
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