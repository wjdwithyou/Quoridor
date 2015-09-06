#ifndef __COMMON_H
#define __COMMON_H

typedef struct Location{
	int x;
	int y;
}Location;

int CooToPxl(int, int);
int PxlToCoo(int, float);

#endif // __COMMON_H