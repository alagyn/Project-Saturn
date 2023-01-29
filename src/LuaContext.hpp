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
	
	using LuaInt = lua_Integer;
	using LuaNum = lua_Number;
	using LuaUInt = lua_Unsigned;

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
		void push(const char* s);
		void push(const char* s, size_t len);
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
		const char* to_str(int idx, size_t* len = NULL);
		
		bool to_bool(int idx);
		LuaCFunc to_cFunc(int idx);
		void* to_pointer(int idx);
		LuaThread to_thread(int idx);
		
		LuaType type(int idx);
		bool is_noneOrNil(int idx);
		static bool is_yieldable(LuaThread t);
		bool is_cFunc(int idx);
		bool is_int(int idx);
		bool is_num(int idx);
		bool is_str(int idx);
		bool is_userdata(int idx);

		LuaType get(int tableIdx);
		LuaType get(int tableIdx, LuaInt idx);
		LuaType get(int tableIdx, const std::string& key);
		
		void set(int tableIdx);
		void set(int tableIdx, const std::string& key);
		void set(int tableIdx, LuaInt idx);

		bool get_metatable(int tableIdx);
		void set_metatable(int tableIdx);
		
		LuaType get_raw(int tableIdx);
		LuaType get_raw(int tableIdx, LuaInt idx);
		LuaType get_raw(int tableIdx, const void* p);

		void set_raw(int tableIdx);
		void set_raw(int tableIdx, LuaInt idx);
		void set_raw(int tableIdx, const void* p);

		LuaType get_iUserVal(int udIdx, int n = 0);
		bool set_iUserVal(int udIdx, int n = 0);

		LuaType get_global(const std::string& name);
		void set_global(const std::string& name);

		/* TODO
		arith
		absindex
		compare
		concat
		closeslot?
		checkstack
		dump
		error
		gc
		getallocf
		getextraspace
		gettop
		insert
		load
		next
		numbertointeger
		rawequal
		Reader?
		remove
		replace
		resume
		rotate
		setallocf
		settop
		setwarnf
		status
		stringtonumber
		upvalueindex
		warning
		Writer?
		xmove
		yield
		yieldk
		*/

		//TODO lua_Debug interface

		//TODO lua_aux
		
		void initChunk();
	
		void pop(int n);

		void call(int numArgs = 0, int numReturns = LUA_MULTRET);
		//void call(const std::string& func, int numArgs = 0, int numReturns = LUA_MULTRET);
		//void call(const char* func, int numArgs = 0, int numReturns = LUA_MULTRET);
		//TODO callk/pcallk?

		void registerFunc(const std::string& name, LuaCFunc func);
		void registerFunc(const std::string& name, SaturnFunc func);

		static int resetThread(LuaThread t);

		//internally pushvalue
		void copy(int idx);
		//internally pushcopy
		void copy(int src, int dest);

		void len(int idx);
		LuaUInt rawlen(int idx);

		bool rawEqual(int idx1, int idx2);

		void close();

		void load_stdLibs();
		void load_file(const std::string& filename, bool init = true);
		void load_string(const std::string& s, bool init = true);

		explicit LuaContext(bool openLibs = true);
		explicit LuaContext(lua_State* L);

		lua_State* getState();

		~LuaContext();

		LuaNum version();
	};

}
