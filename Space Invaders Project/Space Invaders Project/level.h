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
class CFPSCounter;
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

	void SetScore(int _i);
	int GetScore();
protected:
	//Collision stuff goes here
	void EnemyBulletWallCollision();
	bool EnemyBulletCollision(float _fDeltatick);
	bool BulletEnemyBulletCollision(float _fDeltaTick);
	bool BulletPlayerCollision(float _fDeltaTick);

	void UpdateScoreText();
	void DrawScore();
	void UpdateHealthText();
	void DrawHealth();
	void DrawFPS();
	
private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);
	
	//Member Variables
public:
	bool GetLoseState();
	void SetLoseState(bool _bLoseState);
protected:
	CBullet * m_pBullet;
	CPlayer* m_pPlayer;
	CFPSCounter* m_fpsCounter;

	int m_iWidth;
	int m_iHeight;

	std::vector<CEnemy*> m_vecEnemies;
	std::vector<bool> m_vecbAlienColumns = { true , true ,true, true, true, true, true, true, true, true, true, true };
	std::vector<CEnemyBullet*> m_vecpEnemyBullets;

	float m_fDeltaTick;

	int m_iEnemyRemaning;

	std::wstring m_strScore;
	std::wstring m_strHealth;
private:
	bool bBulletExists;
	bool AlienShoot(int _iStack, float _fDeltaTick);
	float m_fSpeedModifier;
	float m_fTime;
	int m_iScore;
	bool m_bLoseState;

	//Debug values
	int m_fAlienShootMod;
};

#endif // __LEVEL_H__