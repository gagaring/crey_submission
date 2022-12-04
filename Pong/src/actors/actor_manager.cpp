#include "pong/actors/actor_manager.h"

#include "pong/actors/actor.h"

#include <exception>

namespace pong
{
ActorManager::~ActorManager() = default;


std::string ActorManager::ToString(Type type) const
{
	switch (type)
	{
	case Type::Racket:
		return "Racket";
	}
	return "Unknown type: " + static_cast<int>(type);
}

}
