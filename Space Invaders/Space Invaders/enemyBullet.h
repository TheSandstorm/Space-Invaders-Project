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
class CEnemyBullet
{
public:
	// Constructors and destructors
	CEnemyBullet(float xPos, float yPos, float speed);
	~CEnemyBullet();

	// Variables
	float m_fX;
	float m_fY;
	float m_fSpeed;
	bool m_bHit;

	// Functions
	void draw();
	void move();
	void hit();
};