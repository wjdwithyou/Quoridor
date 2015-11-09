#include "sound.h"
#include "common.h"

Sound::Sound()
	: Audio(NULL), bgm(NULL), test1(NULL), test2(NULL), test3(NULL), test4(NULL)
{
	InitializeSound();
}

Sound::~Sound(){}

void Sound::InitializeSound(){
	Audio = OpenDevice();

	if (!Audio){
		MessageBox(hWnd, "AudiereDevice Init - Failed", "Error", MB_OK);
		return;
	}

	bgm = OpenSound(Audio, "Sound/Maid with the Flaxen Hair.mp3", true); // stream on
	bgm->setRepeat(true);

	test1 = OpenSound(Audio, "Sound/fs1.wav", false);
	test2 = OpenSound(Audio, "Sound/fs2.wav", false);
	test3 = OpenSound(Audio, "Sound/fs3.wav", false);
	test4 = OpenSound(Audio, "Sound/fs4.wav", false);

	BlockSound = OpenSound(Audio, "Sound/Shieldbearer.mp3", false);
	
	return;
}