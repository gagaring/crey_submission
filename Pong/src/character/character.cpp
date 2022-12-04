#include "pong/character/character.h"

#include "pong/actors/racket.h"

namespace pong
{

Character::Config::Config(const rapidjson::Document& json)
{
	m_speed = json["character"]["speed"].GetFloat();
	m_size.x = json["character"]["size_x"].GetFloat();
	m_size.y = json["character"]["size_y"].GetFloat();
}

Character::Character(Racket& racket, Config config, glm::vec2 default_pos, float normal_x)
	: m_racket{ racket }
	, m_default_position{ std::move(default_pos) }
{
	racket.SetSpeed(config.m_speed);
	racket.SetSize(config.m_size);
	racket.SetNormal(glm::vec2(normal_x, 0));

	Reset();
}

Character::~Character() = default;

void Character::Reset()
{
	m_racket.SetPosition(m_default_position);
	m_racket.SetDirection(MoveDirection::None);
}

const Racket& Character::GetRacket() const
{
	return m_racket;
}

}
