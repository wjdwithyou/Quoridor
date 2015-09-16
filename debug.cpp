#include "debug.h"
#include "dxfunc.h"

Debug::Debug()
	: FPS_SPACE(20){

}

Debug::~Debug(){}

float Debug::CalcFPS() const{
	static int cnt = 0;
	static DWORD curr_time = 0, prev_time = 0, elapsed = 0;
	static float fps = 0.0f;

	prev_time = curr_time;
	curr_time = timeGetTime();
	cnt++;
	elapsed += curr_time - prev_time;

	if(elapsed >= 1000) {
		 fps = cnt * 1000.0f / elapsed;
		 elapsed = 0;
		 cnt = 0;
	}

	return fps;
}

void Debug::PrintFPS(RECT rc) const{
	rc.top += FPS_SPACE;
	rc.right -= FPS_SPACE;
	Font->DrawTextA(Sprite, sz_fps, -1, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));

	rc.top += 2;
	rc.right -= 2;
	Font->DrawTextA(Sprite, sz_fps, -1, &rc, DT_RIGHT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));

	return;
}

void Debug::PrintValue(RECT rc) const{
	rc.top += 200;
	Font->DrawTextA(Sprite, sz_cturn, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	rc.top += 40;
	Font->DrawTextA(Sprite, sz_pxl_x, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	rc.top += 20;
	Font->DrawTextA(Sprite, sz_pxl_y, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	rc.top += 20;
	Font->DrawTextA(Sprite, sz_loc_x, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	rc.top += 20;
	Font->DrawTextA(Sprite, sz_loc_y, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	rc.top += 40;
	Font->DrawTextA(Sprite, sz_mstat, -1, &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));

	return;
}