#include "fps.h"
#include <Windows.h>

const int FPS_SPACE = 20;

char sz_fps[16];

float CalcFPS(){
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