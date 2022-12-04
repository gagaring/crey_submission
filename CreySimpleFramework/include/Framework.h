#pragma once

#include "Types.h"

#include "static_string.h"

#include <memory>
#include <vector>

namespace sf
{
class Window;
class InputManager;
class TextureManager;

template< typename TGAME >
class Framework
{
private:
	struct Asset
	{
		AssetTag 	asset_tag_;
		AssetPath 	filename_;
	};

public:
	Framework();
	~Framework();
	Framework(const Framework&) = delete;
	Framework& operator=(const Framework&) = delete;

public:
	const bool init();
	void loop();
	void terminate();

	bool loadJSONConfig(std::vector< Asset >& oAssetList);
	void loadTextures(std::vector< Asset >& iAssetList);
	const Window& getWindow() const;
	TextureManager& getTextureManager();
	InputManager& getInputManager();

private:
	std::unique_ptr<Window> window_;
	std::unique_ptr<TGAME> game_;
	std::unique_ptr<TextureManager> textureManager_;
	std::unique_ptr<InputManager> inputManager_;
};
}

#include "Framework.hpp"
