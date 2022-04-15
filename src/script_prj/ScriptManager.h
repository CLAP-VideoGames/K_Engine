#pragma once
#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#define SCRIPTS_FILE_PATH "assets/scripts/"
#define FILE_EXTENSION ".lua"

namespace luabridge {
    class LuaRef;
}

typedef struct lua_State lua_State;

namespace K_Engine {
    class EntityManager;

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

        //Lectura de tablas
        luabridge::LuaRef getTable(const std::string& c_name);
        luabridge::LuaRef getMetatable(luabridge::LuaRef table, const std::string& c_name);
        void setDataComponents(std::vector<std::string> components);

        //Lectura de parametros
        /// <summary>
        /// Lectura de un parametro perteneciente a un tabla de Lua
        /// Una forma adecuada de obtener la tabla es usando getTable o getMetatable si está a un nivel más profundo
        /// </summary>
        /// <param name="object"></param>
        template<class T>
        T getParameter(luabridge::LuaRef table, const std::string& parameterName);


        //Test(Provisional, borrar antes de la entrega final)

        void createPlayerbyAtrib(std::string name, float x, float y);
        //Lectura de una tabla llamando desde Lua
        void createPlayerbyObject(luabridge::LuaRef object);
        //Lectura de una tabla script YA CARGADO sin llamar desde Lua
        void loadScene(std::string scene, EntityManager* entMan);

    private:
        static std::unique_ptr<ScriptManager> instance;
        std::string n;

        lua_State* luaState;
        std::map<std::string, luabridge::LuaRef*> classes_;

        float x_, y_;

        //Clean LuaStack top
        static void clean();
        //Check lua scripting
        bool checkLua(lua_State* L, int r);
        //Clases y funciones de otros proyectos
        std::vector<std::string > dataComponents;
    };
}

#endif //SCRIPTMANAGER_H
