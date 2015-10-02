#ifndef __BUTTON_H
#define __BUTTON_H

#include <d3d9.h>
#include "common.h"

enum BtnStat{ btn_down, btn_up };

class Button{
private:
	int num;
	BtnStat status;
	Location loc;
	IDirect3DTexture9** texture_pack;

public:
	const static int WIDTH = 500;	// even only
	const static int HEIGHT = 75;	// even only
	const static int NUM = 5;
	const static int NUM_STAT = 2;

public:
	Button();
	Button(int);
	~Button();

	void Draw() const;

	int get_num() const{ return num; }
	BtnStat get_status() const{ return status; }

	void set_status(BtnStat s){ status = s; return; }
};

#endif // __BUTTON_H