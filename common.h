#ifndef __COMMON_H
#define __COMMON_H

typedef struct Location{
	int x;
	int y;
}Location;

Location CooToPxl(Location);
Location PxlToCoo(Location);

#endif // __COMMON_H