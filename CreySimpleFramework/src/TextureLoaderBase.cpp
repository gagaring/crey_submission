#include "TextureLoaderBase.h"

namespace sf
{

TextureLoaderBase::~TextureLoaderBase() = default;

TextureLoaderBase::TextureLoaderBase(const sf::AssetExtension& iExtension)
	: extension_(iExtension)
{

}

const sf::AssetExtension& TextureLoaderBase::getExtension() const
{
	return extension_;
}

}
