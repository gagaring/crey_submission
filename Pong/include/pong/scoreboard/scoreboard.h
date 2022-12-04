#pragma once

#include <glm/vec2.hpp>

#include <memory>
#include <utility>
#include <vector>

namespace pong
{

class RenderManager;
class ScoreNumber;

class Scoreboard
{
public:
	Scoreboard(RenderManager& render_manager, glm::vec2 position, int layer);
	~Scoreboard();

	void Reset();
	void SetScore(int left, int right);

private:
	void CreateNumbers(RenderManager& render_manager, int layer);
	std::unique_ptr<ScoreNumber> CreateNumber(RenderManager& render_manager, int layer, bool left);
	void CreateColon(RenderManager& render_manager, int layer);

	RenderManager& m_render_manager;

	std::unique_ptr<ScoreNumber> m_left;
	std::unique_ptr<ScoreNumber> m_right;
	std::unique_ptr<ScoreNumber> m_colon;

	glm::vec2 m_position;
	int m_left_active{ 0 };
	int m_right_active{ 0 };
};

}
