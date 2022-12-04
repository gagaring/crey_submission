#pragma once

#include <rapidjson/document.h>

namespace pong
{
struct Layers
{
public:
	Layers(const rapidjson::Document& doc)
		: m_ai{ GetLayer(doc, "ai") }
		, m_ball{ GetLayer(doc, "ball") }
		, m_ball_effect{ GetLayer(doc, "ball_effect") }
		, m_player{ GetLayer(doc, "player") }
		, m_scoreboard{ GetLayer(doc, "scoreboard") }
		, m_wall{ GetLayer(doc, "wall") }
	{
	}

	const int m_ai;
	const int m_ball;
	const int m_ball_effect;
	const int m_player;
	const int m_scoreboard;
	const int m_wall;
	
private:
	int GetLayer(const rapidjson::Document& doc, const char* name)
	{
		return doc[name].GetInt();
	}
};

}
