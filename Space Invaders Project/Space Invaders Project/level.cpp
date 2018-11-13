
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
#include "framerate.h"


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
	m_iScore = 0;
	m_dBulletSpeed = 520.0;
	m_fpsCounter = nullptr;
	m_pPlayer = nullptr;
}

CLevel::~CLevel()
{
	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;
}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{

	m_iHeight = _iHeight;
	m_iWidth = _iWidth;

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
	const int kiGap = 35;

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
			pEnemy->SetPoints(30);
		}
		//Sets second set
		else if (i >= 12 && i < 36)
		{
			iSprite = IDB_Enemy2;
			iSpriteMask = IDB_Enemy2Mask;
			pEnemy->SetPoints(20);
		}
		//Sets final set
		else
		{
			iSprite = IDB_Enemy3;
			iSpriteMask = IDB_Enemy3Mask;
			pEnemy->SetPoints(10);
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

	if (m_fpsCounter == nullptr)
	{
		m_fpsCounter = new CFPSCounter();
		VALIDATE(m_fpsCounter->Initialise());
		UpdateScoreText();
	}

	//FP initialisation
	return (true);
}

void CLevel::Draw()
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

	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		if (m_vecpEnemyBullets.empty() == false)
		{
			m_vecpEnemyBullets[i]->Draw();
		}
	}
	//Draw screen statistics for debugging
	//ScreenStats();
	DrawScore();
	DrawFPS();
	DrawHealth();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_fDeltaTick = _fDeltaTick;

	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); i++)
	{
		m_vecpEnemyBullets[i]->Process(_fDeltaTick);
	}

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

	EnemyBulletWallCollision();
	BulletPlayerCollision(_fDeltaTick);
	//Checks player bullet if it hits the top wall
	if (bBulletExists == true && m_pBullet->GetY() <= -m_pBullet->GetHeight())
	{
		m_pPlayer->DeleteBullet();
		m_pBullet = nullptr;
		bBulletExists = false;
	}

	if (bBulletExists == true)
	{
		bBulletExists=EnemyBulletCollision(_fDeltaTick);
	}
	if (bBulletExists == true)
	{
		bBulletExists = BulletEnemyBulletCollision(_fDeltaTick);
	}
	

	//Alien Shoot
	if (s_iShootFrameBuffer <= 0 && m_fAlienShootMod != -1)
	{
		s_iShootFrameBuffer = rand() % (m_fAlienShootMod);
		if (AlienShoot((rand() % 12), _fDeltaTick) == false) {
			s_iShootFrameBuffer = 1;
		}
	}
	else if (m_fAlienShootMod == -1)
	{
		s_iShootFrameBuffer = 1;
	}

	--s_iShootFrameBuffer;
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
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

void CLevel::SetScore(int _i)
{
	m_iScore = _i;
	UpdateScoreText();
}

int CLevel::GetScore()
{
	return m_iScore;
}

//Checks if the enemy bullet hit the bottom wall
void CLevel::EnemyBulletWallCollision()
{
	float fBulletY;
	float fBulletH;

	for (size_t i = 0; i < m_vecpEnemyBullets.size(); i++)//Checks every bullet in the vector
	{
		fBulletH = m_vecpEnemyBullets.at(i)->GetHeight();
		fBulletY = m_vecpEnemyBullets.at(i)->GetY();
		if (fBulletY > (m_iHeight) + fBulletH)
		{
			CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

			m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

			delete pBullet;
			pBullet = nullptr;
		}
	}
}

bool CLevel::EnemyBulletCollision(float _fDeltatick)
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr && !m_vecEnemies[i]->IsHit())
		{
			float fBulletWidth = m_pBullet->GetRadius();
			float fBulletHeight = m_pBullet->GetHeight() / 2;

			float fBulletX = m_pBullet->GetX();
			float fBulletY = m_pBullet->GetY();

			float fEnemyX = m_vecEnemies[i]->GetX();
			float fEnemyY = m_vecEnemies[i]->GetY();

			float fEnemyH = m_vecEnemies[i]->GetHeight();
			float fEnemyW = m_vecEnemies[i]->GetWidth();
			if ((fBulletX + fBulletWidth > fEnemyX - fEnemyW / 2 ) &&
				(fBulletX - fBulletWidth < fEnemyX + fEnemyW / 2) &&
				(fBulletY + fBulletHeight > fEnemyY - fEnemyH / 2) &&
				(fBulletY - fBulletHeight < fEnemyY + fEnemyH / 2 ))
			{
				//Hit's the front side of the ship
				m_pBullet->SetY((fEnemyY + fEnemyH / 2.0f) + fBulletWidth);
				m_pBullet->SetSpeedY(m_pBullet->GetSpeedY()*-1);

				SetScore(m_vecEnemies[i]->GetPoints() + GetScore());
				CEnemy* pEnemy = m_vecEnemies[i];

				delete pEnemy;

				m_vecEnemies[i] = nullptr;

				m_pPlayer->DeleteBullet();

				for (unsigned int j = 0; j < m_vecEnemies.size(); j++)
				{
					if (m_vecEnemies[j] != nullptr)
					{
						m_vecEnemies[j]->m_fSpeed *= 0.97f;
					}
				}
				return false;
			}
		}
	}
	return true;
}

