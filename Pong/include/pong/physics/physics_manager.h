#pragma once

#include "pong/utils/time.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <vector>

namespace pong
{
struct BoundingBox;

class ICollider;

class PhysicsManager 
{
public:
	~PhysicsManager();

	void Register(ICollider* collider);
	void Update() const;

private:
	void CheckCollision(ICollider& collider1, ICollider& collider2) const;
	void CheckCollisionWithKimenatics(ICollider& collider) const;
	bool IsCollided(const ICollider& collider1, const ICollider& collider2) const;

	bool IsOverlap(const BoundingBox& box1, const BoundingBox& box2) const;
	bool IsOverlap(float min1, float max1, float min2, float max2) const;

	void FixPositions(ICollider& collider1, ICollider& collider2) const;
	void FixPosition(ICollider& collider) const;

	std::vector<ICollider*> m_dynamics;
	std::vector<ICollider*> m_kinematics;
};

}
