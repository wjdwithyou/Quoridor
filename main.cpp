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

	Process* process = new Process(WndClass);

	while (Message.message != WM_QUIT){
		if (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)){
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

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
		mouse->Click();
		break;
	/*
	case WM_LBUTTONUP:
		break;
	*/
	case WM_RBUTTONDOWN:
		mouse->R_Click();
		break;

	case WM_MOUSEMOVE:
		mouse->__set_loc(LOWORD(lParam), HIWORD(lParam));
		mouse->CheckOnButton();
		mouse->CheckOnBar();
		mouse->CheckAroundPoint();
		break;

	case WM_MOUSEWHEEL:
		mouse->Wheel(((SHORT)HIWORD(wParam) > 0)? true: false);	// up(+), down(-)
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
	//키입력을 받고 받은 키입력에 따라 처리를 결정하는 함수
	//여기서 간단한 winapi에서 쓰기 쉬운 함수인 GetAsyncKeyState를 씀

	//리턴값을 살펴보면
	//GetAsyncKeyState는 키가 눌렸을 때 GetAsyncKeyState의 0x8000 bit가 1이된다.
	//GetAsyncKeyState가 호출되었을 때부터 다음 GetAsyncKeyState가 호출될 때까지 
	//키가 계속 눌려 있는 상태라면 0x0001 bit는 0, 그렇지 않은 경우는 1이 된다.

	//간단하게 비트연산자를 이용해서 리턴값을 확인하는데 자주쓰이는 2가지 경우를 예로 들면
	//if((GetAsyncKeyState(원하는키) & 0x8001) == 0x8001) <-키가 막 눌린 상태(누른 순간만 true)
	//if(GetAsyncKeyState(원하는키) & 0x8000) <- 키가 눌린 상태(눌리고 있는 동안 계속 true)
	//같이 사용할 수 있다. 복잡해보이면 위의 2경우만 사용하면 됨

	//인자값은 눌린 키를 뜻하는데 아스키코드를 원하면
	//GetAsyncKeyState('a') , GetAsyncKeyState('b') 이렇게 작은따옴표를 이용해서
	//특수한 키를 원하면
	//GetAsyncKeyState(VK_ESC), GetAsyncKeyState(VK_RETURN)  //순서대로 esc와 엔터
	//이렇게 미리 정의되어있는 상수를 슨다.

	if((GetAsyncKeyState(VK_SPACE) & 0x8001) == 0x8001) {
		//스페이스가 눌린 순간을 뜻한다.
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

// 벽 파괴
// bar 생성
// 이동 + 1
// 벽 2개 설치
// ...