#pragma once

#include "Texture.h"
#include "Types.h"
#include "static_string.h"

namespace sf
{
class TextureLoaderBase
{
public:
	TextureLoaderBase(const sf::AssetExtension& iExtension);
	virtual ~TextureLoaderBase();

public:
	const sf::AssetExtension& getExtension() const;

public:
	virtual void loadTexture(const sf::AssetPath& filename, sf::Texture& iTexture) = 0;

private:
	sf::AssetExtension extension_;
};
}
