#include <lua.hpp>
#include <windows.h>

#pragma comment(lib, "../YunitiTresde/LuaJIT-2.0.5/src/lua51.lib")

/*
static int lua_sleep(lua_State *L)
{
	int m = static_cast<int> (luaL_checknumber(L, 1));
	usleep(m * 1000);
	// usleep takes microseconds. This converts the parameter to milliseconds. 
	// Change this as necessary. 
	// Alternatively, use 'sleep()' to treat the parameter as whole seconds. 
	return 0;
}
*/

int main(int argc, char* argv[])
{
	// create new Lua state
	
	lua_State *lua_state;
	lua_state = luaL_newstate();
	
	// load Lua libraries
	static const luaL_Reg lualibs[] =
	{
		{ "base", luaopen_base },{ NULL, NULL }
	};

	const luaL_Reg *lib = lualibs;
	for (; lib->func != NULL; lib++)
	{
		lib->func(lua_state);
		lua_settop(lua_state, 0);
	}
	
	// run the Lua script
	luaL_dofile(lua_state, "helloworld.lua");
	
	// close the Lua state
	lua_close(lua_state);
	
	Sleep(100000);
}
