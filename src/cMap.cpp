#include "cMap.h"
#include <string>
#include <sstream>
#include "cLog.h"
#include "Utils.h"

using namespace util;

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

std::string cMap::getCellDebugString(u32 row, u32 col)
{
	cCell* const cell = getCell(row, col);

	if (!cell)
	{
		fatalError("getCellDebugString: row " + util::toString(row) + " col " + util::toString(col) + " out of bounds");
	}

	return cell->toString();
}

void cMap::toCellCoord(s32 x, s32 y, s32* row, s32* col)
{
	*row = y / cCell::tileHeight;
	*col = x / cCell::tileWidth;
}

bool cMap::isWalkable(const cRectangle& position) const
{
	bool walkable = true;

	const u32 firstRow = position.y / cCell::tileHeight;
	const u32 firstCol = position.x / cCell::tileWidth;
	const u32 lastRow = (position.y + position.h) / cCell::tileHeight;
	const u32 lastCol = (position.x + position.w) / cCell::tileWidth;

	for (u32 row = firstRow; walkable && row <= lastRow; row++)
	{
		for (u32 col = firstCol; walkable && col <= lastCol; col++)
		{
			if (cCell* const cell = getCell(row, col))
			{
				walkable = walkable && cell->isWalkable();
			}
			else
			{
				walkable = false;
			}
		}
	}

	return walkable;
}

u32 cMap::divAddRemainder(u32 dividend, u32 divisor)
{
	u32 result = dividend / divisor;

	if (dividend % divisor)
	{
		result++;
	}

	return result;
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
	std::string tileSet;
	bool finished = false;

	while (!finished)
	{
		if (std::getline(file, line))
		{
			if (line.empty())
			{
				finished = true;
			}
			else if (line[0] != '#')
			{
				if (line[0] == '>')
				{
					tileSet.assign(line.begin() + 1, line.end());
				}
				else
				{
					u32 cellId = hexStrTo<u32>(line, 0, 2);
					bool walkable = hexCharTo<bool>(line[3]);
					u32 duration = hexCharTo<u32>(line[5]);
					u32 z = hexCharTo<u32>(line[7]);
					u32 frameCount = hexCharTo<u32>(line[9]);
					u32 strIndex = 11;

					cCell::tFrameVec frameVec;
					frameVec.reserve(frameCount);

					for (u32 idx = 0; idx < frameCount; idx++)
					{
						u32 framePosX = hexCharTo<u32>(line[strIndex]);
						u32 framePosY = hexCharTo<u32>(line[strIndex + 2]);
						strIndex += 4;

						frameVec.push_back(cCell::sFrameInfo(framePosX, framePosY));
					}

					if (frameVec.empty())
					{
						fatalError("frame vector empty for cellId " + toString(cellId));
					}

					auto it = m_animations.find(cellId);

					if (it == m_animations.end())
					{
						m_animations.emplace_hint(it, tAnimations::value_type(cellId, cCell::sCellInfo(tileSet, frameVec, walkable, duration, z)));
					}
					else
					{
						fatalError("cellId " + toString(cellId) + " is duplicated");
					}
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

		for (u32 idx = 0; idx < line.size(); idx += 2)
		{
			u32 cellId = hexStrTo<u32>(line, idx, idx + 2);
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

		currentRow++;
		currentCol = 0;
	}
}

void cMap::fatalError(const std::string& errorText)
{
	LOG(errorText);
	throw std::runtime_error(errorText);
}

cCell* cMap::getCell(u32 row, u32 col) const
{
	cCell* cell = nullptr;

	if (row < m_grid.size())
	{
		const tRow& gridRow = m_grid[row];

		if (col < gridRow.size())
		{
			cell = gridRow[col];
		}
	}

	return cell;
}
