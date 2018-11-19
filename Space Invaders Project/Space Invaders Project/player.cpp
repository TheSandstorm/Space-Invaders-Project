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


// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "player.h"
#include "bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer() :
	m_bHit(false)
{
	m_iHealth = 3;
}

CPlayer::~CPlayer()
{
	if (m_pBullet != nullptr)
	{
		delete m_pBullet;
		m_pBullet = 0;
	}
}

bool
CPlayer::Initialise(const int _iScreenWidth)
{
	//ID's need to be put into the player
	VALIDATE(CEntity::Initialise(IDB_Player,IDB_PlayerMask));
	//Sprite Size
	CEntity::m_pSprite->SetDestSizeW(32);
	CEntity::m_pSprite->SetDestSizeH(16);
	m_iScreenWidth = _iScreenWidth;
	//Bullet Speed
	m_iBulletSpeed = -300;
	return (true);
}

void
CPlayer::Draw()
{
	CEntity::Draw();
}

void
CPlayer::Process(float _fDeltaTick)
{

	float fHalfPlayerW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 300.0f * _fDeltaTick;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fX -= 300.0f * _fDeltaTick;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_pBullet == nullptr)
		{
			m_pBullet = new CBullet();
			m_pBullet->Initialise(m_fX, m_fY - 15, m_iBulletSpeed);
		}

	}
	if (m_fX <= 0)
	{
		m_fX = 0;
	}
	else if (m_fX + fHalfPlayerW >= m_iScreenWidth)
	{
		m_fX = m_iScreenWidth - fHalfPlayerW;
	}

	CEntity::Process(_fDeltaTick);
}

void
CPlayer::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CPlayer::IsHit() const
{
	return (m_bHit);
}

void CPlayer::LoseLife()
{
	m_iHealth--;
}

int CPlayer::GetLives()
{
	return m_iHealth;
}

void CPlayer::SetHealth(int _iHealth)
{
	m_iHealth = _iHealth;
}

void CPlayer::SetBulletSpeed(float _iBulletSpeed)
{
	m_iBulletSpeed = _iBulletSpeed;
}

void CPlayer::DeleteBullet()
{
	if (m_pBullet != nullptr)
	{
		delete m_pBullet;
		m_pBullet = nullptr;
	}
}


CBullet * CPlayer::GetBullet()
{
	return m_pBullet;
}

void CPlayer::SetBullet(CBullet * _pBullet)
{
	m_pBullet = _pBullet;
}
