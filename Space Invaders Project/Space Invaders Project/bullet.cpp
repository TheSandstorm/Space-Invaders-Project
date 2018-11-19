// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Includes
#include "bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation
bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fSpeedY)
{
	const int iMask = IDB_BulletMask; //ID 

	int iSprite = IDB_PlayerBullet;

	m_pSprite = new CSprite();

	m_pSprite->Initialise(iSprite, iMask);

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fSpeedY = _fSpeedY;
	//Sprite Size
	CEntity::m_pSprite->SetDestSizeW(16);
	CEntity::m_pSprite->SetDestSizeH(32);

	return (true);
}

CBullet::~CBullet()
{
	if (m_pSprite != nullptr)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
}

//CBullet::~CBullet()
//{
//}

void
CBullet::Draw()
{
	CEntity::Draw();
}

void
CBullet::Process(float _fDeltaTick)
{
	m_fY += m_fSpeedY * _fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

float
CBullet::GetSpeedY() const
{
	return (m_fSpeedY);
}

void
CBullet::SetSpeedY(float _fY)
{
	m_fSpeedY = _fY;
}

float
CBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}