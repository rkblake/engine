#pragma once

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

#include <optional>

namespace lua {

lua_State *lua_openfile(const char *filename) {
    lua_State *L = luaL_newstate();

    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        fprintf(stderr, "Failed to open lua file\n");
}

std::optional<char *> get_str_safe(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    if (!lua_isstring(L, -1)) {
        fprintf(stderr, "ERROR: in settings.lua %s should be string\n", name);
        return {};
    }
    char *ret = (char *)lua_tostring(L, -1);
    lua_pop(L, -1);
    return {ret};
}

std::optional<int> get_int_safe(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    if (!lua_isnumber(L, -1)) {
        fprintf(stderr, "ERROR: in settings.lua %s should be number\n", name);
        return {};
    }
    int ret = (int)lua_tonumber(L, -1);
    lua_pop(L, -1);
    return {ret};
}

} // namespace lua
