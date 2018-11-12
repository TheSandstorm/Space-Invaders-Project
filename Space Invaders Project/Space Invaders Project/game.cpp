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
#include "Clock.h"
#include "BackBuffer.h"
#include "utils.h"
#include "sprite.h"
#include "Background.h"
#include "level.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
: m_pClock(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pBackBuffer(0)
{
	m_pBackground = nullptr;
}

CGame::~CGame()
{
    delete m_pBackBuffer;
    m_pBackBuffer = 0;

    delete m_pClock;
    m_pClock = 0;

	delete m_pBackground;
	m_pBackground = 0;

	delete m_pLevel;
	m_pLevel = 0;
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hApplicationInstance = _hInstance;
    m_hMainWindow = _hWnd;

    m_pClock = new CClock();
    VALIDATE(m_pClock ->Initialise());
    m_pClock->Process();

    m_pBackBuffer = new CBackBuffer();
    VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));
	//Needed to create the level obj

	if (m_pBackground == nullptr)
	{
		m_pBackground = new CBackGround();
		VALIDATE(m_pBackground->Initialise());
		//Set the background position to start from {0,0}
		m_pBackground->SetX((float)_iWidth / 2);
		m_pBackground->SetY((float)_iHeight / 2);
	}

	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	ShowCursor(true);

    return (true);
}

void
CGame::Draw()
{
    m_pBackBuffer->Clear();

	m_pBackground->Draw();
// Do all the game’s drawing here...
	m_pLevel->Draw();

    m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
    // Process all the game’s logic here.
	//Load a new sprite.
	m_pBackground->Process(_fDeltaTick);

	m_pLevel->Process(_fDeltaTick);
	
}

void 
CGame::ExecuteOneFrame()
{
    float fDT = m_pClock->GetDeltaTick();

    Process(fDT);
    Draw();

    m_pClock->Process();

	Sleep(1);
}

CGame&
CGame::GetInstance()
{
    if (s_pGame == 0)
    {
        s_pGame = new CGame();
    }

    return (*s_pGame);
}

void 
CGame::DestroyInstance()
{
    delete s_pGame;
    s_pGame = 0;
}

CBackBuffer* 
CGame::GetBackBuffer()
{
    return (m_pBackBuffer);
}

HINSTANCE 
CGame::GetAppInstance()
{
    return (m_hApplicationInstance);
}

HWND 
CGame::GetWindow()
{
    return (m_hMainWindow);
}

void
CGame::DrawFinalScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	std::string _strScore = "Final Score: " + ToString(m_pLevel->GetScore());

	int kiX = m_iWidth / 2;
	int kiY = m_iHeight / 2;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX - 130, kiY + 60, "Game Over!", 10);

	TextOutA(hdc, kiX + 20, kiY + 60, _strScore.c_str(), static_cast<int>(_strScore.size()));
}
