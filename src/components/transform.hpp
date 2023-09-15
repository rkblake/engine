#pragma once

#include "component.hpp"

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
