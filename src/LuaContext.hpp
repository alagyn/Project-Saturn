#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"

namespace saturn
{
	class LuaContext;

	using SaturnFunc = int (*)(LuaContext&);
	using LuaCFunc = int (*)(lua_State*);

	class LuaContext
	{
	private:
		lua_State* L;

		LuaContext(lua_State* L);

		class LuaPush
		{
		private:
			LuaContext* parent;
			lua_State* L;

			//TODO test efficiency of SaturnFuncs
			static int callOverride(lua_State* L);
			static int indexOverride(lua_State* L);
		public:
			LuaPush(LuaContext* parent);

			void boolean(bool b);
			void luaFunc(LuaCFunc func, int upvalues = 0);
			void saturnFunc(SaturnFunc func);
			void fString(const char* format, ...);
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

			//TODO equal?
			//rawequal
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
			LuaType type(int idx);
			void length(int idx);

			void rawLength(int idx);
			LuaType rawKey(int tableIdx);
			LuaType rawIndex(int tableIdx, LuaInt idx);

		};

		class LuaSet
		{
		private:
			lua_State* L;

		public:
			LuaSet(lua_State* L);

			void global(const std::string& name);
			void key(int tableIdx, const std::string& key);
			void key(int tableIdx);
			void index(int tableIdx, LuaInt idx);
			//TODO setiuservalue?
			void metatable(int tableIdx);

			void rawKey(int tableIdx);
			void rawIndex(int tableIdx, LuaInt idx);
		};

		class LuaStack
		{
		private:
			lua_State* L;

		public:
			LuaStack(lua_State* L);

			int absIndex(int idx);
			//internally checkstack
			bool ensure(int n);
			void close();
			int top();
			void top(int newTop);
			void insert(int idx);
			//TODO next?
			void remove(int idx);
			void replace(int idx);
			void rotate(int idx, int n);
			//TODO equal/ other comparisons?
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
		//TODO LuaArith?
		//TODO LuaGarbage?
		//TODO LuaThread?
	public:

		LuaPush push;
		LuaTo to;
		LuaLoader load;
		LuaGet get;
		LuaSet set;
		LuaStack stack;

		explicit LuaContext(bool openLibs = true);

		void pop(int n);
		
		void call(int numArgs = 0, int numReturns = LUA_MULTRET);

		void registerFunc(const std::string& name, LuaCFunc func);
		void registerFunc(const std::string& name, SaturnFunc func);

	};
}
