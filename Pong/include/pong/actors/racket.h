#pragma once

#include "actor.h"

namespace pong
{
enum class MoveDirection
{
	None,
	Down,
	Up
};

class Racket : public Actor
{

public:
	Racket(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer);

	~Racket() override;

	void UpdateImpl(const time::Duration& delta_time) override;
	void SetDirection(MoveDirection direction);
	void SetSpeed(float speed);

	void OnCollided(const ICollider& other);

	glm::vec2 GetNormal() const override
	{
		constexpr float twist = 0.1f;
		auto normal{ m_normal };
		normal.y += GetLastFrameDisplacementVector().y > 0 ? -twist : twist;
		return normal;
	}


private:
	MoveDirection m_last_frame_displacement_vector{ MoveDirection::None };
	float m_speed{0.f};
};

}
