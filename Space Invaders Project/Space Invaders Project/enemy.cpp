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

// Local includes
#include "enemy.h"

// Constructor
CEnemy::CEnemy()
	: m_bHit(false),
	m_fTime(0),
	m_fSpeed(1.0f),
	m_iDirection(1),
	m_bWall(false)
{
	m_bDirectionRight = true;
}

// Destructor
CEnemy::~CEnemy()
{
}

bool CEnemy::Initialise()
{
	m_pSprite = new CSprite();
	m_pSprite->Initialise(m_iSprite, m_iSpriteMask);
	CEntity::m_pSprite->SetDestSizeW(50);
	CEntity::m_pSprite->SetDestSizeH(50);
	return(true);
}

void CEnemy::Draw()
{
	// Check if the enemy needs drawing
	if (!m_bHit)
	{
		// Draw here
		CEntity::Draw();
	}
}

void CEnemy::Process(float _fdeltatime)
{
	if (!m_bHit)
	{
		Move(_fdeltatime);

		CEntity::Process(_fdeltatime);
	}
}

void CEnemy::Shoot(std::vector<CEnemyBullet*>* _vecEnemyBullets)
{
	m_pEnemyBullet = new CEnemyBullet(m_fX, m_fY, 1.0f);
//	m_pEnemyBullet->Initialise(m_fX, m_fY - 15, m_iBulletSpeed);
}

void CEnemy::SetHit(bool _b)
{
}

bool CEnemy::Ishit() const
{
	return false;
}

void CEnemy::SetSprite(int _iSprite)
{
	m_iSprite = _iSprite;
}

void CEnemy::SetSpriteMask(int _iSpriteMask)
{
	m_iSpriteMask = _iSpriteMask;
}

int CEnemy::GetPoints()
{
	return 0;
}

void CEnemy::SetPoints(int _iPoints)
{
}

void CEnemy::SetSpeed(float _fSpeed)
{
}

void CEnemy::Move(float _fDeltaTick)
{
	m_fTime += _fDeltaTick;

	if (m_fTime >= m_fSpeed)
	{
		if (m_bWallHit == true)
		{
			m_iDirection *= -1;
			m_fY += 32;
			m_bWallHit = false;
		}
		else
		{
			m_fX += 20 * m_iDirection;
		}

		m_fTime = 0;

	}
}
