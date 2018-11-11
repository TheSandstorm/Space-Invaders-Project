
// Library Includes
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Local Includes
#include "resource.h"
#include "Game.h"
#include "player.h"
#include "enemy.h"
//#include "mothership.h" // if we get time
#include "bullet.h"
//#include "barrier.h" // if we get time
//#include "lifecount.h" // if we get time
#include "utils.h"
#include "backbuffer.h"
//#include "framecounter.h"


// This Include
#include "Level.h"

// Static Variables
static int s_iShootFrameBuffer = 10;

// Static Function Prototypes

// Implementation

CLevel::CLevel()
	://m_iEnemyRemaining(0)
	m_pPlayer(0)
	,m_pBullet(0)
	,m_iWidth(0)
	,m_iHeight(0)
	,m_fTime(0)
{
	srand(unsigned(time(NULL))); //Seed random shuffler
	bBulletExists = false;
	m_fSpeedModifier = 1.0f;
	m_fAlienShootMod = 500;

	m_pPlayer = nullptr;
}

CLevel::~CLevel()
{
	delete m_pPlayer;
	m_pPlayer = 0;
}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{

	m_iHeight = _iWidth;
	m_iWidth = _iHeight;

	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer();
		VALIDATE(m_pPlayer->Initialise(_iWidth));

		// Set the player's position to be centered on the x, 
		// and a little bit up from the bottom of the window.
		m_pPlayer->SetX(_iWidth / 2.0f);
		m_pPlayer->SetY(_iHeight - (4.0f * m_pPlayer->GetHeight()));
	}
	m_pPlayer->SetHealth(3);

	const int kiEnemyStart = 60;
	const int kiStartX = 50;
	const int kiGap = 32;

	int iCurrentX = kiStartX;
	int iCurrentY = 30;
	//Sets first set
	int iSprite = IDB_Enemy1;
	int iSpriteMask = IDB_Enemy1Mask;
	//Creates the aliens
	for (int i = 0; i < kiEnemyStart; ++i)
	{
		CEnemy*pEnemy;
		pEnemy = new CEnemy();
		if (i < 12)
		{

		}
		//Sets second set
		else if (i >= 12 && i < 36)
		{
			iSprite = IDB_Enemy2;
			iSpriteMask = IDB_Enemy2Mask;
		}
		//Sets final set
		else
		{
			iSprite = IDB_Enemy3;
			iSpriteMask = IDB_Enemy3Mask;
		}
		pEnemy->SetSprite(iSprite);
		pEnemy->SetSpriteMask(iSpriteMask);
		VALIDATE(pEnemy->Initialise());

		pEnemy->SetX(static_cast<float>(iCurrentX));
		pEnemy->SetY(static_cast<float>(iCurrentY));
		pEnemy->SetSpeed(m_fSpeedModifier);
		//Creates a gap between the Aliens
		iCurrentX += static_cast<int>(pEnemy->GetWidth()) + kiGap;
		//jumps down to the next line if too close to the screen edge
		if (iCurrentX > (_iWidth - 150))
		{
			iCurrentX = kiStartX;
			iCurrentY += kiStartX;
		}
		m_vecEnemies.push_back(pEnemy);
	}
	//FP initialisation
	return (true);
}

void
CLevel::Draw()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr)
		{
			m_vecEnemies[i]->Draw();
		}
	}

	m_pPlayer->Draw();

	if (bBulletExists == true)
	{
		m_pBullet->Draw();
	}
	//Draw screen statistics for debugging
	//ScreenStats();

}

void
CLevel::Process(float _fDeltaTick)
{
	m_fDeltaTick = _fDeltaTick;
	
	m_fTime += _fDeltaTick;

	m_pBullet = m_pPlayer->GetBullet();

	if (m_pBullet != nullptr)
	{
		bBulletExists = true;
	}

	if (bBulletExists == true)
	{
		m_pBullet->Process(_fDeltaTick);
	}
	bool hitwall = false;
	for (size_t j = 0; j < m_vecEnemies.size(); j++)
	{
		if (m_vecEnemies[j] != nullptr && m_vecEnemies[j]->m_iDirection > 0) // Move left
		{
			if (m_vecEnemies[j]->GetX() + m_vecEnemies[j]->GetWidth() >= m_iWidth)
			{
				hitwall = true;
			}

		}
		else if (m_vecEnemies[j] != nullptr && m_vecEnemies[j]->m_iDirection < 0)
		{
			if (m_vecEnemies[j]->GetX() - m_vecEnemies[j]->GetWidth() / 2 <= 0)
			{
				hitwall = true;
			}
		}
	}

	if (hitwall == true)
	{
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			if (m_vecEnemies[i] != nullptr)
			{
				m_vecEnemies[i]->m_bWallHit = true;
			}
		}
		hitwall = false;
	}
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr)
		{
			m_vecEnemies[i]->Process(_fDeltaTick);

		}
	}
	m_pPlayer->Process(_fDeltaTick);
}
