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
//TODO: inclResource
#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "game.h"

// This Include
#include "background.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBackGround::CBackGround()
{

}

CBackGround::~CBackGround()
{

}

bool
CBackGround::Initialise()
{
	//TODO: Needs an resource id for a background and a mask to function

	VALIDATE(CEntity::Initialise(,));

	return (true);
}

void
CBackGround::Draw()
{
	CEntity::Draw();
}

void
CBackGround::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}
