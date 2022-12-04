#pragma once

namespace sf
{
class Texture;
}

namespace pong
{
class IRenderable
{
public:
	virtual ~IRenderable() = default;

	virtual void Render() = 0;
};

}
