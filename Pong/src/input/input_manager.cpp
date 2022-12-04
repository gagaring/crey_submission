#include "pong/input/input_manager.h"

#include "InputManager.h"

namespace pong
{

InputManager::~InputManager() = default;

InputManager::InputManager(sf::InputManager& input_manager)
	: m_input_manager{input_manager}
{
}

void InputManager::RegisterInput(std::string key, std::function<void(bool)> callback)
{
	m_input_map[key].push_back(callback);
}

void InputManager::Update() const
{
	for (auto& input : m_input_map)
	{
		UpdateInput(input.first, input.second);
	}
}

void InputManager::UpdateInput(const std::string& key, const std::vector<std::function<void(bool)>>& callbacks) const
{
	bool pressed;
	if (m_input_manager.isPressed(key.c_str()) || m_input_manager.isRepeat(key.c_str()))
	{
		pressed = true;
	}
	else if (m_input_manager.isReleased(key.c_str()))
	{
		pressed = false;
	}
	else
	{
		return;
	}

	for (auto& callback : callbacks)
	{
		callback(pressed);
	}
}

}
