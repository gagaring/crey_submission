#pragma once

#include "pong/render/layers.h"

#include <map>
#include <string>
#include <vector>

namespace sf
{
class Texture;
class TextureManager;
}

namespace pong
{
class IRenderable;

class RenderManager
{
public:
	RenderManager(sf::TextureManager& texture_manager);
	~RenderManager();

	void Register(IRenderable* renderable, int layer);

	sf::Texture* GetTexture(const std::string& texture);

	void Render();

	const Layers& GetLayers() const;

private:
	sf::TextureManager& m_texture_manager;
	Layers m_layers;
	std::map<int, std::vector<IRenderable*>> m_layer_map;
};

}
