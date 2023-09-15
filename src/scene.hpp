#pragma once

#include "../vendor/entt/entt.hpp"
extern "C" {
#include "lua.h"
}
#include "gameobject.hpp"

struct Scene {
    entt::registry registry;
    lua_State *L;
};

// void spawn(char *lua_file);
// void spawn_at(char *lua_file, float x, float y);
// void add_gameobject();
// void add_component();
