// Trafikklys.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Trafikklys.h"
#include <Windows.h>
#include <mmsystem.h>
#include "biler.h"
#include <stdlib.h>
#include <list>
#include <time.h>
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int test = 0;
int x2 = 0;
int tid = 0;
int id = 0;
int probabilityEast = 0;
int probabilitySouth = 0;
wstring data;
wstring data2;
static list<biler*> l;
static list<biler*> l1;
BOOL receivedData = FALSE;
BOOL redLightL = FALSE;
BOOL redLightR = FALSE;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TRAFIKKLYS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRAFIKKLYS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAFIKKLYS));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_TRAFIKKLYS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//C:\Users\Simen\Downloads
	//c:\\Users\\Simen\\Downloads\\House.bmp
	HWND hWnd;
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGFIRST), hWnd, (DLGPROC)DlgProc);
	return TRUE;
}
bool loadImageBmp(HDC hWinDC, LPWSTR path){
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	if (hBitmap == NULL){
		MessageBox(0, _T("Couldn't load the image"), _T("Error"), MB_OK);
		return false;
	}

	HDC hLocalDC = CreateCompatibleDC(hWinDC);
	if (hLocalDC == NULL){
		MessageBox(0, _T("Couldn't load the hLocalDC"), _T("Error"), MB_OK);
		return false;
	}

	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn){
		MessageBox(0, _T("Couldn't load the iReturn"), _T("Error"), MB_OK);
		return false;
	}

	HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL){
		MessageBox(0, _T("Couldn't load the oldBMP"), _T("Error"), MB_OK);
		return false;
	}

	//BOOL qRetBlit = BitBlt(hWinDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
	BOOL qRetBlit = BitBlt(hWinDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit){
		MessageBox(0, _T("Couldn't load the qRetBlit"), _T("Error"), MB_OK);
		return false;
	}
	//452 341
	StretchBlt(hWinDC, 0, 0, 500, 400, hWinDC, 0, 0, 452, 341, SRCCOPY);
	SelectObject(hLocalDC, hOldBmp);
	DeleteObject(hLocalDC);
	DeleteObject(hBitmap);
	return true;
}
bool loadImageBmp2(HDC hWinDC, LPWSTR path){
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"D:\\pic1.png", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL){
		MessageBox(0, _T("Couldn't load the image"), _T("Error"), MB_OK);
		return false;
	}

	HDC hLocalDC = CreateCompatibleDC(hWinDC);
	if (hLocalDC == NULL){
		MessageBox(0, _T("Couldn't load the hLocalDC"), _T("Error"), MB_OK);
		return false;
	}

	BITMAP qBitmap;
	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
	if (!iReturn){
		MessageBox(0, _T("Couldn't load the iReturn"), _T("Error"), MB_OK);
		return false;
	}

	HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
	if (hOldBmp == NULL){
		MessageBox(0, _T("Couldn't load the oldBMP"), _T("Error"), MB_OK);
		return false;
	}

	//BOOL qRetBlit = BitBlt(hWinDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
	BOOL qRetBlit = BitBlt(hWinDC, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
	if (!qRetBlit){
		MessageBox(0, _T("Couldn't load the qRetBlit"), _T("Error"), MB_OK);
		return false;
	}

	int x1 = 0;
	int y1 = 0;
	for (int j = 0; j < 4; j++){
		for (int i = 0; i < 7; i++){
			StretchBlt(hWinDC, x1, y1, 256, 256, hWinDC, 0, 0, 256, 256, SRCCOPY);
			x1 = x1 + 256;
		}
		x1 = 0;
		y1 = y1 + 256;
	}

	SelectObject(hLocalDC, hOldBmp);
	DeleteObject(hLocalDC);
	DeleteObject(hBitmap);
	return true;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush;
	HDC memDC;
	HBITMAP memBM;

	HBITMAP hBitmap;
	HDC hLocalDC;
	BITMAP qBitmap;
	HBITMAP hOldBmp;
	BOOL qRetBlit;
	int iReturn;

	int xHouse;
	int yHouse;
	int xGras;
	int yGras;

	biler *nyBil;
	list<biler*>::iterator k;
	list<biler*>::iterator k1;
	bool allowed = true;

	HGDIOBJ hOrg;
	switch (message)
	{
	case WM_CREATE:
		SetWindowText(hWnd, L"Trafikklys simulator - Simen Bentdal");
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 5000, NULL);
		break;
	case WM_LBUTTONDOWN:{
		int x = 0;
		bool okNew = true;
		for (k = l.begin(); k != l.end(); ++k){
			x = (*k)->getX();
			if (x <= 48)
				okNew = false;
		}
		if (okNew){
			int speed = rand() % 20 + 10;
			nyBil = new biler(false, id, speed);
			id++;
			l.push_back(nyBil);
			InvalidateRect(hWnd, 0, FALSE);
		}
		//mciSendString(L"OPEN test12.mp3 TYPE MPEGVIDEO ALIAS song1", NULL, 0, NULL);	//opens song.mp3 and set its alias to song1
		//mciSendString(L"PLAY song1 FROM 0", NULL, 0, NULL);	//plays song1 from the first frame (the beginning)
		break;
	}
	case WM_RBUTTONDOWN:{
		int y = 0;
		bool okNew = true;
		for (k = l.begin(); k != l.end(); ++k){
			y = (*k)->getY();
			if (y <= 48)
				okNew = false;
		}
		if (okNew){
			int speed = rand() % 20 + 10;
			nyBil = new biler(true, id, speed);
			id++;
			l.push_back(nyBil);
			InvalidateRect(hWnd, 0, FALSE);
		}
		break;
	}
	case WM_TIMER:
		if (receivedData){
			InvalidateRect(hWnd, 0, FALSE);
			SetTimer(hWnd, 3, 1000, NULL);
			WCHAR sz[100];
			wsprintf(sz, _T("Propability west -> east %d   Propability north -> south %d"), probabilityEast, probabilitySouth);
			SetWindowText(hWnd, sz);
			receivedData = false;
		}
		switch (wParam){
		case 1:
			for (k = l.begin(); k != l.end(); ++k){
				bool isVertical;
				if (((*k)->getX() > 700 && (*k)->getX() < 750 && redLightL == true && (*k)->getBool() == false) || ((*k)->getY() > 300 && (*k)->getY() < 350 && redLightR == true && (*k)->getBool() == true)){

				}
				else{
					l1 = l;
					for (k1 = l1.begin(); k1 != l1.end(); ++k1){
						int carX = (*k)->getX();
						int carX2 = (*k1)->getX();
						int carY = (*k)->getY();
						int carY2 = (*k1)->getY();
						isVertical = (*k)->getBool();

						if (!isVertical){
							if ((carX + 65) >= carX2 && (carX + 20) <= (carX2 + 48) && (*k)->getId() != (*k1)->getId() && (*k1)->getBool() == false){
								(*k)->setSpeed((*k1)->getSpeed());
								allowed = false;
							}
						}
						else{

							if ((carY + 65) >= carY2 && (carY + 20) <= (carY2 + 48) && (*k)->getId() != (*k1)->getId() && (*k1)->getBool() == true){
								(*k)->setSpeed((*k1)->getSpeed());
								allowed = false;
							}
						}
					}
					if (allowed){
						(*k)->move();
						RECT temp = (*k)->getRect();
						if ((*k)->getX() < 1872 || (*k)->getY() > 1060)
							InvalidateRect(hWnd, &temp, FALSE);
					}
					else
						allowed = true;
				}


			}
			tid += 1;
			break;
		case 2:
			RECT lLight;
			lLight.left = 705;
			lLight.right = 735;
			lLight.top = 305;
			lLight.bottom = 395;
			RECT rLight;
			rLight.left = 860;
			rLight.right = 890;
			rLight.top = 200;
			rLight.bottom = 290;
			test = test + 1;
			InvalidateRect(hWnd, &lLight, FALSE);
			InvalidateRect(hWnd, &rLight, FALSE);
			break;
		case 3:
			srand((unsigned)time(NULL));
			int random = rand() % 100 + 1;
			if (random <= probabilitySouth){
				int y = 0;
				bool okNew = true;
				for (k = l.begin(); k != l.end(); ++k){
					y = (*k)->getY();
					if (y <= 48)
						okNew = false;
				}
				if (okNew){
					int speed = rand() % 20 + 10;
					nyBil = new biler(true, id, speed);
					id++;
					l.push_back(nyBil);
					RECT temp = nyBil->getRect();
					InvalidateRect(hWnd, &temp, FALSE);
				}
			}

			random = rand() % 100 + 1;
			if (random <= probabilityEast){
				int x = 0;
				bool okNew = true;
				for (k = l.begin(); k != l.end(); ++k){
					x = (*k)->getX();
					if (x <= 48)
						okNew = false;
				}
				if (okNew){
					int speed = rand() % 20 + 10;
					nyBil = new biler(false, id, speed);
					id++;
					l.push_back(nyBil);
					RECT temp = nyBil->getRect();
					InvalidateRect(hWnd, &temp, FALSE);
				}
			}
			break;
		}
		break;
	case WM_ERASEBKGND:
		break;
	case WM_KEYDOWN:
		RECT probTemp;
		probTemp.top = 0;
		probTemp.bottom = 28;
		probTemp.left = 0;
		probTemp.right = 200;
		switch (wParam){
		case VK_RIGHT:

			//TCHAR buff[255];
			//TextOut(hdc, 0, 0, buff, wsprintf(buff, TEXT("Probability West -> East: %d"), probabilityEast));
			//TCHAR buff2[255];
			//TextOut(hdc, 0, 14, buff2, wsprintf(buff2, TEXT("Probability North -> South: %d"), probabilitySouth));
			if (probabilityEast < 100){
				probabilityEast += 10;
				WCHAR sz[100];
				wsprintf(sz, _T("Propability west -> east %d   Propability north -> south %d"), probabilityEast, probabilitySouth);
				//InvalidateRect(hWnd, &probTemp, FALSE);
				SetWindowText(hWnd, sz);
			}
			break;
		case VK_LEFT:
			if (probabilityEast > 0){
				probabilityEast -= 10;
				WCHAR sz[100];
				wsprintf(sz, _T("Propability west -> east %d   Propability north -> south %d"), probabilityEast, probabilitySouth);
				//InvalidateRect(hWnd, &probTemp, FALSE);
				SetWindowText(hWnd, sz);
			}
			break;
		case VK_DOWN:
			if (probabilitySouth > 0){
				probabilitySouth -= 10;
				WCHAR sz[100];
				wsprintf(sz, _T("Propability west -> east %d   Propability north -> south %d"), probabilityEast, probabilitySouth);
				//InvalidateRect(hWnd, &probTemp, FALSE);
				SetWindowText(hWnd, sz);
			}
			break;
		case VK_UP:
			if (probabilitySouth < 100){
				probabilitySouth += 10;
				WCHAR sz[100];
				wsprintf(sz, _T("Propability west -> east %d   Propability north -> south %d"), probabilityEast, probabilitySouth);
				//InvalidateRect(hWnd, &probTemp, FALSE);
				SetWindowText(hWnd, sz);
			}
			break;
		}
		break;
		/*
		*/
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_CHANGE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DLGFIRST), hWnd, (DLGPROC)DlgProc);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:{
		hdc = BeginPaint(hWnd, &ps);

		int xRes = GetDeviceCaps(hdc, HORZRES);
		int yRes = GetDeviceCaps(hdc, VERTRES);
		
		memDC = CreateCompatibleDC(hdc);
		memBM = CreateCompatibleBitmap(hdc, xRes, yRes);
		SelectObject(memDC, memBM);

		xGras = 0;
		yGras = 0;
		
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 7; j++){
				hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
				hLocalDC = CreateCompatibleDC(hdc);
				iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
				hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);

				qRetBlit = BitBlt(memDC, xGras, yGras, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
				SelectObject(hLocalDC, hOldBmp);
				DeleteObject(hLocalDC);
				DeleteObject(hBitmap);
				xGras += 256;
			}
			xGras = 0;
			yGras += 256;
		}

		//loadImageBmp(hdc, L"D:\\House.bmp");

		//ROAD left right		
		
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hOrg = SelectObject(memDC, hBrush);
		Rectangle(memDC, 0, 400, 1920, 450);
		//BitBlt(hdc, 0, 400, 1920, 50, memDC, 0, 400, SRCCOPY);

		Rectangle(memDC, 800, 0, 850, 1080);
		//BitBlt(hdc, 800, 0, 50, 1080, memDC, 800, 0, SRCCOPY);

		SelectObject(memDC, hOrg);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(255, 255, 0));		
		hOrg = SelectObject(memDC, hBrush);
		x2 = 0;
		for (int i = 0; i < 128; i++){
			Rectangle(memDC, x2, 423, (x2 + 15), 427);
			BitBlt(memDC, x2, 423, (x2 + 15), 4, memDC, x2, 423, SRCCOPY);
			x2 = x2 + 25;
		}
		x2 = 0;
		for (int i = 0; i < 70; i++){
			Rectangle(memDC, 823, x2, 826, (x2 + 15));
			BitBlt(memDC, 823, x2, 4, 15, memDC, 823, x2, SRCCOPY);
			x2 = x2 + 25;
		}
		SelectObject(memDC, hOrg);
		DeleteObject(hBrush);

		for (k = l.begin(); k != l.end(); ++k){
			if ((*k)->getBool() == false){
				hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
				hLocalDC = CreateCompatibleDC(hdc);
				iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
				hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);

				qRetBlit = BitBlt(memDC, (*k)->getX(), (*k)->getY(), qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
				SelectObject(hLocalDC, hOldBmp);
				DeleteObject(hLocalDC);
				DeleteObject(hBitmap);
			}
			else{
				hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
				hLocalDC = CreateCompatibleDC(hdc);
				iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
				hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
				//qRetBlit = PlgBlt()
				qRetBlit = BitBlt(memDC, (*k)->getX(), (*k)->getY(), qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
				SelectObject(hLocalDC, hOldBmp);
				DeleteObject(hLocalDC);
				DeleteObject(hBitmap);
			}
		}
		xHouse = 0;
		yHouse = 263;
		for (int i = 0; i < 5; i++){
			hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
			hLocalDC = CreateCompatibleDC(hdc);
			iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP), reinterpret_cast<LPVOID>(&qBitmap));
			hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);

			qRetBlit = BitBlt(memDC, xHouse, yHouse, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
			SelectObject(hLocalDC, hOldBmp);
			DeleteObject(hLocalDC);
			DeleteObject(hBitmap);
			xHouse += 140;
		}

		if (test == 4)
			test = 0;
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hOrg = SelectObject(memDC, hBrush);
		Rectangle(memDC, 705, 305, 735, 395);
		SelectObject(memDC, hOrg);
		DeleteObject(hBrush);
		if (test == 0){
			redLightL = TRUE;
			
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 305, 735, 335);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 335, 735, 365);
			Ellipse(memDC, 705, 365, 735, 395);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		else if (test == 1){
			redLightL = TRUE;
			
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 305, 735, 335);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 335, 735, 365);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 365, 735, 395);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		else if (test == 2){
			redLightL = FALSE;

			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 305, 735, 335);
			Ellipse(memDC, 705, 335, 735, 365);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			
			hBrush = CreateSolidBrush(RGB(31, 252, 7));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 365, 735, 395);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		else if (test == 3){
			// Select red brush
			redLightL = FALSE;

			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 305, 735, 335);
			Ellipse(memDC, 705, 365, 735, 395);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 705, 335, 735, 365);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}


		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		hOrg = SelectObject(memDC, hBrush);
		Rectangle(memDC, 860, 200, 890, 290);
		SelectObject(memDC, hOrg);
		DeleteObject(hBrush);
		//Green
		if (test == 0){
			redLightR = FALSE;
			// Select red brush
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 200, 890, 230);
			Ellipse(memDC, 860, 230, 890, 260);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			
			hBrush = CreateSolidBrush(RGB(31, 252, 7));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 260, 890, 290);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		//gul
		else if (test == 1){
			redLightR = FALSE;

			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 200, 890, 230);
			Ellipse(memDC, 860, 260, 890, 290);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 230, 890, 260);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		//RED LIGHT
		else if (test == 2){
			redLightR = TRUE;
			// Select red brush
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 200, 890, 230);
			
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 230, 890, 260);
			Ellipse(memDC, 860, 260, 890, 290);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		//rødgul
		else if (test == 3){
			redLightR = TRUE;
			// Select red brush
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			hOrg = SelectObject(memDC, hBrush);

			// Red circle
			Ellipse(memDC, 860, 200, 890, 230);
			// Reset original brush
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			hOrg = SelectObject(memDC, hBrush);
			// Yellow circle
			Ellipse(memDC, 860, 230, 890, 260);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
			// Green light
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			hOrg = SelectObject(memDC, hBrush);
			Ellipse(memDC, 860, 260, 890, 290);
			SelectObject(memDC, hOrg);
			DeleteObject(hBrush);
		}
		qRetBlit = BitBlt(hdc, 0, 0, xRes, yRes, memDC, 0, 0, SRCCOPY);
		DeleteObject(memDC);
		DeleteObject(memBM);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1 = NULL;
	static HWND hEdit2 = NULL;

	WORD id = LOWORD(wParam);
	switch (message) {
	case WM_INITDIALOG: // Initializing
		hEdit1 = GetDlgItem(hDlg, IDC_EAST);
		hEdit2 = GetDlgItem(hDlg, IDC_SOUTH);
		return TRUE;
	case WM_COMMAND: // Handling command events
		if (id == IDCANCEL){
			receivedData = true;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if (id == IDOK){
			int textLen = GetWindowTextLength(hEdit1);
			textLen += 1;
			GetWindowText(hEdit1, LPWSTR(data.c_str()), textLen);
			//EndDialog(hDlg, LOWORD(wParam));
			const wchar_t* szName = data.c_str();
			probabilityEast = _ttoi(szName);

			textLen = GetWindowTextLength(hEdit1);
			textLen += 1;
			GetWindowText(hEdit2, LPWSTR(data2.c_str()), textLen);
			EndDialog(hDlg, LOWORD(wParam));
			szName = data2.c_str();
			probabilitySouth = _ttoi(szName);

			receivedData = TRUE;
			return TRUE;
		}
		break;
	}
	return FALSE;
}