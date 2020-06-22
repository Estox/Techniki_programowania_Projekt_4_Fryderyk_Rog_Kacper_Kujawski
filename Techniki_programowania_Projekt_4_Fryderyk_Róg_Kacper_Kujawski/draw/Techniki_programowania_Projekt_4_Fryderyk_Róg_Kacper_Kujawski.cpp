// draw.cpp : Defines the entry point for the application.
//Techniki programowania - Projekt 4 - Fryderyk Rog Kacper Kujawski
//Srodowisko: Microsoft Visual Studio 2019
//Kompilator: Microsoft C/C++

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <queue>
#include <windows.h>
#include <algorithm>
#include <vector>
#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// buttons
HWND hwndButton;
struct person {
	int floor_start = 400;
	int floor_destination = 400;
};

int floor_1_level = 400;
int floor_2_level = 300;
int floor_3_level = 200;
int floor_4_level = 100;
int floor_5_level = 0;
std::queue<person>passenger_floor_1;
std::queue<person>passenger_floor_2;
std::queue<person>passenger_floor_3;
std::queue<person>passenger_floor_4;
std::queue<person>passenger_floor_5;
std::queue<person>passenger_elevator;
int elevator_height = 400;

// sent data
RECT drawArea1 = { NULL };
RECT drawArea2 = { 503,0,698,510};
RECT drawAreaFloor5 = {25, 50, 495, 99};
RECT drawAreaFloor4 = { 705, 150, 1110, 199 };
RECT drawAreaFloor3 = { 25, 250, 495, 299 };
RECT drawAreaFloor2 = { 705, 350, 1110, 399 };
RECT drawAreaFloor1 = { 25, 450, 495, 499 };

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);\

int OnCreate(HWND window)
{
	return 0;
}

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 0, 0, 0), 5);
	Pen pen3(Color(255, 0, 0, 0));
	
	graphics.DrawLine(&pen, 0, floor_5_level + 100, 500, 100);
	graphics.DrawLine(&pen, 0, floor_3_level + 100, 500, 300);
	graphics.DrawLine(&pen, 0, floor_1_level + 100, 500, 500);
	graphics.DrawLine(&pen, 700, floor_4_level + 100, 1136, 200);
	graphics.DrawLine(&pen, 700, floor_2_level + 100, 1136, 400);
	
	graphics.DrawRectangle(&pen2, 500, 5, 200, 526);
}

void Counter(HDC hdc, int var)
{
	switch (var)
	{
	case 1:
		TextOut(hdc, 510, elevator_height + 5, TEXT("70--1"), 5); break;
	case 2:
		TextOut(hdc, 510, elevator_height + 5, TEXT("140-2"), 5); break;
	case 3:
		TextOut(hdc, 510, elevator_height + 5, TEXT("210-3"), 5); break;
	case 4:
		TextOut(hdc, 510, elevator_height + 5, TEXT("280-4"), 5); break;
	case 5:
		TextOut(hdc, 510, elevator_height + 5, TEXT("350-5"), 5); break;
	case 6:
		TextOut(hdc, 510, elevator_height + 5, TEXT("420-6"), 5); break;
	case 7:
		TextOut(hdc, 510, elevator_height + 5, TEXT("490-7"), 5); break;
	case 8:
		TextOut(hdc, 510, elevator_height + 5, TEXT("560-8"), 5); break;
	default:
		TextOut(hdc, 510, elevator_height + 5, TEXT("0---0"), 5); break;
	}
}

void WhichPerson(HDC hdc, int checker, int x, int y)
{
	Graphics graphics(hdc);
	Bitmap bmp1(L"person_1.jpg");
	Bitmap bmp2(L"person_2.jpg");
	Bitmap bmp3(L"person_3.jpg");
	Bitmap bmp4(L"person_4.jpg");
	Bitmap bmp5(L"person_5.jpg");
	if (checker == 400)
	{
		graphics.DrawImage(&bmp1, x, y);
	}
	else if (checker == 300)
	{
		graphics.DrawImage(&bmp2, x, y);
	}
	else if (checker == 200)
	{
		graphics.DrawImage(&bmp3, x, y);
	}
	else if (checker == 100)
	{
		graphics.DrawImage(&bmp4, x, y);
	}
	else if (checker == 0)
	{
		graphics.DrawImage(&bmp5, x, y);
	}
}

