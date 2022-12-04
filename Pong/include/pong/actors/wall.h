#pragma once

#include "pong/actors/actor.h"

#include "pong/utils/time.h"

namespace pong
{
class Wall : public Actor
{
public:
	Wall(RenderManager& render_manager, PhysicsManager& physics_manager, int layer);
	~Wall() override;

	void UpdateImpl(const time::Duration& delta_time) override;
};
}
