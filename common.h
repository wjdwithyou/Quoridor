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

const int WindowWidth = 1024;
const int WindowHeight = 768;

// TODO: for Location, need operator overloading (==)
typedef struct Location{
	int x;
	int y;
}Location;

Location CooToPxl(Location);
Location PxlToCoo(Location);
bool CheckCooRange(Location);

#endif // __COMMON_H