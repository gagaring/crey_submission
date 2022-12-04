#pragma once

#include "pong/render/i_renderable.h"

#include <glm/vec2.hpp>

#include <memory>

namespace sf
{
class Sprite;
}

namespace pong
{

class ScoreNumber : public IRenderable
{
public:
	ScoreNumber();
	~ScoreNumber() override;
	void Render() override;
	void SetPosition(glm::vec2 position);
	void SetTexture(sf::Texture* texture);

private:

	const std::unique_ptr<sf::Sprite> m_sprite;
};

}