void DrawPeople(HDC hdc, std::queue<person> passenger)
{
	if (!passenger.empty())
	{
		int x , y;
		int counter = passenger.size();
		int checker = 0;

		if (passenger.front().floor_start == -5)
		{
			y = elevator_height + 40;
		}
		else
		{
			y = passenger.front().floor_start + 50;
		}

		if (y == 50 || y == 250 || y == 450)
		{
			for (int i = 0; i < counter; i++)
			{
				checker = passenger.front().floor_destination;
				x = 470 - 25 * i;
				WhichPerson(hdc, checker, x, y);
				passenger.pop();
			}
		}
		else if (y == elevator_height + 40)
		{
			for (int i = 0; i < counter; i++)
			{
				checker = passenger.front().floor_destination;
				x = 510 + 21 * i;
				WhichPerson(hdc, checker, x, y);
				passenger.pop();
			}
		}
		else
		{
			for (int i = 0; i < counter; i++)
			{
				checker = passenger.front().floor_destination;
				x = 705 + 25 * i;
				WhichPerson(hdc, checker, x, y);
				passenger.pop();
			}
		}
	}
}

void DrawElevator(HDC hdc)
{
	Graphics graphics(hdc);
	Counter(hdc, passenger_elevator.size());
	Pen pen4(Color(255, 255, 0, 0), 5);
	graphics.DrawRectangle(&pen4, 505, elevator_height, 190, 100);
	DrawPeople(hdc, passenger_elevator);
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	if(drawArea == &drawArea2)
	{ 
		DrawElevator(hdc);
	}
	else if (drawArea == &drawAreaFloor5)
	{
		DrawPeople(hdc, passenger_floor_5);
	}
	else if (drawArea == &drawAreaFloor4)
	{
		DrawPeople(hdc, passenger_floor_4);
	}
	else if (drawArea == &drawAreaFloor3)
	{
		DrawPeople(hdc, passenger_floor_3);
	}
	else if (drawArea == &drawAreaFloor2)
	{
		DrawPeople(hdc, passenger_floor_2);
	}
	else if (drawArea == &drawAreaFloor1)
	{
		DrawPeople(hdc, passenger_floor_1);
	}
	EndPaint(hWnd, &ps);
}

std::queue<person> SortPassengers(std::queue<person> passenger_elevator)
{
	person recreated;
	std::vector<int> sorting_vector;
	int x = passenger_elevator.size();
	for (int i = 0; i < x; i++)
	{
		sorting_vector.push_back(passenger_elevator.front().floor_destination);
		passenger_elevator.pop();

	}

	std::sort(sorting_vector.begin(), sorting_vector.end());

	for (int i = x - 1; i >= 0; i--)
	{
		recreated.floor_start = -5;
		recreated.floor_destination = sorting_vector[i];
		passenger_elevator.push(recreated);
	}
	return passenger_elevator;
}

void CheckingFloor(std::queue<person>&passenger_floor)
{
	while (!passenger_elevator.empty() && passenger_elevator.front().floor_destination == elevator_height)
	{
		passenger_elevator.pop();
		Sleep(200);
	};

	while (!passenger_floor.empty() && passenger_elevator.size() < 8)
	{
		passenger_elevator.push({ passenger_floor.front() });
		passenger_elevator = SortPassengers(passenger_elevator);
		passenger_floor.pop();
		Sleep(200);
	};
}

void CheckingAllFloors()
{
	if (elevator_height == floor_1_level)
	{
		CheckingFloor(passenger_floor_1);
	}
	if (elevator_height == floor_2_level)
	{
		CheckingFloor(passenger_floor_2);
	}
	if (elevator_height == floor_3_level)
	{
		CheckingFloor(passenger_floor_3);
	}
	if (elevator_height == floor_4_level)
	{
		CheckingFloor(passenger_floor_4);
	}
	if (elevator_height == floor_5_level)
	{
		CheckingFloor(passenger_floor_5);
	}
}

void DoesItAll(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	repaintWindow(hWnd, hdc, ps, drawArea);
	if (elevator_height == floor_1_level - 1)
	{
		repaintWindow(hWnd, hdc, ps, &drawAreaFloor1);
	}
	if (elevator_height == floor_2_level + 1 || elevator_height == floor_2_level - 1)
	{
		repaintWindow(hWnd, hdc, ps, &drawAreaFloor2);
	}
	if (elevator_height == floor_3_level + 1 || elevator_height == floor_3_level - 1)
	{
		repaintWindow(hWnd, hdc, ps, &drawAreaFloor3);
	}
	if (elevator_height == floor_4_level + 1 || elevator_height == floor_4_level - 1)
	{
		repaintWindow(hWnd, hdc, ps, &drawAreaFloor4);
	}
	if (elevator_height == floor_5_level + 1)
	{
		repaintWindow(hWnd, hdc, ps, &drawAreaFloor5);
	}
	Sleep(10);
	CheckingAllFloors();
}

