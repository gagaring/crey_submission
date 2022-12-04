#include "pong/actors/actor.h"

#include "pong/move/move_manager.h"
#include "pong/render/render_manager.h"
#include "pong/physics/bounding_box.h"
#include "pong/physics/physics_manager.h"

#include <Sprite.h>

namespace pong
{

Actor::Actor(RenderManager& render_manager, PhysicsManager& physics_manager, int layer)
	: m_sprite{ std::make_unique<sf::Sprite>() }
{
	render_manager.Register(this, layer);
	physics_manager.Register(this);
}

Actor::Actor(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer)
	: Actor(render_manager, physics_manager, layer)
{
	move_manager.Register(this);
}

Actor::~Actor() = default;

void Actor::Update(const time::Duration& delta_time)
{
	auto last_pos{ GetPosition() };
	UpdateImpl(delta_time);
	m_last_frame_displacement_vector = GetPosition() - last_pos;
}

void Actor::SetPosition(glm::vec2 position)
{
	m_sprite->setPosition(std::move(position));
}

const glm::vec2& Actor::GetPosition() const
{
	return m_sprite->getPosition();
}

void Actor::Move(const glm::vec2& move)
{
	m_sprite->setPosition(m_sprite->getPosition() + move);
}

const glm::vec2& Actor::GetLastFrameDisplacementVector() const
{
	return m_last_frame_displacement_vector;
}

void Actor::Render()
{
	m_sprite->render();
}

void Actor::SetTexture(sf::Texture* texture)
{
	m_sprite->setTexture(texture);
}

const glm::vec2& Actor::GetSize() const
{
	return m_size;
}

void Actor::SetSize(glm::vec2 size)
{
	m_size = std::move(size);
}

void Actor::OnCollided(const ICollider&)
{
}

bool Actor::IsKinematic() const
{
	return m_kinematic;
}

void Actor::SetKinematic(bool kinematic)
{
	m_kinematic = kinematic;
}

BoundingBox Actor::GetBoundingBox() const
{
	return BoundingBox(GetPosition(), m_size);
}

glm::vec2 Actor::GetNormal() const
{
	return m_normal;
}

void Actor::SetNormal(glm::vec2 normal)
{
	m_normal = std::move(normal);
}

}