bool CLevel::BulletEnemyBulletCollision(float _fDeltaTick) {
	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); ++i) // cycles through all bullets in the vector
	{
		float fEnemyBulletR = m_vecpEnemyBullets[i]->GetRadius();

		float fEnemyBulletX = m_vecpEnemyBullets[i]->GetX();
		float fEnemyBulletY = m_vecpEnemyBullets[i]->GetY();

		float fBulletX = m_pBullet->GetX();
		float fBulletY = m_pBullet->GetY();

		float fBulletR = m_pBullet->GetRadius();

		if ((fEnemyBulletX + fEnemyBulletR > fBulletX - fBulletR / 2) &&
			(fEnemyBulletX - fEnemyBulletR < fBulletX + fBulletR / 2) &&
			(fEnemyBulletY + fEnemyBulletR > fBulletY - fBulletR / 2) &&
			(fEnemyBulletY - fEnemyBulletR < fBulletY + fBulletR / 2))
		{
			//Hit the front side of the bullet...
			m_vecpEnemyBullets[i]->SetY((fBulletY + fBulletR / 2.0f) + fEnemyBulletR);
			m_vecpEnemyBullets[i]->SetSpeedY(m_vecpEnemyBullets[i]->GetSpeedY() * -1);

			m_pBullet->SetY((fEnemyBulletX + fEnemyBulletR / 2.0f) + fBulletR);
			m_pBullet->SetSpeedY(m_pBullet->GetSpeedY() * -1);

			delete m_pBullet;

			m_pBullet = 0;
			m_pPlayer->SetBullet(nullptr);

			CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

			m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

			delete pBullet;
			pBullet = nullptr;


			//reduce the player's health

			return false;
		}
	}
	return true;
}

bool CLevel::BulletPlayerCollision(float _fDeltaTick) {
	for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); ++i)
	{
		if (m_vecpEnemyBullets[i] != nullptr && !m_pPlayer->IsHit())
		{
			float fBulletR = m_vecpEnemyBullets[i]->GetRadius();

			float fBulletX = m_vecpEnemyBullets[i]->GetX();
			float fBulletY = m_vecpEnemyBullets[i]->GetY();

			float fPlayerX = m_pPlayer->GetX();
			float fPlayerY = m_pPlayer->GetY();

			float fPlayerH = m_pPlayer->GetHeight();
			float fPlayerW = m_pPlayer->GetWidth();

			if ((fBulletX + fBulletR > fPlayerX - fPlayerW / 2) &&
				(fBulletX - fBulletR < fPlayerX + fPlayerW / 2) &&
				(fBulletY + fBulletR > fPlayerY - fPlayerH / 2 + 18) && 
				(fBulletY - fBulletR < fPlayerY + fPlayerH / 2))
			{
				//Hit the front side of the brick...
				m_vecpEnemyBullets[i]->SetY((fPlayerY + fPlayerH / 2.0f) + fBulletR);
				m_vecpEnemyBullets[i]->SetSpeedY(m_vecpEnemyBullets[i]->GetSpeedY() * -1);

				CEnemyBullet* pBullet = m_vecpEnemyBullets.at(i);

				m_vecpEnemyBullets.erase(m_vecpEnemyBullets.begin() + i);

				delete pBullet;
				pBullet = nullptr;

				//reduce the player's health
				m_pPlayer->LoseLife();
				//check to see if the player lost
				if (m_pPlayer->GetLives() == 0)
				{
					this->SetLoseState(true);
				}
				return false;
			}
		}
	}
	return true;
}

void CLevel::UpdateScoreText()
{
	m_strScore = L"Score: ";
	wchar_t wstrTemp[10];
	_itow_s(static_cast< int >(m_iScore), wstrTemp, 10);
	m_strScore += wstrTemp;
}

void CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 0;
	const int kiY = m_iHeight - 14;

	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}

