#include "cMap.h"
#include <string>
#include <sstream>
#include <algorithm>
#include "cLog.h"
#include "Utils.h"
#include "cGame.h"

#undef max

using namespace util;

cMap::cMap() :
	m_originRow(0),
	m_originCol(0),
	m_visibleRows(SCREEN_RES_Y / cCell::tileHeight),
	m_visibleCols(SCREEN_RES_X / cCell::tileWidth),
	m_totalRows(0),
	m_totalCols(0)
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

void cMap::update()
{
	if (cGame::Instance()->Input.KeyDown(DIK_O) && m_originCol + m_visibleCols < m_totalCols)
	{
		m_originCol++;
	}

	if (cGame::Instance()->Input.KeyDown(DIK_I) && m_originCol > 0)
	{
		m_originCol--;
	}

	if (cGame::Instance()->Input.KeyDown(DIK_L) && m_originRow + m_visibleRows < m_totalRows)
	{
		m_originRow++;
	}

	if (cGame::Instance()->Input.KeyDown(DIK_K) && m_originRow > 0)
	{
		m_originRow--;
	}

	//const cPlayer& player = cGame::Instance()->Scene->m_player;
	//cRectangle playerRect = player.GetCollisionRectAbsolute();

	//if (playerRect.x != m_lastPlayerRect.x || playerRect.y != m_lastPlayerRect.y)
	//{
	//	s32 playerRow = (playerRect.y / cCell::tileHeight) + m_originRow;
	//	s32 playerCol = (playerRect.x / cCell::tileWidth) + m_originCol;

	//	cRectangle destRect = playerRect;
	//	s32 colOffset = 0, rowOffset = 0;

	//	if ((playerCol > m_originCol + (m_visibleCols / 2) + 1) && (m_originCol + m_visibleCols < m_totalCols) &&
	//		(player.GetCurrentOrientation() == ORIENTATION_NE || player.GetCurrentOrientation() == ORIENTATION_SE || player.GetCurrentOrientation() == ORIENTATION_E))
	//	{
	//		colOffset++;
	//	}

	//	if ((playerCol < m_originCol + (m_visibleCols / 2) - 1) && (m_originCol > 0) &&
	//		(player.GetCurrentOrientation() == ORIENTATION_NO || player.GetCurrentOrientation() == ORIENTATION_SO || player.GetCurrentOrientation() == ORIENTATION_O))
	//	{
	//		colOffset--;
	//	}

	//	if ((playerRow > m_originRow + (m_visibleRows / 2) + 1) && (m_originRow + m_visibleRows < m_totalRows) &&
	//		(player.GetCurrentOrientation() == ORIENTATION_SO || player.GetCurrentOrientation() == ORIENTATION_SE || player.GetCurrentOrientation() == ORIENTATION_S))
	//	{
	//		rowOffset++;
	//	}

	//	if ((playerRow < m_originRow + (m_visibleRows / 2) - 1) && (m_originRow > 0) &&
	//		(player.GetCurrentOrientation() == ORIENTATION_NO || player.GetCurrentOrientation() == ORIENTATION_NE || player.GetCurrentOrientation() == ORIENTATION_N))
	//	{
	//		rowOffset--;
	//	}

	//	if (colOffset || rowOffset)
	//	{
	//		destRect.x += colOffset * cCell::tileWidth;
	//		destRect.y += rowOffset * cCell::tileHeight;

	//		if (isWalkable(destRect))
	//		{
	//			m_originCol += colOffset;
	//			m_originRow += rowOffset;

	//			s32 enemyX, enemyY;
	//			cEnemyPersecutor& enemy = cGame::Instance()->Scene->m_enemy;
	//			enemy.GetPosition(enemyX, enemyY);
	//			enemyX += (colOffset * cCell::tileWidth * -1);
	//			enemyY += (rowOffset * cCell::tileHeight * -1);
	//			enemy.SetPosition(enemyX, enemyY);
	//		}
	//	}

	//	m_lastPlayerRect = playerRect;
	//}

	for (s32 row = m_originRow; row <= m_originRow + m_visibleRows; row++)
	{
		for (s32 col = m_originCol; col <= m_originCol + m_visibleCols; col++)
		{
			if (cCell* const cell = getCell(row, col))
			{
				cell->update();
			}
		}
	}
}

void cMap::render()
{
	for (s32 row = m_originRow, y = 0; row <= m_originRow + m_visibleRows; row++, y += cCell::tileHeight)
	{
		for (s32 col = m_originCol, x = 0; col <= m_originCol + m_visibleCols; col++, x += cCell::tileWidth)
		{
			if (cCell* const cell = getCell(row, col))
			{
				cell->SetPosition(x, y);
				cell->render();
			}
		}
	}
}

