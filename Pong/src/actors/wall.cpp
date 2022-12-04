#include "pong/actors/wall.h"

#include <glm/vec2.hpp>

namespace pong
{

Wall::Wall(RenderManager& render_manager, PhysicsManager& physics_manager, int layer)
	: Actor(render_manager, physics_manager, layer)
{
	SetKinematic(true);
	SetSize(glm::vec2{ 1280, 10 });
}

Wall::~Wall() = default;

void Wall::UpdateImpl(const time::Duration&)
{
}

}
