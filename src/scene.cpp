#include "scene.hpp"

#include "components/component.hpp"
#include "gameobject.hpp"

Scene current_scene;

entt::entity add_gameobject(Scene scene) { return scene.registry.create(); }

Scene &get_current_scene() { return current_scene; }

// void add_component(Scene scene, Component component) {}
