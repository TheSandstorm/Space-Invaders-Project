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

// Library Includes
#include <vector>
// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "enemy.h"
#include "EnemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

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
	delete m_pSprite;
	m_pSprite = 0;
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
	_vecEnemyBullets->push_back(new CEnemyBullet());
}

void CEnemy::SetHit(bool _b)
{
	m_bHit = _b;
}

bool CEnemy::Ishit() const
{
	return (m_bHit);
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
	return m_iPoints;
}

void CEnemy::SetPoints(int _iPoints)
{
	m_iPoints = _iPoints;
}

void CEnemy::SetSpeed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
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
