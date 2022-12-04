#pragma once

#include "pong/move/i_moveable.h"
#include "pong/physics/i_collider.h"
#include "pong/render/i_renderable.h"
#include "pong/utils/time.h"

#include <glm/vec2.hpp>

#include <memory>
#include <string>

namespace sf
{
class Sprite;
}

namespace pong
{

class MoveManager;
class PhysicsManager;
class RenderManager;

class Actor : public IRenderable, public IMoveable, public ICollider
{
public:
	Actor(RenderManager& render_manager, PhysicsManager& physics_manager, int layer);
	Actor(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer);
	virtual ~Actor();

	//IMoveable
	void Update(const time::Duration& delta_time) override;
	void SetPosition(glm::vec2 position) override;
	const glm::vec2& GetPosition() const override;
	void Move(const glm::vec2& move) override;

	const glm::vec2& GetLastFrameDisplacementVector() const override;

	//IRenderable
	void Render() override;
	void SetTexture(sf::Texture* texture);

	//ICollider
	void SetSize(glm::vec2 size);
	const glm::vec2& GetSize() const override;
	void OnCollided(const ICollider& other) override;
	bool IsKinematic() const override;
	void SetKinematic(bool kinematic);
	BoundingBox GetBoundingBox() const override;
	glm::vec2 GetNormal() const override;
	void SetNormal(glm::vec2 normal);

protected:
	virtual void UpdateImpl(const time::Duration& delta_time) = 0;

	std::unique_ptr<sf::Sprite> m_sprite;
	glm::vec2 m_size{ 0,0 };
	bool m_kinematic{ false };
	glm::vec2 m_normal{ 0, 0 };
	glm::vec2 m_last_frame_displacement_vector{ glm::vec2{0,0} };
};
}
