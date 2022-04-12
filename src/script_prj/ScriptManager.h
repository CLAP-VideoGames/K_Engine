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
    class  __declspec(dllexport) ScriptManager {
    public:
        ScriptManager();
        ~ScriptManager();

        static ScriptManager* GetInstance();

        static bool Init(std::string name);
        static bool Shutdown();

        luabridge::LuaRef getLuaClass(const std::string& c_name);

        void registerClassesandFunctions(lua_State* L);
        //Reload Lua Script
        bool reloadLuaScript(const std::string& luafile);
    private:
        static std::unique_ptr<ScriptManager> instance;
        std::string n;

        lua_State* luaState;
        std::map<std::string, luabridge::LuaRef> classes_;

        float x_, y_;

        //Clean LuaStack top
        static void clean();
        //Check lua scripting
        bool checkLua(lua_State* L, int r);
        //Clases y funciones de otros proyectos

        //Test
        void createPlayerbyAtrib(std::string name, float x, float y);
        void createPlayerbyObject(luabridge::LuaRef object);
    };
}

#endif //SCRIPTMANAGER_H
