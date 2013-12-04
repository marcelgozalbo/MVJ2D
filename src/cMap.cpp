#include "cMap.h"
#include <string>
#include <sstream>

cMap::tWalkability cMap::walkability = { true, false, true, true };

template <typename T>
std::string toString(T in)
{
	std::stringstream ss;

	ss << in;
	return ss.str();
}

cMap::cMap()
{

}

cMap::~cMap()
{

}

void cMap::load(const std::string& _filePath)
{
	std::ifstream file;

	clear();
	file.open(_filePath.c_str(), std::ifstream::in);

	if (file.good())
	{
		int currentRow = 0;
		int currentCol = 0;
		std::string line;

		while (std::getline(file, line))
		{
			m_grid.push_back(tRow());

			for (auto character : line)
			{
				if (character != ' ')
				{
					unsigned int cellId;
					std::stringstream ss;

					ss << character;
					ss >> cellId;

					if (cellId < walkability.size())
					{
						m_grid.back().push_back(new cCell(currentRow, currentCol, cellId, walkability[cellId]));
					}
					else
					{
						std::string message = "unknown cellId: " + toString(cellId) + " on row " + toString(currentRow) + " and column " + toString(currentCol);
						throw std::runtime_error(message);
					}

					currentCol++;
				}
			}

			currentRow++;
			currentCol = 0;
		}
	}

	file.close();
}

void cMap::render()
{
	for (auto& row : m_grid)
	{
		for (auto* cell : row)
		{
			cell->render();
		}
	}
}

void cMap::update()
{
	for (auto& row : m_grid)
	{
		for (auto* cell : row)
		{
			cell->update();
		}
	}
}

void cMap::clear()
{
	for (auto& row : m_grid)
	{
		for (auto* cell : row)
		{
			delete cell;
		}
	}

	m_grid.clear();
}
