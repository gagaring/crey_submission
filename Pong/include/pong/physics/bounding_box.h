#pragma once

#include <glm/vec2.hpp>

namespace pong
{
struct BoundingBox
{
	BoundingBox() = default;
	BoundingBox(const glm::vec2& position, const glm::vec2& size)
	{
		float half_size_x = size.x * 0.5f;
		float half_size_y = size.y * 0.5f;
		m_left = position.x - half_size_x;
		m_right = position.x + half_size_x;
		m_bottom = position.y - half_size_y;
		m_top = position.y + half_size_y;
	}
	float m_left{ 0 };
	float m_right{ 0 };
	float m_bottom{ 0 };
	float m_top{ 0 };
};

}
