#include "cEnemyPersecutor.h"
#include "cGame.h"

cEnemyPersecutor::cEnemyPersecutor() :
cCharacter("enemies", cRectangle(0, 0, 60, 59), 0, 0, 10, 2, 0, 2.0f),
_state(IDLE),
_anim_frame_to_change(12),
_anim_curr_frame(0),
_movement(M_DOWN),
_attack_area(100),
_sound_action(0),
_sound_death(0)
{
	const u32 w = 60, h = 59;
	const u32 x0 = 12, x1 = x0 + w, x2 = x1 + w, x3 = x2 + w, x4 = x3 + w, x5 = x4 + w, x6 = x5 + w, x7 = x6 + w, x8 = x7 + w, x9 = x8 + w;
	const u32 y0 = 165, y1 = y0 + h, y2 = y1 + h, y3 = y2 + h;
	
	_left_animation.push_back(cRectangle(x0,	y0, w, h));
	_left_animation.push_back(cRectangle(x1,	y0, w, h));
	_left_animation.push_back(cRectangle(x2,	y0, w, h));
	_left_animation.push_back(cRectangle(x3,	y0, w, h));

	_attack_left_animation.push_back(cRectangle(x4, y0, w, h));
	_attack_left_animation.push_back(cRectangle(x5, y0, w, h));
	_attack_left_animation.push_back(cRectangle(x6, y0, w, h));
	_attack_left_animation.push_back(cRectangle(x7, y0, w, h));
	_attack_left_animation.push_back(cRectangle(x8, y0, w, h));
	_attack_left_animation.push_back(cRectangle(x9, y0, w, h));

	_up_animation.push_back(cRectangle(x0, y1, w, h));
	_up_animation.push_back(cRectangle(x1, y1, w, h));
	_up_animation.push_back(cRectangle(x2, y1, w, h));
	_up_animation.push_back(cRectangle(x3, y1, w, h));

	_attack_up_animation.push_back(cRectangle(x4, y1, w, h));
	_attack_up_animation.push_back(cRectangle(x5, y1, w, h));
	_attack_up_animation.push_back(cRectangle(x6, y1, w, h));
	_attack_up_animation.push_back(cRectangle(x7, y1, w, h));
	_attack_up_animation.push_back(cRectangle(x8, y1, w, h));
	_attack_up_animation.push_back(cRectangle(x9, y1, w, h));

	_right_animation.push_back(cRectangle(x0, y2, w, h));
	_right_animation.push_back(cRectangle(x1, y2, w, h));
	_right_animation.push_back(cRectangle(x2, y2, w, h));
	_right_animation.push_back(cRectangle(x3, y2, w, h));

	_attack_right_animation.push_back(cRectangle(x4, y2, w, h));
	_attack_right_animation.push_back(cRectangle(x5, y2, w, h));
	_attack_right_animation.push_back(cRectangle(x6, y2, w, h));
	_attack_right_animation.push_back(cRectangle(x7, y2, w, h));
	_attack_right_animation.push_back(cRectangle(x8, y2, w, h));
	_attack_right_animation.push_back(cRectangle(x9, y2, w, h));

	_down_animation.push_back(cRectangle(x0, y3, w, h));
	_down_animation.push_back(cRectangle(x1, y3, w, h));
	_down_animation.push_back(cRectangle(x2, y3, w, h));
	_down_animation.push_back(cRectangle(x3, y3, w, h));

	_attack_down_animation.push_back(cRectangle(x4, y3, w, h));
	_attack_down_animation.push_back(cRectangle(x5, y3, w, h));
	_attack_down_animation.push_back(cRectangle(x6, y3, w, h));
	_attack_down_animation.push_back(cRectangle(x7, y3, w, h));
	_attack_down_animation.push_back(cRectangle(x8, y3, w, h));
	_attack_down_animation.push_back(cRectangle(x9, y3, w, h));

	_death_animation.push_back(cRectangle(x0, 460, w, h));
	_death_animation.push_back(cRectangle(x1, 460, w, h));
	_death_animation.push_back(cRectangle(x2, 460, w, h));
	_death_animation.push_back(cRectangle(x3, 460, w, h));
	_death_animation.push_back(cRectangle(x4, 460, w, h));
	_death_animation.push_back(cRectangle(x5, 460, w, h));
	_death_animation.push_back(cRectangle(x6, 460, w, h));

	SetAnimationRects(_down_animation);
	SetAnimationFramesPerStep(2);
	EnableAnimation();


	cRectangle r(24, 24, 14, 16);
	SetCollisionRectRelative(r);

	EnableDebugMode();
}

