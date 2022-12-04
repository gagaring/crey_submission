#pragma once

#include "Types.h"

#include "static_string.h"

#include <GLFW/glfw3.h>

namespace sf
{
class Window
{
public:
	Window() = default;
	~Window();

public:
	void setup(const sf::u32 iWidth, const sf::u32 iHeight, const static_string< 512 >& iTitle);
	const bool createWindow();
	const sf::u32 getWindowWidth() const;
	const sf::u32 getWindowHeight() const;
	GLFWwindow* getGLFWWindow() const;

private:
	GLFWwindow* window_{ nullptr };
	sf::u32					windowWidth_{ 0 };
	sf::u32					windowHeight_{ 0 };
	static_string< 512 >	title_{ "" };
};
}
