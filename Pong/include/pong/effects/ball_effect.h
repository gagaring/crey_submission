#pragma once

#include "pong/render/i_renderable.h"

#include <glm/vec2.hpp>

#include <deque>
#include <memory>
#include <vector>

namespace sf
{
class Sprite;
}

namespace pong
{

class Ball;
class RenderManager;

class BallEffect : public IRenderable
{
public:
	BallEffect(const Ball& ball, RenderManager& render_manager);
	~BallEffect();

	void Update();
	void Reset();

	void Render() override;

private:
	std::unique_ptr<sf::Sprite> CreateParticle(RenderManager& render_manager, int number);

	const Ball& m_ball;
	std::deque<glm::vec2> m_ball_positions;
	std::vector<std::unique_ptr<sf::Sprite>> m_particles;

};
}
