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
#include "enemyBullet.h"

CEnemyBullet::CEnemyBullet(float xPos, float yPos, float speed)
{
	m_fX = xPos;
	m_fY = yPos;
	m_fSpeed = speed;
	m_bHit = false;
}

CEnemyBullet::~CEnemyBullet()
{
}

void CEnemyBullet::Draw()
{
	// Check if the enemy needs drawing
	if (!m_bHit)
	{
		// Draw here
		//CEntity::Draw();
	}
}

void CEnemyBullet::Move()
{
	// Move the bullet downwards
	m_fY += 10;
}

void CEnemyBullet::Hit()
{

}