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
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityY)
{
	const int iMask = IDB_BulletMask; //ID 

	int iSprite = IDB_PlayerBullet;

	m_pSprite = new CSprite();

	m_pSprite->Initialise(iSprite, iMask);

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityY = _fVelocityY;
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
	m_fY += m_fVelocityY * _fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

float
CBullet::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CBullet::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

float
CBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}