#ifndef __SOUND_H
#define __SOUND_H

#include <audiere.h>

#pragma comment(lib, "audiere.lib")

using namespace audiere;

/***************************************************
	http://audiere.sourceforge.net/download.php
***************************************************/

class Sound{
private:
	AudioDevicePtr Audio;

public:
	OutputStreamPtr bgm;

	OutputStreamPtr test1;
	OutputStreamPtr test2;
	OutputStreamPtr test3;
	OutputStreamPtr test4;

	OutputStreamPtr BlockSound;

public:
	Sound();
	~Sound();

	void InitializeSound();

	//AudioDevicePtr get_Audio() { return Audio; }
};

#endif // __SOUND_H