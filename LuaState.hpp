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
		//TODO LuaIs
	};
	
public:
	
	LuaPush push;
	LuaTo to;

	LuaState(bool openLibs = true);
	
	void pop(int n);
	LuaType getType(int idx);
};

