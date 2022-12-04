#pragma once

#include "pong/actors/ball.h"
#include "pong/actors/racket.h"
#include "pong/actors/wall.h"

#include <memory>
#include <string>
#include <vector>

namespace pong
{
class Actor;
class MoveManager;
class PhysicsManager;
class RenderManager;

class ActorManager
{
public:
	enum class Type
	{
		Player,
		Racket
	};

public:
	~ActorManager();

	template<class T>
	T* CreateActor(RenderManager& render_manager, PhysicsManager& physics_manager, int layer)
	{
		auto actor = std::make_unique<T>(render_manager, physics_manager, layer);
		T* ret_val = actor.get();
		m_actors.push_back(std::move(actor));
		return ret_val;
	}

	template<class T>
	T* CreateActor(RenderManager& render_manager, PhysicsManager& physics_manager, MoveManager& move_manager, int layer)
	{
		auto actor = std::make_unique<T>(render_manager, physics_manager, move_manager, layer);
		T* ret_val = actor.get();
		m_actors.push_back(std::move(actor));
		return ret_val;
	}

private:
	std::string ToString(Type type) const;
	std::vector<std::unique_ptr<Actor>> m_actors;
};

}
