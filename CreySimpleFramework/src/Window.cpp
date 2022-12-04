
#include "Window.h"

namespace sf
{
Window::~Window() = default;

void Window::setup(const sf::u32 iWidth, const sf::u32 iHeight, const static_string< 512 >& iTitle)
{
	windowWidth_ = iWidth;
	windowHeight_ = iHeight;
	title_ = iTitle;
}

const bool Window::createWindow()
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window_ = glfwCreateWindow(windowWidth_, windowHeight_, title_.toChar(), NULL, NULL);
	return window_;
}

const sf::u32 Window::getWindowWidth() const
{
	return windowWidth_;
}

const sf::u32 Window::getWindowHeight() const
{
	return windowHeight_;
}

GLFWwindow* Window::getGLFWWindow() const
{
	return window_;
}
}
