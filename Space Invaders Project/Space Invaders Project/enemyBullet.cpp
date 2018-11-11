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

// Local Includes
#include "resource.h"
#include "utils.h"

// This Includes
//#include "bullet.h"
#include "enemyBullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEnemyBullet::CEnemyBullet()
	:m_fSpeed(0.0f)
{
	m_pSprite = nullptr;
}

CEnemyBullet::~CEnemyBullet()
{
}

bool
CEnemyBullet::Initialise(float _fPosX, float _fPosY, float _fSpeedY, float _fDeltaTick)
{
	const int iMask = IDB_BulletMask;

	int iSprite = IDB_EnemyBullet;


	m_pSprite = new CSprite();
	m_pSprite->Initialise(iSprite, iMask);

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fSpeed = _fSpeedY;

	CEntity::m_pSprite->SetDestSizeW(16);
	CEntity::m_pSprite->SetDestSizeH(32);
	CEntity::Process(_fDeltaTick);

	return (true);
}


void CEnemyBullet::Draw()
{
	// Draw here
	CEntity::Draw();
}

void CEnemyBullet::Process(float _fDeltaTick)
{
	m_fY += m_fSpeed * _fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

float CEnemyBullet::GetSpeedY() const
{
	return (m_fSpeed);
}

void CEnemyBullet::SetSpeedY(float _fY)
{
	m_fSpeed = _fY;
}

float CEnemyBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}
