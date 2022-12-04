#include "pong/physics/physics_manager.h"

#include "pong/physics/bounding_box.h"
#include "pong/physics/i_collider.h"

#include "pong/move/i_moveable.h"

#include <exception>

namespace pong
{

PhysicsManager::~PhysicsManager() = default;

void PhysicsManager::Register(ICollider* collider)
{
	if (collider->IsKinematic())
	{
		m_kinematics.push_back(collider);
	}
	else
	{
		m_dynamics.push_back(collider);
	}
}

void PhysicsManager::Update() const
{
	for (size_t i = 0; i < m_dynamics.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < m_dynamics.size(); ++j)
		{
			CheckCollision(*m_dynamics[i], *m_dynamics[j]);
		}
		CheckCollisionWithKimenatics(*m_dynamics[i]);
	}

	CheckCollisionWithKimenatics(*m_dynamics.back());
}

void PhysicsManager::CheckCollisionWithKimenatics(ICollider& collider) const
{
	for (auto* kinematic : m_kinematics)
	{
		CheckCollision(collider, *kinematic);
	}
}

void PhysicsManager::CheckCollision(ICollider& collider1, ICollider& collider2) const
{
	if (!IsCollided(collider1, collider2))
	{
		return;
	}
	FixPositions(collider1, collider2);
	collider1.OnCollided(collider2);
	collider2.OnCollided(collider1);
}

void PhysicsManager::FixPositions(ICollider& collider1, ICollider& collider2) const
{
	FixPosition(collider1);
	FixPosition(collider2);
}

void PhysicsManager::FixPosition(ICollider& collider) const
{
	if (collider.IsKinematic())
	{
		return;
	}
	auto moveable = dynamic_cast<IMoveable*>(&collider);
	if (!moveable)
	{
		throw std::exception("Dynamic collider has to be imovable");
	}
	auto move_direction = moveable->GetLastFrameDisplacementVector();
	moveable->SetPosition(moveable->GetPosition() - move_direction);
}

bool PhysicsManager::IsCollided(const ICollider& collider1, const ICollider& collider2) const
{
	auto bb1 = collider1.GetBoundingBox();
	auto bb2 = collider2.GetBoundingBox();
	return IsOverlap(bb1, bb2);
}

bool PhysicsManager::IsOverlap(const BoundingBox& box1, const BoundingBox& box2) const
{
	return IsOverlap(box1.m_left, box1.m_right, box2.m_left, box2.m_right) &&
		IsOverlap(box1.m_bottom, box1.m_top, box2.m_bottom, box2.m_top);
}

bool PhysicsManager::IsOverlap(float min1, float max1, float min2, float max2) const
{
	return max1 >= min2 && max2 >= min1;
}

}
