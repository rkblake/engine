#include "../vendor/entt/entt.hpp"
extern "C" {
#include "../vendor/lua/lauxlib.h"
#include "../vendor/lua/lua.h"
#include "../vendor/lua/lualib.h"
}
#include "raylib.h"
#include <cstdio>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "engine: missing arguments\n");
        fprintf(stderr, "usage: engine settings.lua\n");
        return -1;
    }

    lua_State *settings_file = luaL_newstate();

    if (luaL_loadfile(settings_file, argv[1]) ||
        lua_pcall(settings_file, 0, 0, 0))
        fprintf(stderr, "Failed to open lua file\n");

    lua_getglobal(settings_file, "title");
    lua_getglobal(settings_file, "width");
    lua_getglobal(settings_file, "height");
    lua_getglobal(settings_file, "fps_target");

    if (!lua_isstring(settings_file, -4))
        fprintf(stderr, "title should be a string\n");
    if (!lua_isnumber(settings_file, -3))
        fprintf(stderr, "width should be a number\n");
    if (!lua_isnumber(settings_file, -2))
        fprintf(stderr, "height should be a number\n");
    if (!lua_isnumber(settings_file, -1))
        fprintf(stderr, "fps_target should be a number\n");

    int screen_width = (int)lua_tonumber(settings_file, -3);
    int screen_height = (int)lua_tonumber(settings_file, -2);
    int fps_target = (int)lua_tonumber(settings_file, -1);
    char *title = (char *)lua_tostring(settings_file, -4);

    SetTraceLogLevel(LOG_WARNING | LOG_ERROR);
    InitWindow(screen_width, screen_height, title);

    SetTargetFPS(fps_target);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
