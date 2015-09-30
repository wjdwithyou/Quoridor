#ifndef __COMMON_H
#define __COMMON_H

#include <Windows.h>

class Image;
class Mouse;
class Player;
class Debug;

extern HWND hWnd;
extern MSG Message;

extern Image* image;
extern Mouse* mouse;
extern Debug* debug;

extern Player* turn;

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