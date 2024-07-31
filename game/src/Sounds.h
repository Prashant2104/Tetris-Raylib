#pragma once
#include "raylib.h"

class Sounds {
public:
	void Setup();

	void BlockMove();
	void BlockPlace();
	void BlockSwap();
	void LineClear();
	void GameOver();
	void PlayBgm();
private:
	Sound SFX_BlockMove, SFX_BlockPlace, SFX_BlockSwap, SFX_LineClear, SFX_GameOver;

	Music BGM;
};