#pragma once

#include <glm/vec2.hpp>

namespace pong
{

struct BoundingBox;

class ICollider
{
public:
	virtual ~ICollider() = default;

	virtual void OnCollided(const ICollider& other) = 0;
	virtual bool IsKinematic() const = 0;
	virtual BoundingBox GetBoundingBox() const = 0;
	virtual glm::vec2 GetNormal() const = 0;
};

}
