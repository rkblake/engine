#pragma once

extern "C" {
#include "lua.h"
}
#include "../gameobject.hpp"
#include "../scene.hpp"
// #include "transform.hpp"
#include <raylib.h>

struct Component {};

struct ScriptComponent : Component {
    lua_State *L;
};

struct Position3f : Component {
    float x;
    float y;
    float z;
};

struct Rotation3f : Component {
    float x;
    float y;
    float z;
};

struct Scale3f : Component {
    float x;
    float y;
    float z;
};

struct Transform3f : Component {
    Position3f position;
    Rotation3f rotation;
    Scale3f scale;
};

struct Sprite2D : Component {
    Transform3f transform;
    Image image;
};

void new_sprite2d(Scene &scene, GameObject &game_object) {
    // scene.registry.emplace<Sprite2D>(game_object, );
}

struct BoxCollider : Component {};
