#include "pong/character/player.h"
#include "pong/actors/racket.h"

namespace pong
{

Player::Player(Racket& racket, Config config, glm::vec2 default_pos, float normal_x)
	: Character(racket, config, default_pos, normal_x)
{
}

Player::~Player() = default;

void Player::OnUpPressed(bool pressed)
{
	m_racket.SetDirection(pressed ? MoveDirection::Up : MoveDirection::None);
}

void Player::OnDownPressed(bool pressed)
{
	m_racket.SetDirection(pressed ? MoveDirection::Down : MoveDirection::None);
}

}
