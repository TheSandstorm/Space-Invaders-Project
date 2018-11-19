
// Library Includes
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Local Includes
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
//#include "Invader.h"


// This Include
#include "Level.h"

// Static Variables
static int s_iShootFrameBuffer = 10;

// Static Function Prototypes

// Implementation

CLevel::CLevel()
	:m_pPlayer(0)
	,m_pBullet(0)
	,m_iWidth(0)
	,m_iHeight(0)
	,m_fTime(0)
{
	srand(unsigned(time(NULL))); //Seed random shuffler
	bBulletExists = false;
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
		VALIDATE(m_pPlayer->Initialise(m_iWidth));

		// Set the player's position to be centered on the x, 
		// and a little bit up from the bottom of the window.
		m_pPlayer->SetX(_iWidth / 2.0f);
		m_pPlayer->SetY(_iHeight - (2.0f * m_pPlayer->GetHeight()));
	}
	m_pPlayer->SetHealth(3);

	//FP initialisation
	return (true);
}

void
CLevel::Draw()
{
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


	m_pPlayer->Process(_fDeltaTick);
}
