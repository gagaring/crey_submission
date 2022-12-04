#pragma once

#include "pong/character/character.h"

#include "Types.h"

#include <glm/vec2.hpp>

#include <string>

namespace pong
{

class Ball;
class Racket;

class AI : public Character
{
public:
	enum class Difficulty
	{
		Beginner,
		Medium,
		Hard
	};

	struct Config : public Character::Config
	{
	public:
		Config(const rapidjson::Document& json);
		Difficulty m_difficulty;

	private:
		Difficulty FromString(const std::string& from) const;
	};

public:
	AI(Racket& racket, Config config, glm::vec2 default_pos, const Ball& ball, sf::u32 level_width, float normal_x);
	~AI();

	void Update();
	
private:
	bool IsActive(float ball_distance) const;
	const Ball& m_ball;
	
	Difficulty m_difficulty;
	sf::u32 m_level_width;
};

}