cEnemyPersecutor::~cEnemyPersecutor()
{

}

void cEnemyPersecutor::Update()
{
	bool frameElapsed = false;

	if (_anim_curr_frame <= _anim_frame_to_change)
	{
		_anim_curr_frame++;
	}
	else
	{
		frameElapsed = true;
		_anim_curr_frame = 0;
	}

	switch (_state)
	{
		case IDLE:
			UpdateIdle();
			if (frameElapsed)
			{
				ChangeToPatrol();
			}
		break;
		case PATROL:
			UpdatePatrol();
			if (frameElapsed)
				ComputeNextMovement();
		break;
		case RUN:
			UpdateRun();
		break;
		case ACTION:
			UpdateAction();
		break;
		case DEATH:
		break;
	}

	cBaseEntity::Update();
}

void cEnemyPersecutor::Render()
{
	if (IsColDebugMode())
		RenderPatrolRectangle();
	
	cBaseEntity::Render();
}

void cEnemyPersecutor::Die()
{
	if (IsAlive())
		ChangeToDie();
}

void cEnemyPersecutor::UpdateIdle()
{
}

void cEnemyPersecutor::ChangeToIdle()
{
	SetPatrol(_patrol_rectangle.w, _patrol_rectangle.h);
	
	auto orient = GetCurrentOrientation();
	switch (orient)
	{
		case ORIENTATION_N:
		case ORIENTATION_NE:
		case ORIENTATION_NO:
			SetAnimationRects(_up_animation);
			break;
		case ORIENTATION_S:
		case ORIENTATION_SE:
		case ORIENTATION_SO:
			SetAnimationRects(_down_animation);
			break;
		case ORIENTATION_E:
			SetAnimationRects(_right_animation);
			break;
		case ORIENTATION_O:
			SetAnimationRects(_left_animation);
			break;
		default:
			break;
	}

	ResetAnimation();
	StopAnimation();
	_state = IDLE;
}

void cEnemyPersecutor::UpdatePatrol()
{
	// Comprovem si estem a l'abast de l'enemic
	s32 posx = GetCollisionRectAbsolute().x, posy = GetCollisionRectAbsolute().y, posplayerx = cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().x, posplayery = cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().y;

	double radi = sqrt((posplayerx - posx)*(posplayerx - posx) + (posplayery - posy)*(posplayery - posy));
	if (radi < _attack_area)
	{
		int* map = cGame::Instance()->Scene->m_map.getVisibleCells();
		Path.Make(map, posx / cCell::tileWidth, posy / cCell::tileHeight, posplayerx / cCell::tileWidth, posplayery / cCell::tileHeight);
		delete map;
		ChangeToRun();
		return;
	}
	
	// Comprovem si el seguent moviment surt dels limits de la patrulla
	s32 x = 0, y = 0;
	switch (_movement)
	{
	case M_DOWN:
		x = 0, y = 1;
		break;
	case M_UP:
		x = 0, y = -1;
		break;
	case M_LEFT:
		x = -1, y = 0;
		break;
	case M_RIGHT:
		x = 1, y = 0;
		break;
	}
	
	s32 pposx = 0, pposy = 0;
	cCharacter::PossibleMovement(x, y, pposx, pposy);
	if (!_patrol_rectangle.isInside(pposx, pposy))
	{
		ResetAnimation();
		StopAnimation();
	}
	else
	{
		DoMovement();
	}
}

void cEnemyPersecutor::ChangeToPatrol()
{
	ComputeNextMovement();
	PlayAnimation();
	_state = PATROL;
}

