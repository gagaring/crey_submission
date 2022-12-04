#pragma once

#include "pong/utils/time.h"

#include <glm/vec2.hpp>

#include <vector>

namespace pong
{
class IMoveable;

class MoveManager
{
public:
	~MoveManager();

	void Register(IMoveable* moveable);
	void Update(const time::Duration& delta_time);

private:
	std::vector<IMoveable*> m_moveables;
};

}
