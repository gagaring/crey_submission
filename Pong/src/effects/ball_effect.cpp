#include "pong/effects/ball_effect.h"

#include "pong/actors/ball.h"

#include "pong/render/render_manager.h"

#include "Sprite.h"

namespace pong
{

BallEffect::BallEffect(const Ball& ball, RenderManager& render_manager)
	: m_ball{ ball }
{
	m_particles.push_back(CreateParticle(render_manager, 1));
	m_particles.push_back(CreateParticle(render_manager, 2));
	m_particles.push_back(CreateParticle(render_manager, 3));
	render_manager.Register(this, render_manager.GetLayers().m_ball_effect);
	Reset();
}

BallEffect::~BallEffect() = default;

std::unique_ptr<sf::Sprite> BallEffect::CreateParticle(RenderManager& render_manager, int number)
{
	auto sprite = std::make_unique<sf::Sprite>();
	sprite->setTexture(render_manager.GetTexture("ball_effect" + std::to_string(number)));
	return sprite;
}

void BallEffect::Update()
{
	const int distances[] = { 100, 49, 25 };
	float distance = 0;
	int current_index = 0;
	auto prev_pos = m_ball.GetPosition();
	size_t remove_from = -1;
	for (size_t i = 0; i < m_ball_positions.size(); ++i)
	{
		float diff_x = prev_pos.x - m_ball_positions[i].x;
		float diff_y = prev_pos.y - m_ball_positions[i].x;
		distance += diff_x * diff_x + diff_y * diff_y;
		if (distance < distances[current_index])
		{
			continue;
		}
		m_particles[current_index]->setPosition(m_ball_positions[i]);
		if (++current_index == 3)
		{
			remove_from = i + 1;
			break;
		}
	}
	if (remove_from != -1 && remove_from < m_ball_positions.size())
	{
		m_ball_positions.erase(m_ball_positions.begin() + remove_from, m_ball_positions.end());
	}
	m_ball_positions.push_front(m_ball.GetPosition());

}

void BallEffect::Reset()
{
	for (auto& particle : m_particles)
	{
		particle->setPosition(glm::vec2(-64, -64));
	}

}

void BallEffect::Render()
{
	for (auto& particle : m_particles)
	{
		particle->render();
	}
}

}
