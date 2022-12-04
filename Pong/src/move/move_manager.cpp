#include "pong/move/move_manager.h"

#include "pong/move/i_moveable.h"

namespace pong
{

MoveManager::~MoveManager() = default;

void MoveManager::Register(IMoveable* moveable)
{
	m_moveables.push_back(moveable);
}

void MoveManager::Update(const time::Duration& delta_time)
{
	for (auto* moveable : m_moveables)
	{
		moveable->Update(delta_time);
	}
}

}
