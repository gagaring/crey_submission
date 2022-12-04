#pragma once

#include <glm/vec2.hpp>

#include <rapidjson/document.h>

namespace pong
{

class Ball;
class Racket;

class Character
{
public:
	struct Config
	{
		Config(const rapidjson::Document& json);
		float m_speed;
		glm::vec2 m_size;
	};

	Character(Racket& racket, Config config, glm::vec2 default_pos, float normal);
	~Character();

	void Reset();

	const Racket& GetRacket() const;

protected:
	Racket& m_racket;
	glm::vec2 m_default_position;

};

}
