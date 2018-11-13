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

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "resource.h"
#include "level.h"
#include "player.h"

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

CGame& rGame = CGame::GetInstance();
HWND g_hDlgDebug;

LRESULT CALLBACK WindowProc(HWND _hWnd,
	UINT _uiMsg,
	WPARAM _wParam,
	LPARAM _lParam)
{
    switch (_uiMsg)
	{
		case WM_KEYDOWN:
		{
			switch (_wParam)
			{
				case VK_ESCAPE:
				{
					ShowWindow(g_hDlgDebug, SW_SHOWNORMAL);
					break;
				}
			
				default:
					break;
			}
			
			return (0);
		}

		case WM_DESTROY:
        {
            PostQuitMessage(0);

            return(0);
        }

        default:
			break;
    } 

    return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

BOOL CALLBACK DIALOG(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	switch (_msg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
				// Change enemy speed
				case IDC_EDIT1:
				{
					float newValue = ReadFromEditBox(_hwnd, IDC_EDIT1);
					rGame.GetInstance().GetLevel()->Modify(newValue, 0, 0, 0);
					break;
				}

				// Change enemy bullet speed
				case IDC_EDIT2:
				{
					float newValue = ReadFromEditBox(_hwnd, IDC_EDIT2);
					rGame.GetInstance().GetLevel()->Modify(0, newValue, 0, 0);
					break;
				}

				// Change enemy fire rate
				case IDC_EDIT3:
				{
					float newValue = ReadFromEditBox(_hwnd, IDC_EDIT3);
					rGame.GetInstance().GetLevel()->Modify(0, 0, newValue, 0);
					break;
				}

				// Change player bullet speed
				case IDC_EDIT4:
				{
					float newValue = ReadFromEditBox(_hwnd, IDC_EDIT4);
					rGame.GetInstance().GetLevel()->Modify(0, 0, 0, -newValue);
					break;
				}

				default:
					break;
			}

			break;
		}
		
		case WM_CLOSE:
		{
			ShowWindow(_hwnd, SW_HIDE);
			return TRUE;
			break;
		}
		
		default:
			break;
	}

	return FALSE;
}

HWND 
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
    WNDCLASSEX winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = WindowProc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = _hInstance;
    winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
    winclass.lpszMenuName = NULL;
    winclass.lpszClassName = WINDOW_CLASS_NAME;
    winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&winclass))
    {
        // Failed to register.
        return (0);
    }

    HWND hwnd; 
    hwnd = CreateWindowEx(NULL,
                  WINDOW_CLASS_NAME,
                  _pcTitle,
              WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 
                  CW_USEDEFAULT, CW_USEDEFAULT,
                  _iWidth, _iHeight,
                  NULL,
                  NULL,
                  _hInstance,
                  NULL);
    
    if (!hwnd)
    {
        // Failed to create.
        return (0);
    }

    return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
    MSG msg;
	RECT _rect;
    ZeroMemory(&msg, sizeof(MSG));

	const int kiWidth = 960;
	const int kiHeight = 720;

    HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Space Invaders");
	g_hDlgDebug = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)DIALOG);

	GetClientRect(hwnd, &_rect);
    if (!rGame.Initialise(_hInstance, hwnd, _rect.right, _rect.bottom))
    {
        // Failed
        return (0);
    }

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            rGame.ExecuteOneFrame();
        }
    }
	
    CGame::DestroyInstance();

    return (static_cast<int>(msg.wParam));
}