#include "pong/render/render_manager.h"

#include "pong/render/i_renderable.h"

#include "pong/utils/config_reader.h"

#include "Texture.h"
#include "TextureManager.h"
#include "TGATextureLoader.h"

namespace pong
{

RenderManager::RenderManager(sf::TextureManager& texture_manager)
	: m_texture_manager{ texture_manager }
	, m_layers{ Layers{config::ReadFromFile("asset/layer_config.json")} }
{
	m_texture_manager.registerTextureLoader< sf::TGATextureLoader >("tga");
}

RenderManager::~RenderManager() = default;

void RenderManager::Register(IRenderable* renderable, int layer)
{
	m_layer_map[layer].push_back(renderable);
}

sf::Texture* RenderManager::GetTexture(const std::string& texture)
{
	return m_texture_manager.getTexture(texture.c_str());
}

const Layers& RenderManager::GetLayers() const
{
	return m_layers;
}

void RenderManager::Render()
{
	for (auto& layer : m_layer_map)
	{
		for (auto* renderable : layer.second)
		{
			renderable->Render();
		}
	}
}

}
