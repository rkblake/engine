#include <cstdio>
#include <optional>
#include <raylib.h>
#include <stdio.h>

#include "lua/lua_engine.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "engine: missing arguments\n");
        fprintf(stderr, "usage: engine settings.lua\n");
        return -1;
    }

    lua_State *settings = lua::lua_openfile(argv[1]);

    auto title = lua::get_str_safe("title", settings);
    auto screen_width = lua::get_int_safe("width", settings);
    auto screen_height = lua::get_int_safe("height", settings);
    auto fps_target = lua::get_int_safe("fps_target", settings);

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
