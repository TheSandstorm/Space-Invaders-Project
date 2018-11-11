//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__BULLET_H__)
#define __BULLET_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "sprite.h"
// Types

// Constants

// Prototypes
class CSprite;

class CBullet : public CEntity
{
	// Member Functions
public:
	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY);
	virtual ~CBullet();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	float GetVelocityY() const;
	void SetVelocityY(float _fY);

	float GetRadius() const;

protected:
	float m_fVelocityY;
};


#endif    // __BULLET_H__

