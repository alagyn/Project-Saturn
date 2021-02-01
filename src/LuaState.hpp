#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"
#include <unordered_map>

namespace saturn
{
	class LuaState;

	using SaturnFunc = int (*)(LuaState&);
	using LuaCFunc = int (*)(lua_State*);

	class LuaState
	{
	private:
		lua_State* L;

		LuaState(lua_State* L);

		class LuaPush
		{
		private:
			LuaState* parent;
			lua_State* L;

			static int callOverride(lua_State* L);
			static int indexOverride(lua_State* L);
		public:
			LuaPush(LuaState* parent);

			void boolean(bool b);
			void luaFunc(LuaCFunc func);
			void saturnFunc(SaturnFunc func);
			//TODO cClosure
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
			void copy(int from, int to);
			//TODO vfstring
			void table(int arrayHint = 0, int dictHint = 0);
			//TODO newuserdata
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
			const char* string(int idx, size_t* len = nullptr);
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
			LuaType index(int tableIdx, LuaInt idx);
			LuaType key(int tableIdx, const std::string& key);
			//Uses top of stack as key, works for any object as key?
			LuaType key(int tableIdx);
			//Returns true if mt exists
			bool metatable(int tableIdx);
		};

		class LuaSet
		{
		private:
			lua_State* L;

		public:
			LuaSet(lua_State* L);

			void global(const std::string& name);
			//TODO LuaSet
		};

		class LuaStack
		{
		private:
			lua_State* L;

		public:
			LuaStack(lua_State* L);

			//TODO top()
			//TODO checkstack
			//TODO absindex
			//TODO insert
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

		//TODO LuaMetatableUtils?

	public:

		LuaPush push;
		LuaTo to;
		LuaLoader load;
		LuaGet get;
		LuaSet set;
		LuaStack stack;

		explicit LuaState(bool openLibs = true);

		void pop(int n);
		LuaType getType(int idx);

		void call(int numArgs = 0, int numReturns = LUA_MULTRET);

	};
}
