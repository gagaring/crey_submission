#include "pong/utils/config_reader.h"

#include "rapidjson/filereadstream.h"

#include <exception>
#include <fstream>
#include <string>

namespace pong::config
{

rapidjson::Document ReadFromFile(const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	const bool result = file.is_open();
	if (!result)
	{
		throw std::exception(("File not found: " + path).c_str());
	}
	rapidjson::Document doc;
	{
		file.seekg(0, std::ios_base::beg);
		file.seekg(0, std::ios::end);
		size_t fsize = file.tellg();
		file.seekg(0, std::ios_base::beg);
		char* data = new char[fsize];
		file.read((char*)data, fsize);
		file.close();

		doc.Parse< rapidjson::kParseStopWhenDoneFlag >(data);
		delete[] data;
	}
	return doc;
}

}
