#include "common.h"

int CooToPxl(int point, int coo){
	return coo * 65 + point;
}

int PxlToCoo(int point, float pxl){
	int q = (pxl - point) / 65;
	int r = static_cast<int>(pxl - point) % 65;

	if (q < 0 || q > 8)
		return -1;
	if (60 <= r && r <= 64)
		return -1;

	return q;
}