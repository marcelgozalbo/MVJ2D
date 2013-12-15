#ifndef MPV2D_CENEMY_PERSECUTOR_H_
#define MPV2D_CENEMY_PERSECUTOR_H_

#include "cCharacter.h"

class cEnemyPersecutor : public cCharacter
{
public:
	cEnemyPersecutor();
	~cEnemyPersecutor();

	void Update() override;
	void Render() override;
	void SetPatrol(u32 a_weight, u32 a_height);

private:
	
	std::vector<cRectangle> _down_animation;
	std::vector<cRectangle> _up_animation;
	std::vector<cRectangle> _right_animation;
	std::vector<cRectangle> _left_animation;

	enum eState
	{
		IDLE,
		PATROL,
		RUN,
		ACTION,
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

	void ComputeNextMovement();
	void Move();
	void RenderPatrolRectangle();

	eMovement _movement;
	cRectangle _patrol_rectangle;
};

#endif
