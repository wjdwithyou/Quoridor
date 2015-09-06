#ifndef __API_H
#define __API_H

#include <Windows.h>
#include "mouse.h"

extern HWND hWnd;
extern MSG Message;

extern Mouse* mouse;

const int WindowWidth = 1024;
const int WindowHeight = 768;

#endif // __API_H