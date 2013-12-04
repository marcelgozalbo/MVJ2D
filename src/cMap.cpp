#include "cMap.h"
#include <sstream>

cMap::cMap()
{

}

cMap::~cMap()
{

}

void cMap::load(const std::string& _filePath)
{
	std::ifstream file;

	file.open(_filePath.c_str(), std::ifstream::in);

	if (file.good())
	{
		std::string line;

		while (std::getline(file, line))
		{
			m_grid.push_back(tRow());

			for (auto character : line)
			{
				int textureId;
				std::stringstream ss;

				ss << character;
				ss >> textureId;

				m_grid.back().push_back(textureId);
			}
		}
	}

	file.close();
}
