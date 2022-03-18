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
    L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
        std::cout << "Error: script not loaded (" << filename << ")" << std::endl;
        L = 0;
    }

	return true;
}

bool ScriptManager::Shutdown()
{
    if (L) lua_close(L);
	return true;
}

void ScriptManager::printError(const std::string& variableName, const std::string& reason)
{
    std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

//Tuto
//https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/
template <>
inline std::string ScriptManager::lua_getdefault() {
    return "null";
}

template<typename T>
T get(const std::string& variableName) {
    if (!L) {
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

    lua_pop(L, level + 1); // pop all existing elements from stack
    return result;
}

bool ScriptManager::lua_gettostack(const std::string& variableName) {
    level = 0;
    std::string var = "";
    for (unsigned int i = 0; i < variableName.size(); i++) {
        if (variableName.at(i) == '.') {
            if (level == 0) {
                lua_getglobal(L, var.c_str());
            }
            else {
                lua_getfield(L, -1, var.c_str());
            }

            if (lua_isnil(L, -1)) {
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
        lua_getglobal(L, var.c_str());
    }
    else {
        lua_getfield(L, -1, var.c_str());
    }
    if (lua_isnil(L, -1)) {
        printError(variableName, var + " is not defined");
        return false;
    }

    return true;
}

template <>
inline bool template <>
inline bool LuaScript::lua_get(const std::string& variableName) {
    return (bool)lua_toboolean(L, -1);
}

template <>
inline float LuaScript::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template <>
inline int LuaScript::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (int)lua_tonumber(L, -1);
}

template <>
inline std::string LuaScript::lua_get(const std::string& variableName) {
    std::string s = "null";
    if (lua_isstring(L, -1)) {
        s = std::string(lua_tostring(L, -1));
    }
    else {
        printError(variableName, "Not a string");
    }
    return s;
}::lua_get(const std::string& variableName) {
    return (bool)lua_toboolean(L, -1);
}

template <>
inline float template <>
inline bool LuaScript::lua_get(const std::string& variableName) {
    return (bool)lua_toboolean(L, -1);
}

template <>
inline float LuaScript::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template <>
inline int template <>
inline bool LuaScript::lua_get(const std::string& variableName) {
    return (bool)lua_toboolean(L, -1);
}

template <>
inline float LuaScript::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template <>
inline int ScripManager::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (int)lua_tonumber(L, -1);
}

template <>
inline std::string ScripManager::lua_get(const std::string& variableName) {
    std::string s = "null";
    if (lua_isstring(L, -1)) {
        s = std::string(lua_tostring(L, -1));
    }
    else {
        printError(variableName, "Not a string");
    }
    return s;
}::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (int)lua_tonumber(L, -1);
}

template <>
inline std::string ScripManager::lua_get(const std::string& variableName) {
    std::string s = "null";
    if (lua_isstring(L, -1)) {
        s = std::string(lua_tostring(L, -1));
    }
    else {
        printError(variableName, "Not a string");
    }
    return s;
}::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template <>
inline int LuaScript::lua_get(const std::string& variableName) {
    if (!lua_isnumber(L, -1)) {
        printError(variableName, "Not a number");
    }
    return (int)lua_tonumber(L, -1);
}

template <>
inline std::string ScripManager::lua_get(const std::string& variableName) {
    std::string s = "null";
    if (lua_isstring(L, -1)) {
        s = std::string(lua_tostring(L, -1));
    }
    else {
        printError(variableName, "Not a string");
    }
    return s;
}
