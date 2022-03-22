#include "ScriptManager.h"

#include <stdio.h>
#include <vector>
#include <iostream>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <LuaBridge.h>

using namespace std;
using namespace luabridge;

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
    if (instance.get()->luaState) 
        lua_close(instance.get()->luaState);
    return true;
}

void ScriptManager::printError(const std::string& variableName, const std::string& reason)
{
    std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

template<typename T>
T ScriptManager::lua_getdefault(const std::string& variableName) {
    return 0;
}

template<>
std::string ScriptManager::lua_getdefault(const std::string& variableName) {
    return "null";
}

void ScriptManager::clean()
{
    int n = lua_gettop(instance.get()->luaState);
    lua_pop(instance.get()->luaState, n);
}

template<typename T>
T ScriptManager::get(const std::string& variableName) {
    if (!luaState) {
        printError(variableName, "Script is not loaded");
        return lua_getdefault<T>();
    }

    T result;
    if (lua_gettostack(variableName)) { // variable succesfully on top of stack
        result = lua_get<T>(variableName);
    }
    else {
        result = lua_getdefault<T>();
    }

    lua_pop(luaState, level + 1); // pop all existing elements from stack
    return result;
}

bool ScriptManager::lua_gettostack(const std::string& variableName) {
    level = 0;
    std::string var = "";
    for (unsigned int i = 0; i < variableName.size(); i++) {
        if (variableName.at(i) == '.') {
            if (level == 0) {
                lua_getglobal(luaState, var.c_str());
            }
            else {
                lua_getfield(luaState, -1, var.c_str());
            }

            if (lua_isnil(luaState, -1)) {
                printError(variableName, var + " is not defined");
                return false;
            }
            else {
                var = "";
                level++;
            }
        }
        else {
            var += variableName.at(i);
        }
    }
    if (level == 0) {
        lua_getglobal(luaState, var.c_str());
    }
    else {
        lua_getfield(luaState, -1, var.c_str());
    }
    if (lua_isnil(luaState, -1)) {
        printError(variableName, var + " is not defined");
        return false;
    }

    return true;
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

template<>
bool ScriptManager::lua_get(const std::string& variableName) {
    return (bool)lua_toboolean(luaState, -1);
}

template<>
float ScriptManager::lua_get(const std::string& variableName) {
    if (!lua_isnumber(luaState, -1)) {
    printError(variableName, "Not a number");
    }
    return (float)lua_tonumber(luaState, -1);
}

template<>
int ScriptManager::lua_get(const std::string& variableName) {
    if (!lua_isnumber(luaState, -1)) {
        printError(variableName, "Not a number");
    }
    return (int)lua_tonumber(luaState, -1);
}

template<>
std::string ScriptManager::lua_get(const std::string& variableName) {
    std::string s = "null";
    if (lua_isstring(luaState, -1)) {
        s = std::string(lua_tostring(luaState, -1));
    }
    else {
        printError(variableName, "Not a string");
    }
    return s;
}

//Array getters
template<typename T>
std::vector<T> ScriptManager::getArray(const std::string& name) {
    std::vector<T> v;
    if (!lua_gettostack(name.c_str())) {
        printError(name, "Array not found");
        clean();
        return std::vector<T>();
    }
    lua_pushnil(luaState);
    while (lua_next(luaState, -2)) {
        if (lua_isnumber(luaState, -1)) {
            v.push_back((T)lua_tonumber(luaState, -1));
        }
        lua_pop(luaState, 1);
    }
    clean();
    return v;
}

template<>
std::vector<std::string> ScriptManager::getArray(const std::string& name) {
    std::vector<std::string> v;
    if (!lua_gettostack(name.c_str())) {
        printError(name, "Array not found");
        clean();
        return std::vector<std::string>();
    }
    lua_pushnil(luaState);
    while (lua_next(luaState, -2)) {
        if (lua_isstring(luaState, - 1)) {
            v.push_back(std::string(lua_tostring(luaState, -1)));
        }
        lua_pop(luaState, 1);
    }
    clean();
    return v;
}