void cEnemyPersecutor::DoMovement()
{
	s32 x = 0, y = 0;
	switch (_movement)
	{
	case M_DOWN:
		x = 0, y = 1;
		break;
	case M_UP:
		x = 0, y = -1;
		break;
	case M_LEFT:
		x = -1, y = 0;
		break;
	case M_RIGHT:
		x = 1, y = 0;
		break;
	}

	// Si m'haig de moure
	if (x || y)
	{
		bool move = cCharacter::Move(x, y);
		if (GetLastOrientation() != GetCurrentOrientation())
		{
			auto orient = GetCurrentOrientation();
			switch (orient)
			{
			case ORIENTATION_N:
			case ORIENTATION_NE:
			case ORIENTATION_NO:
				SetAnimationRects(_up_animation);
				break;
			case ORIENTATION_S:
			case ORIENTATION_SE:
			case ORIENTATION_SO:
				SetAnimationRects(_down_animation);
				break;
			case ORIENTATION_E:
				SetAnimationRects(_right_animation);
				break;
			case ORIENTATION_O:
				SetAnimationRects(_left_animation);
				break;
			default:
				break;
			}
		}
		PlayAnimation();
	}
	else
	{
		ResetAnimation();
		StopAnimation();
	}
}

void cEnemyPersecutor::UpdateRun()
{	
	if (!Path.IsDone())
	{
		// Comprovem si estem a l'abast de l'enemic
		s32 posx = GetCollisionRectAbsolute().x, posy = GetCollisionRectAbsolute().y, posplayerx = cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().x, posplayery = cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().y;

		double radi = sqrt((posplayerx - posx)*(posplayerx - posx) + (posplayery - posy)*(posplayery - posy));
		if (radi > _attack_area)
		{
			Path.Done();
			ChangeToIdle();
			return;
		}

		s32 nposx = posx, nposy = posy, cx = posx / cCell::tileWidth, cy = posy / cCell::tileHeight;
		int mov = Path.NextStep(&nposx, &nposy, &cx, &cy);

		if (mov == ARRIVE)
		{
			Path.Done();
			ChangeToIdle();
		}
		else if (mov == CONTINUE)
		{
			// Comprovem la colisio amb el jugador
			if (HasCollision(cGame::Instance()->Scene->m_player))
			{
				ChangeToAction();
				return;
			}

			int xdiff = nposx - posx;
			int ydiff = nposy - posy;
			eMovement NewMovement = M_NOT_MOVE;
			if (xdiff > 0) NewMovement = M_RIGHT;
			else if (xdiff < 0) NewMovement = M_LEFT;
			if (NewMovement != M_NOT_MOVE)
			{
				_movement = NewMovement;
				DoMovement();
			}
			
			NewMovement = M_NOT_MOVE;
			if (ydiff > 0) NewMovement = M_DOWN;
			else if (ydiff < 0) NewMovement = M_UP;
			if (NewMovement != M_NOT_MOVE)
			{
				_movement = NewMovement;
				DoMovement();
			}
		}
	}
}

void cEnemyPersecutor::ChangeToRun()
{
	_state = RUN;
}

void cEnemyPersecutor::UpdateAction()
{
	cGame* game = cGame::Instance();
	cScene *sc = cGame::Instance()->Scene;

	//Renderitzo el rectangle a Z+1 perque surti per sobre la textura sempre
	int z;
	GetZIndex(z);
	cGame::Instance()->Graphics->DrawRect(m_attack_col_rect, 0x00FF00FF, z + 1);
	sc->UpdatePlayerHit(m_attack_col_rect);
	
	// Comprovem la colisio amb el jugador per si la perdem
	if (!HasCollision(cGame::Instance()->Scene->m_player))
	{
		ChangeToIdle();
		return;
	}
}

