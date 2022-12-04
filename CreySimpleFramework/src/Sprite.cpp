#include "Sprite.h"

namespace sf
{

Sprite::~Sprite() = default;

void Sprite::setTexture(sf::Texture* iTexture, const sf::s32 iNumTileX /*= 1*/, const sf::s32 iNumTileY /*= 1*/)
{
	texture_ = iTexture;
	numTileX_ = iNumTileX;
	numTileY_ = iNumTileY;
	setTile(0, 0);
}

void Sprite::setTile(const sf::s32 iTileX, const sf::s32 iTileY)
{
	tileX_ = iTileX;
	tileY_ = iTileY;
}

void Sprite::setAngle(const float iAngleInDegrees)
{
	angle_ = iAngleInDegrees;
}

float Sprite::getAngle() const
{
	return angle_;
}

void Sprite::setRenderFlag(const sf::RenderFlag iRenderFlag)
{
	renderFlag_ = iRenderFlag;
}

void Sprite::setPosition(glm::vec2 iPosition)
{
	position_ = std::move(iPosition);
}

const glm::vec2& Sprite::getPosition() const
{
	return position_;
}

void Sprite::render()
{
	SFASSERT(texture_ != nullptr);
	const float tileWidth = static_cast<float>(texture_->getWidth()) / numTileX_;
	const float tileHeight = static_cast<float>(texture_->getHeight()) / numTileY_;
	const float sx = tileWidth * tileX_;
	const float sy = tileHeight * tileY_;
	const float dx = sx + tileWidth;
	const float dy = sy + tileHeight;
	texture_->renderTexture(position_, renderFlag_, angle_, sx, sy, dx, dy);
}

} // namespace sf
