#ifndef __DEBUG_H
#define __DEBUG_H

#include <Windows.h>

class Debug{
private:
	const int FPS_SPACE;

public:
	char sz_fps[16];

	char sz_cturn[16];
	char sz_pxl_x[16];
	char sz_pxl_y[16];
	char sz_loc_x[16];
	char sz_loc_y[16];
	char sz_mstat[16];

	char sz_temp1[16];
	char sz_temp2[16];
	char sz_temp3[16];
	char sz_temp4[16];

public:
	Debug();
	~Debug();

	float CalcFPS() const;
	void PrintFPS(RECT) const;
	void PrintValue(RECT) const;
};

#endif // __DEBUG_H