#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <string>
#include <vector>

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CFPSCounter;
class CBackGround;
class CEnemy;
class CBullet;
class CEnemyBullet;
class CPlayer;
//class CBarrierBlock;
//class CLifeCount;

class CLevel
{
	//Member Functions 
public:
	CLevel();
	virtual ~CLevel();

	virtual bool Initialise(int _iWidth, int _iHeight);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

protected:
	//Collision stuff goes here

private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);
	
	//Member Variables
public:
	CBullet * GetPlayerBullet();
	CPlayer* GetPlayer();

protected:
	CBullet * m_pBullet;
	CPlayer* m_pPlayer;

	int m_iWidth;
	int m_iHeight;

	std::vector<CEnemy*> m_vecEnemies;
	std::vector<bool> m_vecbAlienColumns = { true , true ,true, true, true, true, true, true, true, true, true, true };

	float m_fDeltaTick;
private:
	bool bBulletExists;
	bool AlienShoot(int _iStack, float _fDeltaTick);
	float m_fSpeedModifier;
	float m_fTime;

	//Debug values
	int m_fAlienShootMod;
};

#endif // __LEVEL_H__