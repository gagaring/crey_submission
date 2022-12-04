#include "pong/actors/ball.h"

#include "pong/render/render_manager.h"

#include <glm/glm.hpp>

namespace pong {

Ball::Config::Config(const rapidjson::Document& json)
{
	m_speed = json["ball"]["speed"].GetFloat();
	m_size.x = json["ball"]["size_x"].GetFloat();
	m_size.y = json["ball"]["size_y"].GetFloat();
}

Ball::Ball(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer)
	: Actor(render_manager, physics_manager, move_manager, layer)
{
}

Ball::~Ball() = default;

void Ball::SetConfig(const Config& config)
{
	m_default_speed = config.m_speed;
	m_speed = config.m_speed;
	m_size = config.m_size;
}

void Ball::Reset()
{
	SetPosition(m_default_position);
	m_speed = m_default_speed;
}

void Ball::UpdateImpl(const time::Duration& delta_time)
{
	m_speed = m_speed + time::SecInFloat(delta_time) * 10;
	Move(m_direction * m_speed * time::SecInFloat(delta_time));
}

void Ball::SetDirection(glm::vec2 direction)
{
	m_direction = std::move(direction);
}

void Ball::SetDefaultSpeed(float speed)
{
	m_default_speed = speed;
	m_speed = m_default_speed;
}

void Ball::OnCollided(const ICollider& other)
{
	m_direction = glm::reflect(m_direction, other.GetNormal());
}

void Ball::SetDefaultPosition(glm::vec2 position)
{
	m_default_position = std::move(position);
	SetPosition(m_default_position);
}

}
