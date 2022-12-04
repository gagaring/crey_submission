#pragma once

#include "pong/utils/time.h"

#include <glm/vec2.hpp>

namespace pong
{
class IMoveable
{
public:
	virtual ~IMoveable() = default;

	virtual void Update(const time::Duration& delta_time) = 0;

	virtual void SetPosition(glm::vec2 position) = 0;
	virtual const glm::vec2& GetPosition() const = 0;
	virtual void Move(const glm::vec2& move) = 0;

	virtual const glm::vec2& GetSize() const = 0;

	virtual const glm::vec2& GetLastFrameDisplacementVector() const = 0;
};

}
