#include "pong/character/ai.h"

#include "pong/actors/ball.h"
#include "pong/actors/racket.h"

#include <exception>

namespace pong
{

AI::Config::Config(const rapidjson::Document& json)
	: Character::Config(json)
{
	m_difficulty = FromString(json["ai"]["difficulty"].GetString());
}

AI::Difficulty AI::Config::FromString(const std::string& from) const
{
	if (from == "beginner")
	{
		return Difficulty::Beginner;
	}
	if (from == "medium")
	{
		return Difficulty::Medium;
	}
	if (from == "hard")
	{
		return Difficulty::Hard;
	}
	throw std::exception(("unknown difficulty: " + from).c_str());
}

AI::AI(Racket& racket, Config config, glm::vec2 default_pos, const Ball& ball, sf::u32 level_width, float normal_x)
	: Character(racket, config, default_pos, normal_x)
	, m_ball{ ball }
	, m_difficulty{ config.m_difficulty }
	, m_level_width{ level_width }
{
}

AI::~AI() = default;

void AI::Update()
{
	auto diff = m_ball.GetPosition() - m_racket.GetPosition();
	if (!IsActive(diff.x))
	{
		m_racket.SetDirection(MoveDirection::None);
		return;
	}
	if (abs(diff.y) < 0.01f)
	{
		m_racket.SetDirection(MoveDirection::None);
		return;
	}
	m_racket.SetDirection(diff.y > 0 ? MoveDirection::Up : MoveDirection::Down);
}

bool AI::IsActive(float ball_distance) const
{
	float distance_percent = abs(ball_distance/ m_level_width);
	switch (m_difficulty)
	{
	case pong::AI::Difficulty::Beginner:
		return distance_percent < 0.10f && m_ball.GetLastFrameDisplacementVector().x > 0;
	case pong::AI::Difficulty::Medium:
		return distance_percent < 0.25f && m_ball.GetLastFrameDisplacementVector().x > 0;
	case pong::AI::Difficulty::Hard:
		return true;
	}
	return true;
}

}
