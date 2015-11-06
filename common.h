#ifndef __COMMON_H
#define __COMMON_H

#include <Windows.h>
#include "process.h"

class Image;
class Sound;
class Mouse;
class Player;
class Debug;

extern HWND hWnd;
extern MSG Message;

extern Image* image;
extern Sound* sound;
extern Debug* debug;

extern Mouse* g_mouse;

extern Pstat g_process;
extern Process** g_process_cur;
extern Process** g_process_list0;

extern Player** g_turn;

extern int ending;	/////

const int WindowWidth = 1024;	// even only
const int WindowHeight = 768;	// even only

const float PI = 3.141592f;

typedef struct Location{
	int x;
	int y;
}Location;

Location CooToPxl(int, int, int);
Location CooToPxl(Location, int);
Location PxlToCoo(Location, int);
bool CheckCooRange(Location, int);
bool CheckCooRangeAdditional(Location);

//bool operator==(Location&, Location&);

#endif // __COMMON_H