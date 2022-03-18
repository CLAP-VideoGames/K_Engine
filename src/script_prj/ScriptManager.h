#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <memory>
#include <string>

namespace Lua {
    class LuaScript;
}

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
    T lua_get(const std::string& variableName) {
        return 0;
    }
    // Generic default get
    template<typename T>
    T lua_getdefault(const std::string& variableName) {
        return 0;
    }

    inline std::string lua_getdefault();
private:
    static std::unique_ptr<ScriptManager> instance;
    std::string name;

    lua_State* L;
};

#endif //SCRIPTMANAGER_H
