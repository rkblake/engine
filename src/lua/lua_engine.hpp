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

    if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "Failed to open lua file: %s\n", filename);
        exit(-1);
    }

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

void lua_print_stack(lua_State *L) {
    int top = lua_gettop(L);

    // const char *str = "From top to bottom, the lua stack is \n";
    printf("==============================================\n");
    printf("Printing Lua Stack\n");
    for (unsigned index = top; index > 0; index--) {
        printf("%3d: ", index);
        int type = lua_type(L, index);
        switch (type) {
        // booleans
        case LUA_TBOOLEAN:
            printf("%s\n", (lua_toboolean(L, index) ? "true" : "false"));
            break;

        // numbers
        case LUA_TNUMBER:
            printf("%f\n", lua_tonumber(L, index));
            break;

        // strings
        case LUA_TSTRING:
            printf("%s\n", lua_tostring(L, index));
            break;

        // other
        default:
            printf("%s\n", lua_typename(L, type));
            break;
        }
    }
    printf("==============================================\n");
}

} // namespace lua
