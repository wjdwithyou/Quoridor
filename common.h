#ifndef __COMMON_H
#define __COMMON_H

class Image;
class Player;
class Debug;

extern Image* image;
extern Debug* debug;

extern Player* turn;

typedef struct Location{
	int x;
	int y;
}Location;

Location CooToPxl(Location);
Location PxlToCoo(Location);
bool CheckCooRange(Location);

#endif // __COMMON_H