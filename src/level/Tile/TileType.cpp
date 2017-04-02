#include "TileType.h"

#include "../../util/FileUtil.h"
#include "../../util/json.hpp"

namespace Level{ namespace Tile
{
    Type::Type(std::string&& fileName)
	{
		using json = nlohmann::json;
     
		std::string source = getFileContents("res/tiles/" + fileName + ".json");
		json json_ = json::parse(source.c_str());

		m_data.name = json_["Name"].get<std::string>();

		m_data.id = static_cast<ID>(json_["ID"].get<int>());

		m_data.textureVariations = json_["Variation"].get<int>();

		auto uv = json_["Texture"].get<std::vector<short>>();
		m_data.texCoords.x = uv[0];
		m_data.texCoords.y = uv[1];
    }

    const Type::Data& Type::getData() const
    {
        return m_data;
    }
}}
