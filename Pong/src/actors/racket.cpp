#include "pong/actors/racket.h"

namespace pong
{
Racket::Racket(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer)
	: Actor(render_manager, physics_manager, move_manager, layer)
{
}

Racket::~Racket() = default;

void Racket::UpdateImpl(const time::Duration& delta_time)
{
	if (m_last_frame_displacement_vector == MoveDirection::None)
	{
		return;
	}
	int direction = m_last_frame_displacement_vector == MoveDirection::Up ? 1 : -1;
	glm::vec2 move{ 0, direction * m_speed * time::SecInFloat(delta_time) };
	Move(move);
}

void Racket::SetDirection(MoveDirection direction)
{
	m_last_frame_displacement_vector = direction;
}

void Racket::SetSpeed(float speed)
{
	m_speed = speed;
}

void Racket::OnCollided(const ICollider& other)
{
}

}
