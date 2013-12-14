#ifndef MPV2D_CCHARACTER_H_
#define MPV2D_CCHARACTER_H_

#include "types.h"
#include "cBaseEntity.h"

enum CharacterOrientation
{
	ORIENTATION_N = 0,
	ORIENTATION_NE,
	ORIENTATION_NO,
	ORIENTATION_S,
	ORIENTATION_SE,
	ORIENTATION_SO,
	ORIENTATION_E,
	ORIENTATION_O,
};

class cCharacter : public cBaseEntity
{
public:
	cCharacter();
	cCharacter(const std::string& textureId, const cRectangle& textureRect, s32 x, s32 y, s32 z, s32 vStraight, s32 vDiagonal, f32 textureScale = 1.0f);
	virtual ~cCharacter();

	void Init(const std::string& textureId, const cRectangle& textureRect, s32 x, s32 y, s32 z, s32 vStraight, s32 vDiagonal, f32 textureScale = 1.0f);

	virtual void Update() override = 0;
	virtual void Render() override = 0;
	CharacterOrientation GetCurrentOrientation() const { return m_orientation; };
	CharacterOrientation GetLastOrientation() const { return m_last_orientation; };
protected:
	virtual bool Move(s32 xAmount, s32 yAmount) final;

	CharacterOrientation m_orientation, m_last_orientation;
	s32 m_vStraight;
	s32 m_vDiagonal;
};

#endif
