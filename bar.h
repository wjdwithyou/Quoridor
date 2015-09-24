#ifndef __BAR_H
#define __BAR_H

#include <d3d9.h>
#include "common.h"

enum Bstat{ b_down, b_up, b_clicked };

class Bar{
private:
	static Location size;

	Bstat status;
	Location loc;
	IDirect3DTexture9* texture_;

public:
	const static int _BOARD = 50;	// board-bar
	const static int _BAR = 15;		// bar-bar

public:
	Bar();
	Bar(Bstat, Location);
	~Bar();

	void DrawBar() const;

	Location get_loc() const{ return loc; }		// for debug!
};

#endif // __BAR_H