#include <cstdio>
#include <optional>
#include <raylib.h>
#include <stdio.h>
#include <string>

#include "lua/lua_engine.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "engine: missing arguments\n");
        fprintf(stderr, "usage: engine path/to/settings.lua\n");
        return -1;
    }

    lua_State *settings = lua::lua_openfile(argv[1]);
    printf("[Engine] Opened %s\n", argv[1]);

    auto title = lua::get_str_safe("title", settings);
    auto screen_width = lua::get_int_safe("width", settings);
    auto screen_height = lua::get_int_safe("height", settings);
    auto fps_target = lua::get_int_safe("fps_target", settings);
    auto main_scene = lua::get_str_safe("main_scene", settings);

    const string settings_path = string(argv[1]);
    const string main_scene_path = // TODO: test if path works if it has no '/'
        settings_path.substr(0, settings_path.find_last_of('/')) + "/" +
        string(*main_scene);
    printf("[Engine] Running %s\n", main_scene_path.c_str());

    if (!title || !screen_width || !screen_height || !fps_target)
        return -1;

    SetTraceLogLevel(LOG_ERROR | LOG_WARNING);
    InitWindow(*screen_width, *screen_height, *title);
    printf("[Engine] Started %dx%d window\n", *screen_width, *screen_height);

    SetTargetFPS(*fps_target);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    printf("[Engine] Closing\n");

    return 0;
}
