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

// Library Includes
#include <vector>
// Local Includes
#include "entity.h"
#include "clock.h"
#include "bullet.h"
#include "enemyBullet.h"
#include "entity.h"

class CEnemy : public CEntity 
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
	void Initialise();
	void Draw();
	void Process(float _fdeltatime);
	void Shoot();
	void Move();
	void Drop();
};