#ifndef __POINT_H
#define __POINT_H

#include "common.h"
#include "bar.h"

class Point{
private:
	Bdir onBarStatus;
	Location pxloc;

public:
	Point();
	Point(int, int);
	~Point();

	Bdir get_onBarStatus() const{ return onBarStatus; }
	Location get_pxloc() const{ return pxloc; }

	void set_onBarStatus(Bdir s){ onBarStatus = s; return; }
};

#endif // __POINT_H