#include "../vendor/entt/entt.hpp"
extern "C" {
#include "../vendor/lua/lauxlib.h"
#include "../vendor/lua/lua.h"
#include "../vendor/lua/lualib.h"
}
#include "raylib.h"
#include <cstdio>
#include <functional>
#include <optional>
#include <stdio.h>

using namespace std;

optional<char *> get_str_safe(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    if (!lua_isstring(L, -1)) {
        fprintf(stderr, "ERROR: in settings.lua %s should be string\n", name);
        return {};
    }
    char *ret = (char *)lua_tostring(L, -1);
    lua_pop(L, -1);
    return {ret};
}

optional<int> get_int_safe(const char *name, lua_State *L) {
    lua_getglobal(L, name);
    if (!lua_isnumber(L, -1)) {
        fprintf(stderr, "ERROR: in settings.lua %s should be number\n", name);
        return {};
    }
    int ret = (int)lua_tonumber(L, -1);
    lua_pop(L, -1);
    return {ret};
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "engine: missing arguments\n");
        fprintf(stderr, "usage: engine settings.lua\n");
        return -1;
    }

    lua_State *settings = luaL_newstate();

    if (luaL_loadfile(settings, argv[1]) || lua_pcall(settings, 0, 0, 0))
        fprintf(stderr, "Failed to open lua file\n");

    auto title = get_str_safe("title", settings);
    auto screen_width = get_int_safe("width", settings);
    auto screen_height = get_int_safe("height", settings);
    auto fps_target = get_int_safe("fps_target", settings);

    if (!title || !screen_width || !screen_height || !fps_target)
        return -1;

    SetTraceLogLevel(LOG_ERROR | LOG_WARNING);
    InitWindow(*screen_width, *screen_height, *title);

    SetTargetFPS(*fps_target);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