void CLevel::UpdateHealthText()
{
	m_strHealth = L"Health: ";
	wchar_t wstrTemp[10];
	_itow_s(static_cast<int>(m_pPlayer->GetLives()), wstrTemp, 10);
	m_strHealth += wstrTemp;
}
void CLevel::DrawHealth()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	const int kiX = 0;
	const int kiY = m_iHeight - 40;

	TextOut(hdc, kiX, kiY, m_strHealth.c_str(), static_cast<int>(m_strHealth.size()));
}

void CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}

bool CLevel::GetLoseState()
{
	return m_bLoseState;
}

void CLevel::SetLoseState(bool _bLoseState)
{
	m_bLoseState = _bLoseState;
}


bool CLevel::AlienShoot(int _iStack, float _fDeltaTick)
{
	if ((m_vecbAlienColumns.at(_iStack) == true))
	{
		for (int j = static_cast<int>(m_vecEnemies.size() - 1); j >= 0; --j)
		{
			if ((m_vecEnemies.at(j) != nullptr) && (j % 12 == _iStack))
			{
				m_vecEnemies.at(j)->Shoot(&m_vecpEnemyBullets);
				m_vecpEnemyBullets.back()->Initialise(m_vecEnemies.at(j)->GetX(), m_vecEnemies.at(j)->GetY() + 15, m_dBulletSpeed, m_fDeltaTick);
				return true;
			}
		}
	}
	return false;
}

void CLevel::Modify(float _fEnemySpeed, float _fEnemyBulletSpeed, float _fEnemyFirerate, float _fPlayerBulletSpeed)
{
	if (_fEnemySpeed != 0)
	{
		m_fSpeedModifier = 1 / _fEnemySpeed;
		for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
		{
			if (m_vecEnemies.at(i) != nullptr)
			{
				m_vecEnemies.at(i)->SetSpeed(m_fSpeedModifier);
			}
		}
	}
	if (_fEnemyBulletSpeed != 0)
	{
		for (unsigned int i = 0; i < m_vecpEnemyBullets.size(); ++i)
		{
			if (m_vecpEnemyBullets.at(i) != nullptr)
			{
				m_vecpEnemyBullets.at(i)->SetSpeedY(_fEnemyBulletSpeed);
			}
		}
		m_dBulletSpeed = _fEnemyBulletSpeed;
	}
	if (_fEnemyFirerate != 0)
	{
		//m_fSpeedModifier = _fEnemySpeed;
		m_fAlienShootMod = static_cast<int>(_fEnemyFirerate);
		s_iShootFrameBuffer = 0;
	}
	if (_fPlayerBulletSpeed != 0)
	{
		//m_fSpeedModifier = _fEnemySpeed;
		m_pPlayer->SetBulletSpeed(static_cast<int>(_fPlayerBulletSpeed));
	}
}
void
CLevel::CheckForWin()
{
	for (unsigned int i = 0; i < m_vecEnemies.size(); ++i)
	{
		if (m_vecEnemies[i] != nullptr && !m_vecEnemies[i]->IsHit())
		{
			return;
		}
	}
	ResetLevel();
	Sleep(1000);

	CLevel::Initialise(m_iWidth, m_iHeight);
	m_fSpeedModifier *= 0.85f;
}
void CLevel::ResetLevel()
{
	while (m_vecEnemies.size() > 0)
	{
		CEnemy* pEnemy = m_vecEnemies[m_vecEnemies.size() - 1];

		m_vecEnemies.pop_back();

		delete pEnemy;
		pEnemy = 0;
	}

	//while (m_vecpBarrierBlocks.size() > 0)
	//{
	//	CBarrierBlock* pBarrier = m_vecpBarrierBlocks[m_vecpBarrierBlocks.size() - 1];
	//	m_vecpBarrierBlocks.pop_back();

	//	delete pBarrier;
	//	pBarrier = nullptr;
	//}

	while (m_vecpEnemyBullets.size() != 0)
	{
		CBullet* pEnemyBullet = m_vecpEnemyBullets[m_vecpEnemyBullets.size() - 1];

		m_vecpEnemyBullets.pop_back();

		if (pEnemyBullet != nullptr)
		{
			delete pEnemyBullet;
		}
		pEnemyBullet = nullptr;
	}

	if (m_pBullet != nullptr)
	{
		m_pPlayer->DeleteBullet();
		m_pBullet = nullptr;
		bBulletExists = false;
	}

	//if (bMotherShipExists == true)
	//{
	//	delete m_pMotherShip;
	//	m_pMotherShip = 0;
	//	bMotherShipExists = false;
	//}
}