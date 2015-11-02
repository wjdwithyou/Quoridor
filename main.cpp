#include <stdlib.h>
#include <time.h>
#include "mouse.h"
#include "common.h"
#include "process.h"

#include "dxfunc.h"	/////
#include "Image.h"	/////

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "winmm")
#pragma comment (lib, "dxguid")
#pragma comment (lib, "dinput8")

//void KeyInput();
void GameLoop();
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int nCmdShow){
	WNDCLASS WndClass;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = "Quoridor+";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	srand((unsigned)time(NULL));
	
	if (!RegisterClass(&WndClass)){
		MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}

	hWnd = CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, NULL, NULL, WindowWidth + 6, WindowHeight + 32, NULL, NULL, WndClass.hInstance, NULL);
	
	if (!hWnd){
		MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}
	
	InitializeDevice();

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	image->LoadTextures();



	Process** processList;
	Process* curProcess;

	Process().InitList(&processList, &curProcess);

	/*
	g_process = p_menu;
	g_process_test = &curProcess;
	curProcess = processList[g_process];
	*/

	while (Message.message != WM_QUIT){
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		curProcess->Loop();

		/*
		switch (Process::status){
		case p_menu:
			process->MenuLoop();
			break;

		case p_game:
			process->GameLoop();
			break;

		default:
			break;
		}
		*/
	}

	// TO DELETE/Free/Release LIST
	// Board::board[9][9]
	// _board
	// characters	+	vector moveableList
	// players	+ barList
	// IDirect3DTexture** square, character
	// etc.

	image->ReleaseTextures();
	ReleaseDevice();

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage){
	case WM_LBUTTONDOWN:
		g_mouse->Click();
		break;
	/*
	case WM_LBUTTONUP:
		break;
	*/
	case WM_RBUTTONDOWN:
		g_mouse->R_Click();
		break;

	case WM_MOUSEMOVE:
		g_mouse->__set_loc(LOWORD(lParam), HIWORD(lParam));
		g_mouse->CheckOnButton();
		g_mouse->CheckOnBar();
		g_mouse->CheckAroundPoint();
		break;

	case WM_MOUSEWHEEL:
		g_mouse->Wheel(((SHORT)HIWORD(wParam) > 0)? true: false);	// up(+), down(-)
		break;
		
	case WM_KEYDOWN:
		/*
		if(wParam == VK_ESCAPE) {
			DestroyWindow(hWnd);
			return 0;
		}
		*/
		if(wParam == 'P') {
			// pause?
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

/*
void KeyInput() {
	//Ű�Է��� �ް� ���� Ű�Է¿� ���� ó���� �����ϴ� �Լ�
	//���⼭ ������ winapi���� ���� ���� �Լ��� GetAsyncKeyState�� ��

	//���ϰ��� ���캸��
	//GetAsyncKeyState�� Ű�� ������ �� GetAsyncKeyState�� 0x8000 bit�� 1�̵ȴ�.
	//GetAsyncKeyState�� ȣ��Ǿ��� ������ ���� GetAsyncKeyState�� ȣ��� ������ 
	//Ű�� ��� ���� �ִ� ���¶�� 0x0001 bit�� 0, �׷��� ���� ���� 1�� �ȴ�.

	//�����ϰ� ��Ʈ�����ڸ� �̿��ؼ� ���ϰ��� Ȯ���ϴµ� ���־��̴� 2���� ��츦 ���� ���
	//if((GetAsyncKeyState(���ϴ�Ű) & 0x8001) == 0x8001) <-Ű�� �� ���� ����(���� ������ true)
	//if(GetAsyncKeyState(���ϴ�Ű) & 0x8000) <- Ű�� ���� ����(������ �ִ� ���� ��� true)
	//���� ����� �� �ִ�. �����غ��̸� ���� 2��츸 ����ϸ� ��

	//���ڰ��� ���� Ű�� ���ϴµ� �ƽ�Ű�ڵ带 ���ϸ�
	//GetAsyncKeyState('a') , GetAsyncKeyState('b') �̷��� ��������ǥ�� �̿��ؼ�
	//Ư���� Ű�� ���ϸ�
	//GetAsyncKeyState(VK_ESC), GetAsyncKeyState(VK_RETURN)  //������� esc�� ����
	//�̷��� �̸� ���ǵǾ��ִ� ����� ����.

	if((GetAsyncKeyState(VK_SPACE) & 0x8001) == 0x8001) {
		//�����̽��� ���� ������ ���Ѵ�.
	}

	if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
	}

	if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	}
}
*/

void GameLoop() {
	// impl.
}

// �� �ı�
// bar ����
// �̵� + 1
// �� 2�� ��ġ
// ...

/*
	// �� Ȯ��
		char testtest[128];
		sprintf(testtest, "%d", pn);
		MessageBox(hWnd, testtest, 0, MB_OK);
*/