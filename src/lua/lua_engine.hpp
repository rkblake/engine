#pragma once

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#include "raylib_lua.hpp"

#include <optional>

namespace lua {

static lua_State *lua_openfile(const char *filename) {
    lua_State *L = luaL_newstate();

    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
        fprintf(stderr, "Failed to open lua file\n");

    luaopen_raylib(L);
    return L;
}

static std::optional<char *> get_str_safe(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    if (!lua_isstring(L, -1)) {
        fprintf(stderr, "ERROR: in settings.lua %s should be string\n", name);
        return {};
    }
    char *ret = (char *)lua_tostring(L, -1);
    lua_pop(L, -1);
    return {ret};
}

static std::optional<int> get_int_safe(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    if (!lua_isnumber(L, -1)) {
        fprintf(stderr, "ERROR: in settings.lua %s should be number\n", name);
        return {};
    }
    int ret = (int)lua_tonumber(L, -1);
    lua_pop(L, -1);
    return {ret};
}

static void call_lua_function(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    lua_call(L, 0, 0);
}

} // namespace lua
