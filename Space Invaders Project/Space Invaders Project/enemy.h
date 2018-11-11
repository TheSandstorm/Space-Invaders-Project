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
#if !defined(__ENEMY_H__)
#define __ENEMY_H__

// Library Includes
#include <vector>
// Local Includes
#include "entity.h"
#include "clock.h"
#include "bullet.h"
#include "enemyBullet.h"


class CEnemy : public CEntity 
{
	// Member Functions
public:
	// Constructors and destructors
	CEnemy();
	~CEnemy();

	// Functions
	virtual bool Initialise();
	void Draw();
	void Process(float _fdeltatime);
	void Shoot(std::vector<CEnemyBullet*> *_vecEnemyBullets);
	void SetHit(bool _b);
	bool Ishit()const;

	void SetSprite(int _iSprite);
	void SetSpriteMask(int _iSpriteMask);

	int GetPoints();
	void SetPoints(int _iPoints);
	void SetSpeed(float _fSpeed);
	void Move(float _fDeltaTick);

private:
	CEnemy(const CEnemy& _kr);
	CEnemy& operator= (const CEnemy& _kr);
	// Member Variables
public:
	int m_iPoints;
	float m_fSpeed;
	int m_iDirection;
	bool m_bWallHit;
	int m_iSprite;
	int m_iSpriteMask;

protected:
	bool m_bHit;
	bool m_bShot;
	bool m_bWall;
	bool m_bDirectionRight;

private:
	float m_fTime;
	CEnemyBullet * m_pEnemyBullet = nullptr;
};

#endif    // __ENEMY_H__