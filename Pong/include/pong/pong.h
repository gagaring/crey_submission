#pragma once

#include "Framework.h"
#include "Types.h"

#include "pong/utils/time.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <rapidjson/document.h>

#include <memory>

namespace sf {
class Window;
}

namespace pong
{

class AI;
class ActorManager;
class Ball;
class EffectManager;
class GameController;
class InputManager;
class MoveManager;
class PhysicsManager;
class Player;
class RenderManager;
class Scoreboard;
class Wall;

struct Layers;

class Pong
{
public:
	Pong();
	~Pong();

public:
	void preInit(sf::Framework<Pong>& framework);
	void postInit(sf::Framework<Pong>& framework);
	void step(sf::Framework<Pong>& framework);

private:
	void CreateAI(const rapidjson::Document& config, glm::vec2 position, const Ball& ball, sf::u32 level_width);
	Ball* CreateBall(const rapidjson::Document& config, glm::vec2 position, glm::vec2 direction);
	void CreatePlayer(const rapidjson::Document& config, glm::vec2 position);
	void CreateWalls(sf::Window& window);
	Wall* CreateWall();

	time::Duration GetDeltaTime();

	std::unique_ptr<ActorManager> m_actor_manager;
	std::unique_ptr<EffectManager> m_effect_manager;
	std::unique_ptr<InputManager> m_input_manager;
	std::unique_ptr<MoveManager> m_move_manager;
	std::unique_ptr<RenderManager> m_render_manager;
	std::unique_ptr<PhysicsManager> m_physics_manager;
	std::unique_ptr<GameController> m_game_controller;
	std::unique_ptr<Scoreboard> m_scoreboard;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<AI> m_ai;

	const glm::vec3 m_base_color = { 0.0f, 0.0f, 0.0f };

	bool m_first_frame{ true };
	time::TimePoint m_current_time;
};

}
