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

#pragma once

// Local includes
#include "enemyBullet.h"
#include "entity.h"

class CEnemy
{
public:
	// Constructors and destructors
	CEnemy(float xPos, float yPos, float speed);
	~CEnemy();

	// Variables
	bool m_bShot;
	bool m_bWall;
	bool m_bDirectionRight;
	float m_fSpeed;
	float m_fX;
	float m_fY;

	// Functions
	void draw();
	void shoot();
	void move();
	void drop();
};