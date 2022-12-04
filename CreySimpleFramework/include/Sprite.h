#pragma once

#include "Texture.h"

namespace sf
{
class Texture;

class Sprite
{
public:
	Sprite() = default;
	~Sprite();

public:
	void setTexture(sf::Texture* iTexture, const sf::s32 iNumTileX = 1, const sf::s32 iNumTileY = 1);
	void setTile(const sf::s32 iTileX, const sf::s32 iTileY);
	void setAngle(const float iAngleInDegrees);
	float getAngle() const;
	void setRenderFlag(const sf::RenderFlag iRenderFlag);
	void setPosition(glm::vec2 iPosition);
	const glm::vec2& getPosition() const;
	void render();

private:
	sf::Texture* texture_{ nullptr };
	float angle_{ 0.0f }; // degrees
	sf::RenderFlag renderFlag_{ sf::RenderFlag::NoEffect };
	sf::s32 numTileX_{ 0 };
	sf::s32 numTileY_{ 0 };
	sf::s32 tileX_{ 0 };
	sf::s32 tileY_{ 0 };
	glm::vec2 position_{ 0, 0 };
};
}