std::string cMap::getCellDebugString(u32 row, u32 col)
{
	cCell* const cell = getCell(row, col);

	if (!cell)
	{
		fatalError("getCellDebugString: row " + toString(row) + " col " + toString(col) + " out of bounds");
	}

	return cell->toString();
}

void cMap::toCellCoord(s32 x, s32 y, s32* row, s32* col) const
{
	*row = y / cCell::tileHeight;
	*col = x / cCell::tileWidth;
}

bool cMap::insideLimits(const cRectangle& position)
{
	bool inside = false;

	const s32 limitX = m_totalCols * cCell::tileWidth;
	const s32 limitY = m_totalRows * cCell::tileHeight;

	if (position.x >= 0 && position.x <= limitX && position.y >= 0 && position.y <= limitY)
	{
		inside = true;
	}

	return inside;
}

bool cMap::isWalkable(const cRectangle& position) const
{
	return isWalkableFor(position, m_originRow, m_originCol);
}

bool cMap::movePlayer(const cRectangle& position)
{
	const cPlayer& player = cGame::Instance()->Scene->m_player;
	cRectangle playerRect = player.GetCollisionRectAbsolute();	

	s32 playerRow = (playerRect.y / cCell::tileHeight) + m_originRow;
	s32 playerCol = (playerRect.x / cCell::tileWidth) + m_originCol;

	cRectangle destRect = playerRect;
	s32 colOffset = 0, rowOffset = 0;

	if ((playerCol > m_originCol + (m_visibleCols / 2) + 1) && (m_originCol + m_visibleCols < m_totalCols) &&
		(player.GetCurrentOrientation() == ORIENTATION_NE || player.GetCurrentOrientation() == ORIENTATION_SE || player.GetCurrentOrientation() == ORIENTATION_E))
	{
		colOffset++;
	}

	if ((playerCol < m_originCol + (m_visibleCols / 2) - 1) && (m_originCol > 0) &&
		(player.GetCurrentOrientation() == ORIENTATION_NO || player.GetCurrentOrientation() == ORIENTATION_SO || player.GetCurrentOrientation() == ORIENTATION_O))
	{
		colOffset--;
	}

	if ((playerRow > m_originRow + (m_visibleRows / 2) + 1) && (m_originRow + m_visibleRows < m_totalRows) &&
		(player.GetCurrentOrientation() == ORIENTATION_SO || player.GetCurrentOrientation() == ORIENTATION_SE || player.GetCurrentOrientation() == ORIENTATION_S))
	{
		rowOffset++;
	}

	if ((playerRow < m_originRow + (m_visibleRows / 2) - 1) && (m_originRow > 0) &&
		(player.GetCurrentOrientation() == ORIENTATION_NO || player.GetCurrentOrientation() == ORIENTATION_NE || player.GetCurrentOrientation() == ORIENTATION_N))
	{
		rowOffset--;
	}

	if (colOffset || rowOffset)
	{
		//destRect.x += colOffset * cCell::tileWidth;
		//destRect.y += rowOffset * cCell::tileHeight;

		if (isWalkableFor(playerRect, m_originRow + rowOffset, m_originCol + colOffset))
		{
			m_originCol += colOffset;
			m_originRow += rowOffset;

			s32 enemyX, enemyY;
			cEnemyPersecutor& enemy = cGame::Instance()->Scene->m_enemy;
			enemy.GetPosition(enemyX, enemyY);
			enemyX += (colOffset * cCell::tileWidth * -1);
			enemyY += (rowOffset * cCell::tileHeight * -1);
			enemy.SetPosition(enemyX, enemyY);

			return false;
		}
	}
	else
	{
		if (insideLimits(position) && isWalkable(position))
		{
			return true;
		}
	}

	return false;
}

bool cMap::moveEnemy(const cRectangle& position)
{
	bool moveOk = false;

	if (insideLimits(position) && isWalkable(position))
	{
		moveOk = true;
	}

	return moveOk;
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
	m_originRow = m_originCol = m_totalRows = m_totalCols = 0;
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

		m_totalRows = std::max(currentRow, m_totalRows);
		m_totalCols = std::max(currentCol, m_totalCols);

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

bool cMap::isWalkableFor(const cRectangle& position, s32 originRow, s32 originCol) const
{
	bool walkable = true;

	s32 firstRow = (position.y / cCell::tileHeight) + originRow;
	s32 firstCol = (position.x / cCell::tileWidth) + originCol;
	s32 lastRow = ((position.y + position.h) / cCell::tileHeight) + originRow;
	s32 lastCol = ((position.x + position.w) / cCell::tileWidth) + originCol;

	for (s32 row = firstRow; walkable && row <= lastRow; row++)
	{
		for (s32 col = firstCol; walkable && col <= lastCol; col++)
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
