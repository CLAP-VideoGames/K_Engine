// C++ program to illustrate the use of
// LuaCpp library
#include <stdio.h>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <LuaBridge.h>

using namespace luabridge;

void write(const char* str) {
	std::cout << str << std::endl;
}

static int l_write(lua_State* L) {
	const char* str = lua_tostring(L, 1); // get function argument
	write(str); // calling C++ function with this argument...
	return 0; // nothing to return!
}

int main() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L); // load default Lua libs
	if (luaL_loadfile(L, "assets/scripts/test.lua")) {
		std::cout << "Error loading script" << std::endl;
	}
	lua_pushcfunction(L, l_write);
	lua_setglobal(L, "writ"); // this is how function will be named in Lua
	
	lua_pcall(L, 0, 0, 0); // run script

	lua_close(L);
}
