#include "Framework.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "Window.h"

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>

#include <fstream>

namespace sf
{
template< typename TGAME >
Framework< TGAME >::Framework()
	: window_{ std::make_unique< Window>() }
	, game_{ std::make_unique< TGAME >() }
	, textureManager_{ std::make_unique< TextureManager >() }
	, inputManager_{ std::make_unique<InputManager>() }
{}

template< typename TGAME >
Framework< TGAME >::~Framework() = default;

template< typename TGAME >
const bool Framework< TGAME >::init()
{
	SFLOG("Initializing Crey Simple Framework...\n");
	std::vector< Asset > assetList;
	const bool ret = loadJSONConfig(assetList);
	SFASSERT(ret);
	if (!ret)
	{
		SFLOG("Could not find config.json\n");
		return false;
	}
	if (!glfwInit())
	{
		return false;
	}

	if (!window_->createWindow())
	{
		return false;
	}
	glfwMakeContextCurrent(window_->getGLFWWindow());

	game_->preInit(*this);

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_->getWindowWidth(), 0, window_->getWindowHeight(), -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSetWindowUserPointer(window_->getGLFWWindow(), this);
	auto keyHandler = [](GLFWwindow* iWindow, int iKey, int iScancode, int iAction, int iMods)
	{
		static_cast<Framework< TGAME >*>(glfwGetWindowUserPointer(iWindow))->inputManager_->handleKey(iKey, iScancode, iAction, iMods);
	};
	glfwSetKeyCallback(window_->getGLFWWindow(), keyHandler);

	auto cursorPosHandler = [](GLFWwindow* iWindow, double xpos, double ypos)
	{
		Framework< TGAME >* fw = static_cast<Framework< TGAME >*>(glfwGetWindowUserPointer(iWindow));
		ypos = fw->getWindow().getWindowHeight() - ypos;
		ypos = (ypos < 0) ? 0 : ((ypos > fw->getWindow().getWindowHeight()) ? fw->getWindow().getWindowHeight() : ypos);
		xpos = (xpos < 0) ? 0 : ((xpos > fw->getWindow().getWindowWidth()) ? fw->getWindow().getWindowWidth() : xpos);
		fw->inputManager_->setMousePosition({ xpos, ypos });
	};
	glfwSetCursorPosCallback(window_->getGLFWWindow(), cursorPosHandler);
	loadTextures(assetList);

	game_->postInit(*this);
	return true;
}

template< typename TGAME >
void Framework< TGAME >::loop()
{
	constexpr double TICK = 1000.0 / 60.0 / 1000.0;
	double currentTick = glfwGetTime();
	double nextTick = currentTick + TICK;
	while (!glfwWindowShouldClose(window_->getGLFWWindow()))
	{
		currentTick = glfwGetTime();
		if (currentTick >= nextTick)
		{
			nextTick = currentTick + TICK;
			game_->step(*this);
			inputManager_->step();
			glfwSwapBuffers(window_->getGLFWWindow());
			glfwPollEvents();
		}
	}
}

template< typename TGAME >
void Framework< TGAME >::terminate()
{
	SFLOG("Terminating Crey Simple Framework...\n");
	glfwTerminate();
}

template< typename TGAME >
bool Framework< TGAME >::loadJSONConfig(std::vector< Asset >& oAssetList)
{
	std::ifstream file("asset/config.json", std::ios::binary);
	const bool result = file.is_open();
	SFASSERT(result);
	if (!result)
	{
		return false;
	}
	rapidjson::Document doc;
	{
		file.seekg(0, std::ios_base::beg);
		file.seekg(0, std::ios::end);
		size_t fsize = file.tellg();
		SFASSERT(fsize > 0);
		file.seekg(0, std::ios_base::beg);
		char* data = new char[fsize];
		SFASSERT(data);
		file.read((char*)data, fsize);
		file.close();

		doc.Parse< rapidjson::kParseStopWhenDoneFlag >(data);
		delete[] data;
	}
	SFASSERT(!doc.HasParseError());
	SFASSERT(doc.HasMember("window"));
	SFASSERT(doc.HasMember("textures"));
	u32 width = doc["window"]["width"].GetUint();
	u32 height = doc["window"]["height"].GetUint();
	static_string< 512 > title = doc["window"]["title"].GetString();
	window_->setup(width, height, title);

	for (u32 i = 0; i < doc["textures"].Size(); ++i)
	{
		const char* tag = doc["textures"][i]["tag"].GetString();
		const char* filename = doc["textures"][i]["file"].GetString();
		Asset asset;
		asset.asset_tag_ = tag;
		asset.filename_.set(filename);
		oAssetList.push_back(asset);
	}
	SFASSERT(doc.HasMember("input"));
	for (u32 i = 0; i < doc["input"].Size(); ++i)
	{
		const char* tag = doc["input"][i]["tag"].GetString();
		const int keycode = doc["input"][i]["keycode"].GetInt();
		InputTag inputTag(tag, keycode);
		inputManager_->registerInputTag(inputTag);
	}

	return true;
}

template< typename TGAME >
void Framework< TGAME >::loadTextures(std::vector< Asset >& iAssetList)
{
	for (u32 i = 0; i < iAssetList.size(); ++i)
	{
		textureManager_->loadTexture(iAssetList[i].asset_tag_, iAssetList[i].filename_);
	}
}

template< typename TGAME >
const Window& Framework< TGAME >::getWindow() const
{
	return *window_;
}

template< typename TGAME >
TextureManager& Framework< TGAME >::getTextureManager()
{
	return *textureManager_;
}

template< typename TGAME >
InputManager& Framework< TGAME >::getInputManager()
{
	return *inputManager_;
}

}
