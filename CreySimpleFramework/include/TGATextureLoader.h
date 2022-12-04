#pragma once

#include "TextureLoaderBase.h"

namespace sf
{
class TGATextureLoader : public sf::TextureLoaderBase
{
public:
	TGATextureLoader(const sf::AssetExtension& iExtension);
	~TGATextureLoader() override;

public:
	virtual void loadTexture(const sf::AssetPath& iFilename, sf::Texture& iTexture) override;
};
}
