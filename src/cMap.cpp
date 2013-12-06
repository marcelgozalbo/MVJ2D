#include "cMap.h"
#include <string>
#include <sstream>
#include "cLog.h"
#include "Utils.h"

cMap::cMap()
{

}

cMap::~cMap()
{
	clear();
}

void cMap::load(const std::string& _filePath)
{
	std::ifstream file;

	clear();
	file.open(_filePath.c_str(), std::ifstream::in);

	if (file.good())
	{
		loadAnimations(file);
		loadMap(file);
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

bool cMap::isWalkable(int x, int y) const
{
	bool walkable = false;
	unsigned int row = y / cCell::tileHeight;
	unsigned int col = x / cCell::tileWidth;

	if (row < m_grid.size())
	{
		const tRow& gridRow = m_grid[row];

		if (col < gridRow.size())
		{
			cCell* const cell = gridRow[col];

			walkable = cell->isWalkable();
		}
	}

	return walkable;
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
	m_animations.clear();
}

void cMap::loadAnimations(std::ifstream& file)
{
	std::string line;
	bool finished = false;

	while (!finished)
	{
		if (std::getline(file, line))
		{
			if (line.empty())
			{
				finished = true;
			}
			else
			{
				unsigned int cellId = charTo<unsigned int>(line[0]);
				bool walkable = charTo<bool>(line[2]);
				unsigned int frameCount = charTo<unsigned int>(line[4]);
				unsigned int strIndex = 6;

				cCell::tFrameVec frameVec;
				frameVec.reserve(frameCount);
				
				for (unsigned int idx = 0; idx < frameCount; idx++)
				{
					unsigned int frameId = charTo<unsigned int>(line[strIndex]);
					unsigned int duration = charTo<unsigned int>(line[strIndex + 2]);
					strIndex += 4;

					frameVec.push_back(cCell::sFrameInfo(frameId, duration));
				}

				if (frameVec.empty())
				{
					fatalError("frame vector empty for cellId " + toString(cellId));
				}

				auto it = m_animations.find(cellId);

				if (it == m_animations.end())
				{
					m_animations.emplace_hint(it, tAnimations::value_type(cellId, cCell::sCellInfo(frameVec, walkable)));
				}
				else
				{
					fatalError("cellId " + toString(cellId) + " is duplicated");
				}
			}
		}
	}
}

void cMap::loadMap(std::ifstream& file)
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

				tAnimations::iterator it = m_animations.find(cellId);

				if (it != m_animations.end())
				{
					const cCell::sCellInfo& cellInfo = it->second;

					m_grid.back().push_back(new cCell(currentRow, currentCol, cellInfo));
				}
				else
				{
					fatalError("unknown cellId: " + toString(cellId) + " on row " + toString(currentRow) + " and column " + toString(currentCol));
				}

				currentCol++;
			}
		}

		currentRow++;
		currentCol = 0;
	}
}

void cMap::fatalError(const std::string& errorText)
{
	LOG(errorText);
	throw std::runtime_error(errorText);
}
