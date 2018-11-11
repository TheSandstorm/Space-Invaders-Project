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
CEnemy::CEnemy(float xPos, float yPos, float speed)
{
	m_bShot = false;
	m_bWall = false;
	m_bDirectionRight = true;
	m_fX = xPos;
	m_fY = yPos;
	m_fSpeed = speed;
}

// Destructor
CEnemy::~CEnemy()
{
}

void CEnemy::Draw()
{
	// Check if the enemy needs drawing
	if (!m_bShot)
	{
		// Draw here
	}
}

void CEnemy::Shoot()
{
	m_pBullet = new CEnemyBullet(m_fX, m_fY);
}

void CEnemy::Move()
{
	// Move enemy
	if (m_bDirectionRight)
	{
		m_fX += m_fSpeed;
	}
	else
	{
		m_fX -= m_fSpeed;
	}

	// Call upon the draw function
	Draw();
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