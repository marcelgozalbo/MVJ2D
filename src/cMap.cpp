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

void cMap::reset()
{
	m_originRow = 0;
	m_originCol = 0;
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
	cPlayer& player = cGame::Instance()->Scene->m_player;

	cRectangle playerRect = player.GetCollisionRectAbsolute();

	s32 playerPosX, playerPosY;
	player.GetPosition(playerPosX, playerPosY);

	s32 playerRow = (playerPosY / cCell::tileHeight) + m_originRow;
	s32 playerCol = (playerPosX / cCell::tileWidth) + m_originCol;

	bool moveOk = true;
	eMovementDirection direction = DIRECTION_NONE;

	//#todo: dibuixar algo al voltant de tot el mapa pq no surti negre

	if (playerCol == (m_originCol + m_visibleCols - 2) && (
		player.GetCurrentOrientation() == ORIENTATION_E || player.GetCurrentOrientation() == ORIENTATION_NE || player.GetCurrentOrientation() == ORIENTATION_SE))
	{
		if (m_originCol + m_visibleCols < m_totalCols)
		{
			// jugador al seguent tros de mapa
			s32 futurePos = cCell::tileWidth;
			player.SetPosition(futurePos, playerPosY);
			cRectangle futureRect = player.GetCollisionRectAbsolute();

			// si el podem posar
			if (isWalkableFor(futureRect, m_originRow, m_originCol + m_visibleCols))
			{
				// mostrem seguent tros de mapa
				m_originCol += m_visibleCols;
				//player.SetPosition(rect.x, rect.y);
				direction = DIRECTION_EAST;
				playerPosX = futurePos;
			}
			else
			{
				// recuperem posicio anterior
				player.SetPosition(playerPosX, playerPosY);
				moveOk = true;
			}
		}
	}
	else if (playerCol == m_originCol && (
		player.GetCurrentOrientation() == ORIENTATION_O || player.GetCurrentOrientation() == ORIENTATION_NO || player.GetCurrentOrientation() == ORIENTATION_SO))
	{
		if (m_originCol - m_visibleCols >= 0)
		{
			s32 futurePos = SCREEN_RES_X - cCell::tileWidth - playerRect.w;
			player.SetPosition(futurePos, playerPosY);
			cRectangle futureRect = player.GetCollisionRectAbsolute();

			if (isWalkableFor(futureRect, m_originRow, m_originCol - m_visibleCols))
			{
				m_originCol -= m_visibleCols;
				direction = DIRECTION_WEST;
				playerPosX = futurePos;
			}
			else
			{
				// recuperem posicio
				player.SetPosition(playerPosX, playerPosY);
				moveOk = false;
			}
		}
	}

	if (moveOk)
	{
		if (playerRow == (m_originRow + m_visibleRows - 2) && (
			player.GetCurrentOrientation() == ORIENTATION_S || player.GetCurrentOrientation() == ORIENTATION_SO || player.GetCurrentOrientation() == ORIENTATION_SE))
		{
			if (m_originRow + m_visibleRows < m_totalRows)
			{
				// jugador al seguent tros de mapa
				s32 futurePos = cCell::tileHeight;			
				player.SetPosition(playerPosX, futurePos);
				cRectangle futureRect = player.GetCollisionRectAbsolute();

				if (isWalkableFor(futureRect, m_originRow + m_visibleRows, m_originCol))
				{
					// mostrem seguent tros de mapa
					m_originRow += m_visibleRows;
					direction = DIRECTION_SOUTH;
				}
				else
				{
					//recuperem posicio
					player.SetPosition(playerPosX, playerPosY);
				}
			}
		}
		else if (playerRow == m_originRow && (
			player.GetCurrentOrientation() == ORIENTATION_N || player.GetCurrentOrientation() == ORIENTATION_NO || player.GetCurrentOrientation() == ORIENTATION_NE))
		{
			if (m_originRow - m_visibleRows >= 0)
			{
				s32 futurePos = SCREEN_RES_Y - cCell::tileHeight - playerRect.h;
				player.SetPosition(playerPosX, futurePos);
				cRectangle futureRect = player.GetCollisionRectAbsolute();

				if (isWalkableFor(futureRect, m_originRow - m_visibleRows, m_originCol))
				{
					m_originRow -= m_visibleRows;
					direction = DIRECTION_NORTH;
				}
				else
				{
					player.SetPosition(playerPosX, playerPosY);
				}
			}
		}
	}

	repositionEnemies(direction);

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

bool cMap::insideScreen(const cRectangle& position)
{
	bool inside = false;

	s32 row = position.y / cCell::tileHeight;
	s32 col = position.x / cCell::tileWidth;

	if (row >= m_originRow && row <= m_originRow + m_visibleRows && col >= m_originCol && col <= m_originCol + m_visibleCols)
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
	return moveEnemy(position);
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
					u32 strIndex = 10;

					cCell::tFrameVec frameVec;
					frameVec.reserve(frameCount);

					for (u32 idx = 0; idx < frameCount; idx++)
					{
						u32 framePosX = hexStrTo<u32>(line, strIndex, strIndex + 2);
						u32 framePosY = hexStrTo<u32>(line, strIndex + 2, strIndex + 4);
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

void cMap::repositionEnemies(eMovementDirection direction)
{
	std::vector<cEnemyPersecutor>& enemies = cGame::Instance()->Scene->m_enemies;

	for (u32 idx = 0; idx < enemies.size(); idx++)
	{
		cEnemyPersecutor& enemy = enemies[idx];

		s32 enemyX, enemyY;
		enemy.GetPosition(enemyX, enemyY);

		switch (direction)
		{
		case DIRECTION_EAST:
			enemyX -= m_visibleCols * cCell::tileWidth;
			break;

		case DIRECTION_WEST:
			enemyX += m_visibleCols * cCell::tileWidth;
			break;

		case DIRECTION_SOUTH:
			enemyY -= m_visibleRows * cCell::tileHeight;
			break;

		case DIRECTION_NORTH:
			enemyY += m_visibleRows * cCell::tileHeight;
			break;
		}

		enemy.SetPosition(enemyX, enemyY);
		enemy.UpdatePatrolRectangle();
	}
}

int* cMap::getVisibleCells()
{
	s32 cellCount = m_visibleRows * m_visibleCols;
	s32* map = new s32[cellCount];
	s32 idx = 0;

	for (s32 row = m_originRow; row < m_originRow + m_visibleRows; row++)
	{
		for (s32 col = m_originCol; col < m_originCol + m_visibleCols; col++, idx++)
		{
			if (cCell* const cell = getCell(row, col))
			{
				if (cell->isWalkable())
				{
					map[idx] = 1;
				}
				else
				{
					map[idx] = 0;
				}
			}
			else
			{
				map[idx] = 0;
			}
		}
	}

	return map;
}

void cMap::getLimits(s32* limitX, s32* limitY)
{
	*limitX = m_totalCols * cCell::tileWidth;
	*limitY = m_totalRows * cCell::tileHeight;
}
