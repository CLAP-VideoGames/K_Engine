#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <memory>
#include <string>
#include <map>

#define SCRIPTS_FILE_PATH "assets/scripts/"
#define FILE_EXTENSION ".lua"

namespace luabridge {
    class LuaRef;
}

typedef struct lua_State lua_State;

namespace K_Engine {
    class ScriptManager {
    public:
        ScriptManager();
        ~ScriptManager();

        static ScriptManager* GetInstance();

        static bool Init(const std::string& filename);
        static bool Shutdown();

        luabridge::LuaRef getLuaClass(const std::string& c_name);
        //luabridge::LuaRef getLuaHost(Entity* ent, const std::string& e_name);

    private:
        static std::unique_ptr<ScriptManager> instance;

        lua_State* luaState;
        std::map<std::string, luabridge::LuaRef> classes_;

        //Clean LuaStack top
        static void clean();
        //Check lua scripting
        bool checkLua(lua_State* L, int r);
        //Clases y funciones de otros proyectos
        void registerClassesandFunctions(lua_State* L);
        //Reload Lua Script
        bool reloadLuaScript(const std::string& luafile);
    };
}

#endif //SCRIPTMANAGER_H
