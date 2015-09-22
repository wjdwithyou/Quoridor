#ifndef __BAR_H
#define __BAR_H

#include <d3d9.h>
#include "common.h"

enum Bstat{ b_down, b_up, b_clicked };

class Bar{
private:
	Bstat status;
	Location loc;
	IDirect3DTexture9* texture_;

public:
	Bar();
	Bar(Bstat, Location);
	~Bar();

	void DrawBar() const;
};

#endif // __BAR_H