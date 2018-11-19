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
#include "Sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEntity::CEntity()
	: m_fX(0.0f)
	, m_fY(0.0f)
{

}

CEntity::~CEntity()
{
	if (m_pSprite != nullptr)
	{
		delete m_pSprite;
		m_pSprite = 0;
	}
}

bool
CEntity::Initialise(const int _kiSpriteID, const int _kiMaskID)
{
	m_pSprite = new CSprite();
	VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID));

	return (true);
}

void
CEntity::Draw()
{
	if (m_pSprite != nullptr)
	{
		m_pSprite->Draw();
	}
}

void
CEntity::Process(float _fDeltaTick)
{
	if (m_pSprite != nullptr)
	{
		m_pSprite->SetX(static_cast<int>(m_fX));
		m_pSprite->SetY(static_cast<int>(m_fY));

		m_pSprite->Process(_fDeltaTick);
	}
}

float
CEntity::GetX() const
{
	return (m_fX);
}

float
CEntity::GetY() const
{
	return (m_fY);
}

float
CEntity::GetWidth() const
{
	if (m_pSprite != nullptr)
	{
		return (static_cast<float>(m_pSprite->GetWidth()));

	}
	return 0;
}

void CEntity::SetWidth(int _iWidth)
{
	m_pSprite->SetWidth(_iWidth);
}

void CEntity::SetHeight(int _iHeight)
{
	m_pSprite->SetHeight(_iHeight);
}

float
CEntity::GetHeight() const
{
	if (m_pSprite != nullptr)
	{
		return (static_cast<float>(m_pSprite->GetHeight()));
	}
	return 0;
}

void
CEntity::SetX(float _f)
{
	m_fX = _f;
}

void
CEntity::SetY(float _f)
{
	m_fY = _f;
}
