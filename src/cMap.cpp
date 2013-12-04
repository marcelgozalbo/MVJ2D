#include "cMap.h"
#include "cGame.h"
#include <string>
#include <sstream>

//#define ARRAY_SIZEOF(arr) (sizeof(arr)/sizeof(arr[0]))

cMap::tWalkability cMap::walkability = { true, false };

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
				unsigned int cellId;
				std::stringstream ss;

				ss << character;
				ss >> cellId;

				if (cellId < walkability.size())
				{
					m_grid.back().push_back(new cCell(currentRow, currentCol, walkability[cellId]));
				}
				else
				{
					throw std::runtime_error("unknown cellId: " + toString(cellId) + "on row " + toString(currentRow) + " and column " + toString(currentCol));
				}

				currentCol++;
			}

			currentRow++;
		}
	}

	file.close();
}

void cMap::render()
{
	cGraphicsLayer* Graphics = cGame::Instance()->Graphics;

	for (auto& row : m_grid)
	{
		for (auto* cell : row)
		{
			cell->Render();
		}
	}
}

void cMap::update()
{

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
}