#include "cEnemyPersecutor.h"
#include "cGame.h"

cEnemyPersecutor::cEnemyPersecutor() :
cCharacter("enemies", cRectangle(0, 0, 16, 24), 0, 0, 10, 2, 2, 1.0f),
_state(IDLE),
_anim_frame_to_change(24),
_anim_curr_frame(0),
_movement(M_DOWN)
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
			if (frameElapsed)
				ChangeToIdle();
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
	ChangeToDie();
}

void cEnemyPersecutor::UpdateIdle()
{
}

void cEnemyPersecutor::ChangeToIdle()
{
	ResetAnimation();
	StopAnimation();
	_state = IDLE;
}

void cEnemyPersecutor::UpdatePatrol()
{
	// Comprovem si estem a l'abast de l'enemic
	s32 posx = 0, posy = 0, posplayerx = 0, posplayery = 0;
	GetPosition(posx, posy);
	cGame::Instance()->Scene->m_player.GetPosition(posplayerx, posplayery);

	double radi = sqrt((posplayerx - posx)*(posplayerx - posx) + (posplayery - posy)*(posplayery - posy));
	if (radi < 100)
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
			PlayAnimation();
		}
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
		s32 posx = 0, posy = 0;
		GetPosition(posx, posy);

		s32 nposx = posx, nposy = posy, cx = posx / cCell::tileWidth, cy = posy / cCell::tileHeight;
		int mov = Path.NextStep(&nposx, &nposy, &cx, &cy);

		if (mov == ARRIVE)
		{
			Path.Done();
			int* map = (int *)malloc(sizeof(int)*(25 * 18));
			ZeroMemory(map, (25 * 18)*sizeof(int));
			Path.Make(map, posx / cCell::tileWidth, posy / cCell::tileHeight, 10, 10);
			delete map;
		}
		else if (mov == CONTINUE)
		{

			int xdiff = nposx - posx;
			int ydiff = nposy - posy;
			eMovement NewMovement = M_NOT_MOVE;
			if (xdiff > 0) NewMovement = M_RIGHT;
			else if (xdiff < 0) NewMovement = M_LEFT;
			else if (ydiff > 0) NewMovement = M_DOWN;
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
	
}

void cEnemyPersecutor::ChangeToAction()
{
	auto orient = GetCurrentOrientation();
	switch (orient)
	{
	case ORIENTATION_N:
	case ORIENTATION_NE:
	case ORIENTATION_NO:
		SetAnimationRects(_attack_up_animation);
		break;
	case ORIENTATION_S:
	case ORIENTATION_SE:
	case ORIENTATION_SO:
		SetAnimationRects(_attack_down_animation);
		break;
	case ORIENTATION_E:
		SetAnimationRects(_attack_right_animation);
		break;
	case ORIENTATION_O:
		SetAnimationRects(_attack_left_animation);
		break;
	default:
		break;
	}
	PlayAnimationNoLoop();

	_state = ACTION;
}

void cEnemyPersecutor::ChangeToDie()
{
	SetAnimationRects(_death_animation);
	PlayAnimationNoLoop();
	SetAnimationFramesPerStep(4);
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
	s32 posx = 0, posy = 0;
	GetPosition(posx, posy);

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