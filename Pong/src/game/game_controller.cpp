#include "pong/game/game_controller.h"

#include "pong/actors/ball.h"
#include "pong/actors/racket.h"
#include "pong/character/character.h"
#include "pong/scoreboard/scoreboard.h"

namespace pong
{

GameController::GameController(Ball& ball, Character& player, Character& ai, Scoreboard& scoreboard)
	: m_ball{ ball }
	, m_player{ player }
	, m_ai{ ai }
	, m_scoreboard{ scoreboard }
	, m_player_goal_x{ CalculatePlayerGoalPos() }
	, m_ai_goal_x{ CalculateAIGoalPos() }
{
}

GameController::~GameController() = default;

void GameController::Update()
{
	auto ball_x = m_ball.GetPosition().x;
	if (ball_x <= m_player_goal_x)
	{
		++m_ai_point;
		OnScoreChanged();
		ResetMatch(false);
	}
	else if (ball_x >= m_ai_goal_x)
	{
		++m_player_point;
		OnScoreChanged();
		ResetMatch(true);
	}
}

void GameController::ResetMatch(bool player_point)
{
	m_ball.Reset();
	m_ai.Reset();
	m_player.Reset();
	m_ball.SetDirection(glm::vec2{ 1, player_point ? 1 : -1 });
}

int GameController::CalculatePlayerGoalPos()
{
	return static_cast<int>(m_player.GetRacket().GetPosition().x + m_player.GetRacket().GetSize().x * 0.5f + m_ball.GetSize().x * 0.5f) - 1;
}

int GameController::CalculateAIGoalPos()
{
	return static_cast<int>(m_ai.GetRacket().GetPosition().x - m_ai.GetRacket().GetSize().x * 0.5f - m_ball.GetSize().x * 0.5f) + 1;
}

void GameController::OnScoreChanged()
{
	m_scoreboard.SetScore(m_player_point, m_ai_point);
}


}
