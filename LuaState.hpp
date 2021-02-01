#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"

class LuaState
{
private:
	lua_State* L;

	class LuaPush
	{
	private:
		lua_State* L;

	public:
		LuaPush(lua_State* L);

		void boolean(bool b);
		//TODO cFunc/cClosure
		//TODO fString
		void globalTable();
		void integer(LuaInt n);
		//Internally lightuserdata
		void pointer(void* p);
		//TODO pushliteral
		//TODO pushlstring
		void nil();
		void number(LuaNum n);
		void string(const std::string& s);
		//TODO pushthread
		//internally pushvalue
		void copy(int idx);
		//TODO vfstring
	};

	class LuaTo
	{
	private:
		lua_State* L;

	public:
		LuaTo(lua_State* L);

		bool boolean(int idx);
		//TODO toCFunc
		LuaInt integer(int idx, bool unsafe = true);
		//TODO look at tolstring & tostring
		LuaNum number(int idx, bool unsafe = true);
		//internally touserdata
		void* pointer(int idx);
		//TODO tothread

	};

	class LuaIs
	{
	private:
		lua_State* L;

	public:
		LuaIs(lua_State* L);

		bool boolean(int idx);
		bool cFunction(int idx);
		bool function(int idx);
		bool integer(int idx);
		//internally isLightUserData
		bool pointer(int idx);
		bool nil(int idx);
		//internally isNone
		bool invalid(int idx);
		//internally isNoneOrNil
		bool invalidOrNil(int idx);
		bool number(int idx);
		bool string(int idx);
		bool table(int idx);
		bool thread(int idx);
		bool userdata(int idx);
		bool yieldable(int idx);
	};

	class LuaGet
	{
	private:
		lua_State* L;

	public:
		LuaGet(lua_State* L);

		//TODO LuaGet
		LuaType global(const std::string& name);
	};
	
	class LuaLoader
	{
	private:
		lua_State* L;

		void callSetup();

	public:
		LuaLoader(lua_State* L);

		void stdLibs();
		void file(const std::string& filename, bool setup = true);
		void string(const std::string& s, bool setup = true);
	};

public:
	
	LuaPush push;
	LuaTo to;
	LuaLoader load;
	LuaGet get;

	LuaState(bool openLibs = true);
	
	void pop(int n);
	LuaType getType(int idx);

	void call(int numArgs = 0, int numReturns = LUA_MULTRET);

};

