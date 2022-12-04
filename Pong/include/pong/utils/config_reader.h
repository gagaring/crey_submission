#pragma once

#include <rapidjson/document.h>

#include <string>

namespace pong::config
{

rapidjson::Document ReadFromFile(const std::string& path);

}
