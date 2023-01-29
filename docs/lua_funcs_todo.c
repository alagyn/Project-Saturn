
/*
** state manipulation
*/
 
 lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);


/*
** basic stack manipulation
*/
 int   (lua_absindex) (lua_State *L, int idx);
 int   (lua_gettop) (lua_State *L);
 void  (lua_settop) (lua_State *L, int idx);
 void  (lua_pushvalue) (lua_State *L, int idx);
 void  (lua_rotate) (lua_State *L, int idx, int n);
 void  (lua_copy) (lua_State *L, int fromidx, int toidx);
 int   (lua_checkstack) (lua_State *L, int n);

 void  (lua_xmove) (lua_State *from, lua_State *to, int n);


/*
** Comparison and arithmetic functions
*/

#define LUA_OPADD	0	/* ORDER TM, ORDER OP */
#define LUA_OPSUB	1
#define LUA_OPMUL	2
#define LUA_OPMOD	3
#define LUA_OPPOW	4
#define LUA_OPDIV	5
#define LUA_OPIDIV	6
#define LUA_OPBAND	7
#define LUA_OPBOR	8
#define LUA_OPBXOR	9
#define LUA_OPSHL	10
#define LUA_OPSHR	11
#define LUA_OPUNM	12
#define LUA_OPBNOT	13

 void  (lua_arith) (lua_State *L, int op);

#define LUA_OPEQ	0
#define LUA_OPLT	1
#define LUA_OPLE	2

 int   (lua_rawequal) (lua_State *L, int idx1, int idx2);
 int   (lua_compare) (lua_State *L, int idx1, int idx2, int op);


/*
** 'load' and 'call' functions (load and run Lua code)
*/
 void  (lua_callk) (lua_State *L, int nargs, int nresults,
                           lua_KContext ctx, lua_KFunction k);
#define lua_call(L,n,r)		lua_callk(L, (n), (r), 0, NULL)

 int   (lua_pcallk) (lua_State *L, int nargs, int nresults, int errfunc,
                            lua_KContext ctx, lua_KFunction k);
#define lua_pcall(L,n,r,f)	lua_pcallk(L, (n), (r), (f), 0, NULL)

 int   (lua_load) (lua_State *L, lua_Reader reader, void *dt,
                          const char *chunkname, const char *mode);

 int (lua_dump) (lua_State *L, lua_Writer writer, void *data, int strip);


/*
** coroutine functions
*/
 int  (lua_yieldk)     (lua_State *L, int nresults, lua_KContext ctx,
                               lua_KFunction k);
 int  (lua_resume)     (lua_State *L, lua_State *from, int narg,
                               int *nres);
 int  (lua_status)     (lua_State *L);
 int (lua_isyieldable) (lua_State *L);

#define lua_yield(L,n)		lua_yieldk(L, (n), 0, NULL)


/*
** Warning-related functions
*/
 void (lua_setwarnf) (lua_State *L, lua_WarnFunction f, void *ud);
 void (lua_warning)  (lua_State *L, const char *msg, int tocont);


/*
** garbage-collection function and options
*/

#define LUA_GCSTOP		0
#define LUA_GCRESTART		1
#define LUA_GCCOLLECT		2
#define LUA_GCCOUNT		3
#define LUA_GCCOUNTB		4
#define LUA_GCSTEP		5
#define LUA_GCSETPAUSE		6
#define LUA_GCSETSTEPMUL	7
#define LUA_GCISRUNNING		9
#define LUA_GCGEN		10
#define LUA_GCINC		11

 int (lua_gc) (lua_State *L, int what, ...);


/*
** miscellaneous functions
*/

 int   (lua_error) (lua_State *L);

 int   (lua_next) (lua_State *L, int idx);

 void  (lua_concat) (lua_State *L, int n);

 size_t   (lua_stringtonumber) (lua_State *L, const char *s);

 lua_Alloc (lua_getallocf) (lua_State *L, void **ud);
 void      (lua_setallocf) (lua_State *L, lua_Alloc f, void *ud);

 void  (lua_toclose) (lua_State *L, int idx);
