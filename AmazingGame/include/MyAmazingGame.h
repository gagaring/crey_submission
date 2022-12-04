#pragma once

#include "Framework.h"
#include "Sprite.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class MyAmazingGame
{
public:
	~MyAmazingGame();

public:
	void preInit(sf::Framework< MyAmazingGame >& iFramework);
	void postInit(sf::Framework< MyAmazingGame >& iFramework);
	void step(sf::Framework< MyAmazingGame >& iFramework);

private:
	const glm::vec3 color = { 0.0f, 0.0f, 0.0f };
	const glm::vec2 velHornet = { 2.0f, 2.0f };
	glm::vec2 basePos_{ 0, 0 };
	sf::Sprite spHornet_;
	sf::Sprite spLayer01_;
	sf::Sprite spLayer02_;
	sf::Sprite spLayer03_;
	sf::Sprite spLayer04_;
	sf::Sprite spLayer05_;
	sf::Sprite spRotatingObject_;
	sf::Sprite spBoom_;
};
