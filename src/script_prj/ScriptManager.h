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
    typedef int (*lua_CFunction) (lua_State* L);

namespace K_Engine {
    class LogManager;
    class EntityManager;
    class Entity;
    class ComponentManager;
    class Component;
    class PhysicsManager;
    class RenderManager;


    class  __declspec(dllexport) ScriptManager {
    public:
        ScriptManager();
        ~ScriptManager();

        static ScriptManager* GetInstance();

        static bool Init();
        static bool Shutdown();

        luabridge::LuaRef getLuaClass(const std::string& c_name);

        void registerClassesandFunctions(lua_State* L);
        //Reload Lua Script
        bool reloadLuaScript(const std::string& luafile);

        //Lectura de tablas
        luabridge::LuaRef getTable(const std::string& c_name);
        luabridge::LuaRef getMetatable(luabridge::LuaRef table, const std::string& c_name);

        //Lectura de parametros
        /// <summary>
        /// Lectura de un parametro perteneciente a un tabla de Lua
        /// Una forma adecuada de obtener la tabla es usando getTable o getMetatable si está a un nivel más profundo
        /// </summary>
        /// <param name="object"></param>
        template<class T>
        T getParameter(luabridge::LuaRef table, const std::string& parameterName);


        //Lectura de una tabla script YA CARGADO sin llamar desde Lua
        void loadLuaScene(std::string scene, EntityManager* entMan);

        //Publicar funcion de C++ a Lua
        void registerCFunctionToLua(std::string name, lua_CFunction(*func)(lua_State* L));
        //Quitar funcion de C++ a Lua
        void unRegisterCFunctionToLua(std::string name, lua_CFunction(*func)(lua_State* L));

        //Publicar funcion de C++ a Lua
        template <typename T>
        void publishCNamespaceFunctionToLua(std::string classTypename, std::string name, lua_CFunction(*func)(lua_State* L));

        //Devolver funcion de Lua a C++
        luabridge::LuaRef getLuaFunction(std::string funcName);
        //Llamada a una función de lua
        //template<typename ...Ts>
        void callLuaFunction(std::string funcName, float f);
        void callLuaCallback(std::string funcName);

    private:
        void doLuaFunction();
        void pushToStack();

        static std::unique_ptr<ScriptManager> instance;

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
