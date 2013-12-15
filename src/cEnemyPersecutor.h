#ifndef MPV2D_CENEMY_PERSECUTOR_H_
#define MPV2D_CENEMY_PERSECUTOR_H_

#include "cCharacter.h"
#include "cPath.h"

class cEnemyPersecutor : public cCharacter
{
public:
	cEnemyPersecutor();
	~cEnemyPersecutor();

	void Update() override;
	void Render() override;
	void SetPatrol(u32 a_weight, u32 a_height);
	void Die();

private:
	
	std::vector<cRectangle> _down_animation;
	std::vector<cRectangle> _up_animation;
	std::vector<cRectangle> _right_animation;
	std::vector<cRectangle> _left_animation;

	std::vector<cRectangle> _attack_down_animation;
	std::vector<cRectangle> _attack_up_animation;
	std::vector<cRectangle> _attack_right_animation;
	std::vector<cRectangle> _attack_left_animation;

	std::vector<cRectangle> _death_animation;

	enum eState
	{
		IDLE,
		PATROL,
		RUN,
		ACTION,
		DEATH,
	};

	eState _state;

	std::size_t _anim_frame_to_change;		//quantitat de frames que han de passar per canviar de direccio
	std::size_t _anim_curr_frame;	//quantitat de frames que han passat desde l'ultim canvi d'step

	enum eMovement
	{
		M_DOWN,
		M_UP,
		M_LEFT,
		M_RIGHT,
		M_NUM_MOV
	};

	void DoMovement();
	void ComputeNextMovement();
	void Move();
	void RenderPatrolRectangle();
	void UpdateIdle();
	void ChangeToIdle();
	void UpdatePatrol();
	void ChangeToPatrol();
	void UpdateRun();
	void ChangeToRun();
	void UpdateAction();
	void ChangeToAction();
	void UpdateDie();
	void ChangeToDie();

	eMovement _movement;
	cRectangle _patrol_rectangle;
	cPath Path;
};

#endif
