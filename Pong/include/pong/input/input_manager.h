#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

namespace sf
{
class InputManager;
}

namespace pong
{
class InputManager
{
public:
	InputManager(sf::InputManager& input_manager);
	virtual ~InputManager();

	void RegisterInput(std::string key, std::function<void(bool)> callback);

	void Update() const;

private:
	void UpdateInput(const std::string& key, const std::vector<std::function<void(bool)>>& callbacks) const;

	sf::InputManager& m_input_manager;
	std::unordered_map<std::string, std::vector<std::function<void(bool)>>> m_input_map;
};

}
