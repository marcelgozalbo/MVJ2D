#include "cEnemyPersecutor.h"

cEnemyPersecutor::cEnemyPersecutor() :
cCharacter("enemies", cRectangle(0, 0, 26, 30), 0, 0, 10, 3, 2, 3.0f),
_state(PATROL),
_anim_frame_to_change(30),
_anim_curr_frame(0),
_movement(M_DOWN)
{
	_down_animation.push_back(cRectangle(11, 315, 26, 30));
	_down_animation.push_back(cRectangle(38, 315, 26, 30));
	_down_animation.push_back(cRectangle(68, 315, 26, 30));
	_down_animation.push_back(cRectangle(98, 315, 26, 30));

	_up_animation.push_back(cRectangle(13, 233, 26, 32));
	_up_animation.push_back(cRectangle(43, 233, 26, 32));
	_up_animation.push_back(cRectangle(76, 233, 26, 32));
	_up_animation.push_back(cRectangle(107, 233, 26, 32));

	_left_animation.push_back(cRectangle(13, 184, 26, 31));
	_left_animation.push_back(cRectangle(42, 184, 26, 31));
	_left_animation.push_back(cRectangle(72, 184, 26, 31));
	_left_animation.push_back(cRectangle(100, 184, 26, 31));

	_right_animation.push_back(cRectangle(13, 273, 26, 30));
	_right_animation.push_back(cRectangle(41, 273, 26, 30));
	_right_animation.push_back(cRectangle(71, 273, 26, 30));
	_right_animation.push_back(cRectangle(100, 273, 26, 30));
	
	SetAnimationSteps(_down_animation);
	SetAnimationFramesPerStep(2);
	EnableAnimation();
	
	EnableDebugMode();
}

cEnemyPersecutor::~cEnemyPersecutor()
{

}

void cEnemyPersecutor::Update()
{
	cBaseEntity::Update();

	switch (_state)
	{
		case IDLE:
			break;
		case PATROL:
						
			if (_anim_curr_frame <= _anim_frame_to_change)
			{
				_anim_curr_frame++;
			}
			else
			{
				ComputeNextMovement();
				_anim_curr_frame = 0;
			}
			Move();
			break;
		case RUN:
			break;
		case ACTION:
			break;
	}
}

void cEnemyPersecutor::Render()
{
	cBaseEntity::Render();
}

void cEnemyPersecutor::ComputeNextMovement()
{
	_movement = static_cast<eMovement>(std::rand() % M_NUM_MOV);
}

void cEnemyPersecutor::Move()
{
	s32 x = 0, y = 0;
	switch (_movement)
	{
		case M_DOWN:
			x = 0, y = 1;
			break;
		case M_UP:
			x = 0, y = -1;
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
		cCharacter::Move(x, y);

		if (GetLastOrientation() != GetCurrentOrientation())
		{
			auto orient = GetCurrentOrientation();
			switch (orient)
			{
			case ORIENTATION_N:
			case ORIENTATION_NE:
			case ORIENTATION_NO:
				SetAnimationSteps(_up_animation);
				break;
			case ORIENTATION_S:
			case ORIENTATION_SE:
			case ORIENTATION_SO:
				SetAnimationSteps(_down_animation);
				break;
			case ORIENTATION_E:
				SetAnimationSteps(_right_animation);
				break;
			case ORIENTATION_O:
				SetAnimationSteps(_left_animation);
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
