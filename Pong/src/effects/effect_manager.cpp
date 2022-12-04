#include "pong/effects/effect_manager.h"

#include "pong/effects/ball_effect.h"

#include "pong/actors/ball.h"
#include "pong/render/layers.h"

namespace pong
{

EffectManager::EffectManager(const Ball& ball, RenderManager& render_manager)
	: m_ball_effect{std::make_unique<BallEffect>(ball, render_manager)}
{
}

EffectManager::~EffectManager() = default;

void EffectManager::Update()
{
	m_ball_effect->Update();
}

}
