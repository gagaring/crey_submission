#include "pong/scoreboard/score_number.h"

#include "Sprite.h"

namespace pong
{

ScoreNumber::ScoreNumber()
	: m_sprite{ std::make_unique<sf::Sprite>() }
{
}

ScoreNumber::~ScoreNumber() = default;

void ScoreNumber::Render()
{
	m_sprite->render();
}

void ScoreNumber::SetTexture(sf::Texture* texture)
{
	m_sprite->setTexture(texture);
}

void ScoreNumber::SetPosition(glm::vec2 position)
{
	m_sprite->setPosition(std::move(position));
}

}
