#include "pong/pong.h"

#include "pong/actors/actor_manager.h"
#include "pong/actors/ball.h"
#include "pong/actors/racket.h"

#include "pong/character/ai.h"
#include "pong/character/player.h"

#include "pong/effects/effect_manager.h"
#include "pong/input/input_manager.h"
#include "pong/game/game_controller.h"
#include "pong/move/move_manager.h"
#include "pong/physics/physics_manager.h"
#include "pong/render/layers.h"
#include "pong/render/render_manager.h"
#include "pong/scoreboard/scoreboard.h"

#include "pong/utils/config_reader.h"

#include "Framework.h"
#include "InputManager.h"
#include "Window.h"

#include <glm/vec2.hpp>

namespace pong
{

Pong::Pong() = default;
Pong::~Pong() = default;

void Pong::preInit(sf::Framework<Pong>& framework)
{
	m_actor_manager = std::make_unique<ActorManager>();
	m_input_manager = std::make_unique<InputManager>(framework.getInputManager());
	m_move_manager = std::make_unique<MoveManager>();
	m_physics_manager = std::make_unique<PhysicsManager>();
	m_render_manager = std::make_unique<RenderManager>(framework.getTextureManager());
}

void Pong::postInit(sf::Framework<Pong>& framework)
{
	auto window = framework.getWindow();

	CreateWalls(window);
	auto game_config = config::ReadFromFile("asset/game_config.json");
	CreatePlayer(game_config, glm::vec2{10, window.getWindowHeight() / 2});
	auto* ball = CreateBall(game_config, glm::vec2{ window.getWindowWidth() / 2, window.getWindowHeight() / 2 }, glm::vec2{ -1,1 });
	CreateAI(game_config, glm::vec2{ window.getWindowWidth() - 10, window.getWindowHeight() / 2 }, *ball, window.getWindowWidth());
	m_scoreboard = std::make_unique<Scoreboard>(*m_render_manager, 
		glm::vec2{ window.getWindowWidth() / 2, window.getWindowHeight() - 96 }, 
		m_render_manager->GetLayers().m_scoreboard);
	m_game_controller = std::make_unique<GameController>(*ball, *m_player, *m_ai, *m_scoreboard);
	m_effect_manager = std::make_unique<EffectManager>(*ball, *m_render_manager);
}

void Pong::step(sf::Framework<Pong>& framework)
{
	auto delta_time = GetDeltaTime();

	glClearColor(m_base_color.r, m_base_color.g, m_base_color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_input_manager->Update();
	m_move_manager->Update(delta_time);
	m_physics_manager->Update();
	m_ai->Update();
	m_effect_manager->Update();
	m_render_manager->Render();
	m_game_controller->Update();
}

time::Duration Pong::GetDeltaTime()
{
	if (m_first_frame)
	{
		m_current_time = time::Now();
		m_first_frame = false;
		return time::Duration{ 0 };
	}
	auto last_frame{ m_current_time };
	m_current_time = time::Now();
	return m_current_time.time_since_epoch() - last_frame.time_since_epoch();
}

void Pong::CreatePlayer(const rapidjson::Document& config, glm::vec2 position)
{
	auto* racket = m_actor_manager->CreateActor<Racket>(*m_render_manager, *m_physics_manager,*m_move_manager, m_render_manager->GetLayers().m_player);
	racket->SetTexture(m_render_manager->GetTexture("racket"));
	m_player = std::make_unique<Player>(*racket, Character::Config{ config }, position, 1.f);
	m_input_manager->RegisterInput("up", [=](bool pressed) { m_player->OnUpPressed(pressed); });
	m_input_manager->RegisterInput("down", [=](bool pressed) { m_player->OnDownPressed(pressed); });
}

void Pong::CreateAI(const rapidjson::Document& config, glm::vec2 position, const Ball& ball, sf::u32 level_width)
{
	auto* racket = m_actor_manager->CreateActor<Racket>(*m_render_manager, *m_physics_manager, *m_move_manager, m_render_manager->GetLayers().m_ai);
	racket->SetTexture(m_render_manager->GetTexture("racket"));
	m_ai = std::make_unique<AI>(*racket, AI::Config{ config }, position, ball, level_width, -1.f);
}

Ball* Pong::CreateBall(const rapidjson::Document& config, glm::vec2 position, glm::vec2 direction)
{
	auto* ball = m_actor_manager->CreateActor<Ball>(*m_render_manager, *m_physics_manager, *m_move_manager, m_render_manager->GetLayers().m_ball);
	ball->SetTexture(m_render_manager->GetTexture("ball"));
	ball->SetConfig(Ball::Config{ config });
	ball->SetDirection(direction);
	ball->SetDefaultPosition(position);
	return ball;
}

void Pong::CreateWalls(sf::Window& window)
{
	float half_width = window.getWindowWidth() * 0.5f;
	auto wall = CreateWall();
	wall->SetPosition(glm::vec2(half_width, 10));
	wall->SetNormal(glm::vec2{ 0, 1 });
	wall = CreateWall();
	wall->SetPosition(glm::vec2(half_width, window.getWindowHeight() - 10));
	wall->SetNormal(glm::vec2{ 0, -1 });
}

Wall* Pong::CreateWall()
{
	auto* wall = m_actor_manager->CreateActor<Wall>(*m_render_manager, *m_physics_manager, m_render_manager->GetLayers().m_player);
	wall->SetTexture(m_render_manager->GetTexture("wall"));
	return wall;
}

}
