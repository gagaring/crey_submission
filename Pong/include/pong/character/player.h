#pragma once

#include "pong/character/character.h"

#include <glm/vec2.hpp>

#include <string>

namespace pong
{

class Racket;

class Player : public Character
{
public:
	Player(Racket& racket, Config config, glm::vec2 default_pos, float normal_x);
	~Player();

	void OnUpPressed(bool pressed);
	void OnDownPressed(bool pressed);
private:
};

}
