// C++ program to illustrate the use of
// LuaCpp library
#include <stdio.h>
#include <lua.h>
#include <LuaBridge.h>
#include <lualib.h>
#include <lauxlib.h>

using namespace luabridge;

int main() {
    lua_State* L = luaL_newstate();
    luaL_dofile(L, "script.lua");
    luaL_openlibs(L);
    lua_pcall(L, 0, 0, 0);
    LuaRef s = getGlobal(L, "testString");
    LuaRef n = getGlobal(L, "number");
    std::string luaString = s.cast<std::string>();
    int answer = n.cast<int>();
    std::cout << luaString << std::endl;
    std::cout << "And here's our number:" << answer << std::endl;
}