void LoadingElevatorByFloor(int &travel, int destination, std::queue<person>& passenger_floor_checked,
	HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	while(!passenger_floor_checked.empty() && passenger_elevator.size() < 8)
	{
		int new_destination = destination;
		travel = elevator_height - new_destination;
		if (travel == 0)
		{
			CheckingFloor(passenger_floor_checked);
		}
		else if (travel < 0)
		{
			travel = -travel;
			for (int i = 0; i < travel; i++)
			{
				elevator_height++;
				DoesItAll(hWnd, hdc, ps, drawArea);
			}
		}
		else if (travel > 0)
		{
			for (int i = 0; i < travel; i++)
			{
				elevator_height--;
				DoesItAll(hWnd, hdc, ps, drawArea);
			}
		}
	}
}

void LiftingElevator(int& elevator_height, HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	int travel = 0;
	while (!passenger_elevator.empty() || !passenger_floor_1.empty() || !passenger_floor_2.empty()
		|| !passenger_floor_3.empty() || !passenger_floor_4.empty() || !passenger_floor_5.empty())
	{
		LoadingElevatorByFloor(travel, floor_1_level, passenger_floor_1, hWnd, hdc, ps, &drawArea2);
		LoadingElevatorByFloor(travel, floor_2_level, passenger_floor_2, hWnd, hdc, ps, &drawArea2);
		LoadingElevatorByFloor(travel, floor_3_level, passenger_floor_3, hWnd, hdc, ps, &drawArea2);
		LoadingElevatorByFloor(travel, floor_4_level, passenger_floor_4, hWnd, hdc, ps, &drawArea2);
		LoadingElevatorByFloor(travel, floor_5_level, passenger_floor_5, hWnd, hdc, ps, &drawArea2);

		while (passenger_elevator.size() > 0 && passenger_elevator.size() <= 8)
		{
			int new_destination;
			new_destination = passenger_elevator.front().floor_destination;
			travel = elevator_height - new_destination;
			if (travel == 0)
			{
				CheckingAllFloors();
			}
			else if (travel < 0)
			{
				travel = -travel;
				for (int i = 0; i < travel; i++)
				{
					elevator_height++;
					DoesItAll(hWnd, hdc, ps, drawArea);
				}
			}
			else if (travel > 0)
			{
				for (int i = 0; i < travel; i++)
				{
					elevator_height--;
					DoesItAll(hWnd, hdc, ps, drawArea);
				}
			}
		};
	};
}

// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
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
	hInst = hInstance; // Store instance handle (of exe) in our global variable
	HWND hWnd;
	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       

	//Floor 3
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 100,                                  // the left and top co-ordinates
		25, 25,	                         // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 125,                                  // the left and top co-ordinates
		25, 25,	                            // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 150,                                  // the left and top co-ordinates
		25, 25,	                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		0, 175,										 // the left and top co-ordinates
		25, 25,										  // width and height
		hWnd,									   // parent window handle
		(HMENU)ID_BUTTON4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	//Floor 5
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 0,                                  // the left and top co-ordinates
		25, 25,	                         // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL); // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 25,                                  // the left and top co-ordinates
		25, 25,	                            // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON6,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 50,                                  // the left and top co-ordinates
		25, 25,	                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON7,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		0, 75,										 // the left and top co-ordinates
		25, 25,										  // width and height
		hWnd,									   // parent window handle
		(HMENU)ID_BUTTON8,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	//Floor 1
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 300,                                  // the left and top co-ordinates
		25, 25,	                         // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON9,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 325,                                  // the left and top co-ordinates
		25, 25,	                            // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON10,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		0, 350,                                  // the left and top co-ordinates
		25, 25,	                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON11,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		0, 375,										 // the left and top co-ordinates
		25, 25,										  // width and height
		hWnd,									   // parent window handle
		(HMENU)ID_BUTTON12,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	//Floor 4
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1111, 75,                                  // the left and top co-ordinates
		25, 25,	                         // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON13,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1111, 100,                                  // the left and top co-ordinates
		25, 25,	                            // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON14,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("2"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1111, 125,                                  // the left and top co-ordinates
		25, 25,	                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON15,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		1111, 150,										 // the left and top co-ordinates
		25, 25,										  // width and height
		hWnd,									   // parent window handle
		(HMENU)ID_BUTTON16,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	//Floor 2
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("5"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1111, 200,                                  // the left and top co-ordinates
		25, 25,	                         // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON17,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1111, 225,                                  // the left and top co-ordinates
		25, 25,	                            // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON18,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1111, 250,                                  // the left and top co-ordinates
		25, 25,	                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON19,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("1"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		1111, 275,										 // the left and top co-ordinates
		25, 25,										  // width and height
		hWnd,									   // parent window handle
		(HMENU)ID_BUTTON20,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	// create button and store the handle 
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("START"),							    // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		705, 450,										 // the left and top co-ordinates
		100, 50,										  // width and height
		hWnd,									   // parent window handle
		(HMENU)ID_BUTTON21,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	person a;
	switch(message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:

		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
/*3  5*/case ID_BUTTON1 :
			a.floor_start = 200;
			a.floor_destination = floor_5_level;
			passenger_floor_3.push(a);
			break;
/*3  4*/case ID_BUTTON2 :
			a.floor_start = 200;
			a.floor_destination = floor_4_level;
			passenger_floor_3.push(a);
			break;
/*3	 2*/case ID_BUTTON3:			
			a.floor_start = 200;
			a.floor_destination = floor_2_level;
			passenger_floor_3.push(a);
			break;
/*3	 1*/case ID_BUTTON4:
			a.floor_start = 200;
			a.floor_destination = floor_1_level;
			passenger_floor_3.push(a);
			break;
/*5	 4*/case ID_BUTTON5:
			a.floor_start = 0;
			a.floor_destination = floor_4_level;
			passenger_floor_5.push(a);
			break;
/*5	 3*/case ID_BUTTON6:
			a.floor_start = 0;
			a.floor_destination = floor_3_level;
			passenger_floor_5.push(a);
			break;
/*5	 2*/case ID_BUTTON7:
			a.floor_start = 0;
			a.floor_destination = floor_2_level;
			passenger_floor_5.push(a);
			break;
/*5	 1*/case ID_BUTTON8:
			a.floor_start = 0;
			a.floor_destination = floor_1_level;
			passenger_floor_5.push(a);
			break;
/*1	 5*/case ID_BUTTON9:
			a.floor_start = 400;
			a.floor_destination = floor_5_level;
			passenger_floor_1.push(a);
			break;
/*1	 4*/case ID_BUTTON10:
			a.floor_start = 400;
			a.floor_destination = floor_4_level;
			passenger_floor_1.push(a);
			break;
/*1	 3*/case ID_BUTTON11:
			a.floor_start = 400;
			a.floor_destination = floor_3_level;
			passenger_floor_1.push(a);
			break;
/*1	 2*/case ID_BUTTON12:
			a.floor_start = 400;
			a.floor_destination = floor_2_level;
			passenger_floor_1.push(a);
			break;
/*4	 5*/case ID_BUTTON13:
			a.floor_start = 100;
			a.floor_destination = floor_5_level;
			passenger_floor_4.push(a);
			break;
/*4	 3*/case ID_BUTTON14:
			a.floor_start = 100;
			a.floor_destination = floor_3_level;
			passenger_floor_4.push(a);
			break;
/*4	 2*/case ID_BUTTON15:
			a.floor_start = 100;
			a.floor_destination = floor_2_level;
			passenger_floor_4.push(a);
			break;
/*4	 1*/case ID_BUTTON16:
			a.floor_start = 100;
			a.floor_destination = floor_1_level;
			passenger_floor_4.push(a);
			break;
/*2	 5*/case ID_BUTTON17:
			a.floor_start = 300;
			a.floor_destination = floor_5_level;
			passenger_floor_2.push(a);
			break;
/*2	 4*/case ID_BUTTON18:
			a.floor_start = 300;
			a.floor_destination = floor_4_level;
			passenger_floor_2.push(a);
			break;
/*2	 3*/case ID_BUTTON19:
			a.floor_start = 300;
			a.floor_destination = floor_3_level;
			passenger_floor_2.push(a);
			break;
/*2	 1*/case ID_BUTTON20:
			a.floor_start = 300;
			a.floor_destination = floor_1_level;
			passenger_floor_2.push(a);
			break;
		case ID_BUTTON21:
				repaintWindow(hWnd, hdc, ps, &drawAreaFloor1);
				repaintWindow(hWnd, hdc, ps, &drawAreaFloor2);
				repaintWindow(hWnd, hdc, ps, &drawAreaFloor3);
				repaintWindow(hWnd, hdc, ps, &drawAreaFloor4);
				repaintWindow(hWnd, hdc, ps, &drawAreaFloor5);
				LiftingElevator(elevator_height, hWnd, hdc, ps, &drawArea2);
				repaintWindow(hWnd, hdc, ps, &drawArea2);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyOnPaint(hdc);
		DrawElevator(hdc);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
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
