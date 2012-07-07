#include <lauxlib.h>

/* Input/Output pointers */

static const unsigned char *input;
static int input_ctr;
static size_t i_len;
static luaL_Buffer output_buffer;

/* Replace nkf's getchar/putchar for variable modification */
/* we never use getc, ungetc */

#undef getc
#undef ungetc
#define getc(f)     (input_ctr>=i_len?-1:input[input_ctr++])
#define ungetc(c,f) input_ctr--

#undef putchar
#undef TRUE
#undef FALSE

#define putchar(c)  luaL_addchar(&output_buffer, (c))

#define PERL_XS 1
#include "nkf/utf8tbl.c"
#include "nkf/nkf.c"

static void
nkf_buf_dispose(nkf_buf_t *buf) {
  nkf_xfree(buf->ptr);
  nkf_xfree(buf);
}

static void
nkf_state_dispose() {
  nkf_buf_dispose(nkf_state->std_gc_buf);
  nkf_buf_dispose(nkf_state->broken_buf);
  nkf_buf_dispose(nkf_state->nfc_buf);
  nkf_xfree(nkf_state);
  nkf_state = NULL;
}
 
static int l_convert(lua_State *L) {
  const char *opt = luaL_checkstring(L, 1);
  input = (const unsigned char *)luaL_checklstring(L, 2, &i_len);

  reinit();

  int ret = options((unsigned char *)opt);
  if (ret) {
    lua_pushnil(L);
    lua_pushstring(L, "nkf options error");
    lua_pushnumber(L, ret);
    nkf_state_dispose();
    return 3;
  }

  input_ctr = 0;
  luaL_buffinit(L, &output_buffer);
  ret = kanji_convert(NULL);
  if (ret) {
    lua_pushnil(L);
    lua_pushstring(L, "nkf kanji_convert error");
    lua_pushnumber(L, ret);
    nkf_state_dispose();
    return 3;
  }

  luaL_pushresult(&output_buffer);
  nkf_state_dispose();
  return 1;
}

static const struct luaL_Reg nkf[] = {
  {"convert", l_convert},
  {NULL, NULL}
};

int luaopen_nkf(lua_State *L) {
  luaL_register(L, "nkf", nkf);
  return 1;
}
