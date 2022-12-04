#pragma once

namespace pong
{

class Ball;
class Character;
class Scoreboard;

class GameController
{
public:
	GameController(Ball& ball, Character& player, Character& ai, Scoreboard& scoreboard);
	~GameController();

	void Update();

private:
	int CalculatePlayerGoalPos();
	int CalculateAIGoalPos();
	void ResetMatch(bool player_point);
	void OnScoreChanged();

	Ball& m_ball;
	Character& m_player;
	Character& m_ai;
	Scoreboard& m_scoreboard;

	int m_player_goal_x;
	int m_ai_goal_x;

	int m_player_point{ 0 };
	int m_ai_point{ 0 };
};

}
