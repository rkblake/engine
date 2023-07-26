#pragma once

#include "lua_engine.hpp"
#include <raylib.h>

static int draw_text(lua_State *L) {
    const char *text = luaL_checkstring(L, 1);
    const int x = luaL_checkinteger(L, 2);
    const int y = luaL_checkinteger(L, 3);

    DrawText(text, x, y, 10, RAYWHITE);

    return 0;
}

static int draw_rect(lua_State *L) {
    const int x = luaL_checkinteger(L, 1);
    const int y = luaL_checkinteger(L, 2);
    const int width = luaL_checkinteger(L, 3);
    const int height = luaL_checkinteger(L, 4);

    DrawRectangle(x, y, width, height, RAYWHITE);

    return 0;
}

static int is_key_down(lua_State *L) {
    const int keycode = luaL_checkinteger(L, 1);

    const bool key_pressed = IsKeyDown(keycode);
    lua_pushinteger(L, key_pressed);

    return 1;
}

static const struct luaL_Reg raylib[]{{"draw_text", draw_text},
                                      {"draw_rect", draw_rect},
                                      {"is_key_down", is_key_down},
                                      {NULL, NULL}};

static int luaopen_raylib(lua_State *L) {
    for (auto lib : raylib) {
        luaL_requiref(L, lib.name, lib.func, 1);
    }
    return 1;
}
