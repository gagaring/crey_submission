#pragma once

#include "pong/actors/actor.h"
#include "pong/utils/time.h"

#include <glm/vec2.hpp>
#include <rapidjson/document.h>

namespace pong
{
class Ball : public Actor
{
public:
	struct Config
	{
		Config(const rapidjson::Document& json);
		float m_speed;
		glm::vec2 m_size;
	};

public:
	Ball(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer);
	~Ball() override;

	void SetConfig(const Config& config);
	void Reset();

	void UpdateImpl(const time::Duration& delta_time) override;
	void SetDirection(glm::vec2 direction);
	void SetDefaultPosition(glm::vec2 position);

	void OnCollided(const ICollider& other) override;

private:
	void SetDefaultSpeed(float speed);

	glm::vec2 m_default_position{ 0,0 };
	glm::vec2 m_direction{ 0,0 };
	float m_speed{ 0.f };
	float m_default_speed{ 0.f };
};
}
