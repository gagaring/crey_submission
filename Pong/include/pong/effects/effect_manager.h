#pragma once

#include "pong/utils/time.h"

#include <memory>

namespace pong
{

class Ball;
class BallEffect;
class RenderManager;

class EffectManager
{
public:
	EffectManager(const Ball& ball, RenderManager& render_manager);
	~EffectManager();

	void Update();

private:
	std::unique_ptr<BallEffect> m_ball_effect;
};

}
