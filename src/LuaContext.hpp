#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"
#include <stdexcept>

//TOFIX Figure out how to let users have upvalues for SaturnFuncs
//TOFIX Figure out if LuaContext needs any state

namespace saturn
{
	class LuaContext;

	using SaturnFunc = int (*)(LuaContext&);
	using LuaCFunc = int (*)(lua_State*);

	using LuaThread = lua_State*;
	using LuaString = const char*;

	class LuaContext
	{
	private:
		lua_State* L;

		static int callOverride(lua_State* L);

	public:

		void push(bool b);
		void push(LuaInt n);
		void push(LuaNum n);
		void push(const std::string& s);
		void push(char* s);
		void push(LuaCFunc func, int upvalues = 0);
		void push(SaturnFunc func);
		
		void push(void* p);

		void push_nil();
		void push_globalTable();
		
		void new_table(int arrayHint = 0, int dictHint = 0);
		LuaThread new_thread();
		void* new_userdata(size_t size, int numUValues = 1);

		LuaInt to_int(int idx, int* ret = NULL);
		LuaNum to_num(int idx, int* ret = NULL);
		LuaString to_string(int idx, size_t* len = NULL);
		
		bool to_bool(int idx);
		LuaCFunc to_cFunc(int idx);
		void* to_pointer(int idx);
		LuaThread to_thread(int idx);
		
		bool is_invalid(int idx);
		bool is_bool(int idx);
		bool is_nil(int idx);
		bool is_noneOrNil(int idx);
		bool is_num(int idx);
		bool is_string(int idx);
		bool is_table(int idx);
		bool is_userdata(int idx);
		bool is_pointer(int idx);
		bool is_function(int idx);
		bool is_thread(int idx);

		bool is_yieldable(LuaThread t);

		LuaType get(int tableIdx);
		LuaType get(int tableIdx, LuaInt idx);
		LuaType get(int tableIdx, const std::string& key);
		
		bool get_metatable(int tableIdx);
		LuaType get_type(int idx);
		void get_length(int idx);

		void get_rawLength(int idx);
		LuaType get_rawKey(int tableIdx);
		LuaType get_rawIndex(int tableIdx, LuaInt idx);

		LuaType get_iUserVal(int udIdx, int n = 0);
		LuaType get_global(const std::string& name);

		void set(int tableIdx);
		void set(int tableIdx, const std::string& key);
		void set(int tableIdx, LuaInt idx);

		void set_metatable(int tableIdx);
		void set_raw(int tableIdx);
		void set_raw(int tableIdx, LuaInt idx);
		void set_raw(int tableIdx, const void* p);
		
		bool set_iUserVal(int udIdx, int n = 0);
		void set_global(const std::string& name);

		/*
		int stack_absIndex(int idx);
		//internally checkstack
		bool stack_ensure(int n);
		void stack_close();
		int stack_top();
		void stack_top(int newTop);
		void stack_insert(int idx);
		//TODO next?
		void stack_remove(int idx);
		void stack_replace(int idx);
		void stack_rotate(int idx, int n);
		//TODO equal/ other comparisons?
		*/

		//TODO LuaMetatableUtils?
		//TODO LuaArith?
		//TODO LuaGarbage?
		//TODO LuaThread?

		void initChunk();
	
		void pop(int n);

		void call(int numArgs = 0, int numReturns = LUA_MULTRET);

		void register_func(const std::string& name, LuaCFunc func);
		void register_func(const std::string& name, SaturnFunc func);

		//internally pushvalue
		void copy(int idx);
		//internally pushcopy
		void copy(int src, int dest);

		bool rawEqual(int idx1, int idx2);

		void close();

		void load_stdLibs();
		void load_file(const std::string& filename, bool init = true);
		void load_string(const std::string& s, bool init = true);

		explicit LuaContext(bool openLibs = true);
		explicit LuaContext(lua_State* L);

		~LuaContext();
	};

}