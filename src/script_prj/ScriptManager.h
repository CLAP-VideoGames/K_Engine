#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <memory>
#include <string>
#include <vector>

namespace luabridge {
    class LuaRef;
}

typedef struct lua_State lua_State;

class ScriptManager {
public:
    ScriptManager();
    ~ScriptManager();

    static ScriptManager* GetInstance();

    static bool Init(const std::string& filename);
    static bool Shutdown();

    void printError(const std::string& variableName, const std::string& reason);

    template<typename T>
    T get(const std::string& variableName);
    bool lua_gettostack(const std::string& variableName);
    // Generic get
    template<typename T>
    T lua_get(const std::string& variableName);
    // Generic default get
    template<typename T>
    T lua_getdefault(const std::string& variableName);
    //Generic getArray
    template<typename T>
    std::vector<T> getArray(const std::string& name);

private:
    static std::unique_ptr<ScriptManager> instance;
    std::string name;

    
    lua_State* luaState;
    int level;
    //Clean LuaStack top
    static void clean();
    bool checkLua(lua_State* L, int r);
};

#endif //SCRIPTMANAGER_H
