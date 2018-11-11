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

#if !defined(__ENEMYBULLET_H__)
#define __ENEMYBULLET_H__

// Library Includes

// Local Includes
#include "bullet.h"

// Types

// Constants

// Prototypes
class CSprite;
class CSprite;

class CEnemyBullet : public CBullet
{
public:
	// Constructors and destructors
	CEnemyBullet();
	~CEnemyBullet();
	// Functions
	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY, float _fDeltaTick);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	float GetSpeedY() const;
	void SetSpeedY(float _fY);

	float GetRadius() const;
protected:

private:
	CEnemyBullet(const CEnemyBullet& _kr);
	CEnemyBullet& operator= (const CEnemyBullet& _kr);
public:

protected:
	float m_fSpeed;
private:

};

#endif