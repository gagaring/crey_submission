#include "pong/scoreboard/scoreboard.h"

#include "pong/scoreboard/score_number.h"

#include "pong/render/render_manager.h"

namespace pong
{

Scoreboard::Scoreboard(RenderManager& render_manager, glm::vec2 position, int layer)
	: m_render_manager{ render_manager }
	, m_position{ position }
{
	CreateNumbers(render_manager, layer);
	CreateColon(render_manager, layer);
}

Scoreboard::~Scoreboard() = default;

void Scoreboard::CreateNumbers(RenderManager& render_manager, int layer)
{
	m_left = CreateNumber(render_manager, layer, true);
	m_right = CreateNumber(render_manager, layer, false);
}

std::unique_ptr<ScoreNumber> Scoreboard::CreateNumber(RenderManager& render_manager, int layer, bool left)
{
	auto score_number = std::make_unique<ScoreNumber>();
	score_number->SetTexture(render_manager.GetTexture("number0"));
	render_manager.Register(score_number.get(), layer);
	auto pos = m_position;
	pos.x += left ? -64 : 64;
	score_number->SetPosition(std::move(pos));
	return score_number;
}

void Scoreboard::CreateColon(RenderManager& render_manager, int layer)
{
	m_colon = std::make_unique<ScoreNumber>();
	m_colon->SetTexture(render_manager.GetTexture("colon"));
	render_manager.Register(m_colon.get(), layer);
	m_colon->SetPosition(m_position);
}

void Scoreboard::Reset()
{
	SetScore(0, 0);
}

void Scoreboard::SetScore(int left, int right)
{
	while(left > 9)
	{
		left -= 10;
	}
	while(right > 9)
	{
		right -= 10;
	}
	m_left->SetTexture(m_render_manager.GetTexture("number" + std::to_string(left)));
	m_right->SetTexture(m_render_manager.GetTexture("number" + std::to_string(right)));
}

}