void cEnemyPersecutor::ChangeToAction()
{
	// Calculem la orientacio de l'atac segons el jugador
	s32 posx = GetCollisionRectAbsolute().x, posy = GetCollisionRectAbsolute().y, posplayerx = cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().x, posplayery = cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().y;
	s32 maxposx = posx + GetCollisionRectAbsolute().w, maxposy = posy + GetCollisionRectAbsolute().h, maxposplayerx = posplayerx + cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().w, maxposplayery = posplayery + cGame::Instance()->Scene->m_player.GetCollisionRectAbsolute().h;
	if (posx >= maxposplayerx)
	{
		m_orientation = ORIENTATION_O;
	}
	else if (maxposx <= posplayerx)
	{
		m_orientation = ORIENTATION_E;
	}
	else if (posy > posplayery)
	{
		m_orientation = ORIENTATION_N;
	}
	else
	{
		m_orientation = ORIENTATION_S;
	}

	auto orient = GetCurrentOrientation();
	auto recEnemy = GetCollisionRectAbsolute();
	switch (orient)
	{
	case ORIENTATION_N:
	case ORIENTATION_NE:
	case ORIENTATION_NO:
		SetAnimationRects(_attack_up_animation);
		m_attack_col_rect.SetRect(recEnemy.x, recEnemy.y - 30, recEnemy.w, 30);
		break;
	case ORIENTATION_S:
	case ORIENTATION_SE:
	case ORIENTATION_SO:
		SetAnimationRects(_attack_down_animation);
		m_attack_col_rect.SetRect(recEnemy.x, recEnemy.y + recEnemy.h, recEnemy.w, 30);
		break;
	case ORIENTATION_E:
		SetAnimationRects(_attack_right_animation);
		m_attack_col_rect.SetRect(recEnemy.x + recEnemy.w, recEnemy.y, 30, recEnemy.h);
		break;
	case ORIENTATION_O:
		SetAnimationRects(_attack_left_animation);
		m_attack_col_rect.SetRect(recEnemy.x - 30, recEnemy.y, 30, recEnemy.h);
		break;
	default:
		break;
	}
	PlayAnimation();

	if (_sound_action == 0)
	{
		_sound_action = cGame::Instance()->Sound.LoadSound("../media/sword2.wav");
		cGame::Instance()->Sound.SetVolumeSound(_sound_action, 1.0f);
	}

	cGame::Instance()->Sound.PlayGameSound(_sound_action);
	_state = ACTION;
}

void cEnemyPersecutor::ChangeToDie()
{
	SetAnimationRects(_death_animation);
	PlayAnimationNoLoop();
	SetAnimationFramesPerStep(4);
	if (_sound_death == 0)
	{
		_sound_death = cGame::Instance()->Sound.LoadSound("../media/death.wav");
		cGame::Instance()->Sound.SetVolumeSound(_sound_death, 1.0f);
	}
	cGame::Instance()->Sound.PlayGameSound(_sound_death);
	_state = DEATH;
}

void cEnemyPersecutor::UpdateDie()
{
}

void cEnemyPersecutor::ComputeNextMovement()
{
	_movement = static_cast<eMovement>(std::rand() % M_NUM_MOV);
}

void cEnemyPersecutor::SetPatrol(u32 a_weight, u32 a_height)
{
	s32 posx = GetCollisionRectAbsolute().x, posy = GetCollisionRectAbsolute().y;

	_patrol_rectangle.x = posx - a_weight / 2;
	_patrol_rectangle.y = posy - a_height / 2;
	_patrol_rectangle.h = a_weight;
	_patrol_rectangle.w = a_height;
}

void cEnemyPersecutor::RenderPatrolRectangle()
{
	if (IsCollidable())
	{
		s32 zIndex = 0;
		GetZIndex(zIndex);
		//Renderitzo el rectangle a Z+1 perque surti per sobre la textura sempre
		cGame::Instance()->Graphics->DrawRect(_patrol_rectangle, 0x00FF00FF, zIndex + 1);
	}
}

void cEnemyPersecutor::UpdatePatrolRectangle()
{
	SetPatrol(_patrol_rectangle.w, _patrol_rectangle.h);
}

void cEnemyPersecutor::respawn()
{
	if (!IsAlive())
	{
		ChangeToIdle();
	}
}
