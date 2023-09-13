#pragma once

#include "../vendor/entt/entt.hpp"

struct Scene {
    entt::registry registry;
};

// void spawn(char *lua_file);
// void spawn_at(char *lua_file, float x, float y);
void add_gameobject(GameObject game_object);
