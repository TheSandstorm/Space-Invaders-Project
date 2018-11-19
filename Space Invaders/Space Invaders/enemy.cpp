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

void CEnemy::Initialise()
{
}

void CEnemy::Draw()
{
	// Check if the enemy needs drawing
	if (!m_bShot)
	{
		// Draw here
		CEntity::Draw();
	}
}

void CEnemy::Process(float _fdeltatime)
{
}

void CEnemy::Shoot(std::vector<CEnemyBullet*>* _vecEnemyBullets)
{
	m_pEnemyBullet = new CEnemyBullet(m_fX, m_fY, 1.0f);
	m_pEnemyBullet->Initialise(m_fX, m_fY - 15, m_iBulletSpeed);
}

void CEnemy::Drop()
{
	// Change direction
	if (m_bDirectionRight)
	{
		m_bDirectionRight = false;
	}
	else
	{
		m_bDirectionRight = true;
	}

	// Drop the enemies down
	m_fY += 20;
}

void CEnemy::SetHit(bool _b)
{
}

bool CEnemy::Ishit() const
{
	return false;
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
}
