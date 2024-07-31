#include "Sounds.h"

void Sounds::Setup()
{
	SFX_BlockMove = LoadSound("resources/Sounds/MoveRot.mp3");
	SFX_BlockSwap = LoadSound("resources/Sounds/Swap.wav");
	SFX_BlockPlace = LoadSound("resources/Sounds/BlockPlace.mp3");
	SFX_GameOver = LoadSound("resources/Sounds/GameOver.mp3");
	SFX_LineClear = LoadSound("resources/Sounds/LineClear.mp3");

	BGM = LoadMusicStream("resources/Sounds/BGM.wav");
	if (IsMusicReady(BGM)) {
		PlayMusicStream(BGM);
	}
}

void Sounds::BlockMove()
{
	if(IsSoundReady(SFX_BlockMove))  //&& !IsSoundPlaying(SFX_BlockMove))
		PlaySound(SFX_BlockMove);  
}								   
								   
void Sounds::BlockPlace()		   
{								   
	if (IsSoundReady(SFX_BlockPlace))// && !IsSoundPlaying(SFX_BlockPlace))
		PlaySound(SFX_BlockPlace);
}								   
								   
void Sounds::BlockSwap()		   
{								   
	if (IsSoundReady(SFX_BlockSwap)) // && !IsSoundPlaying(SFX_BlockSwap))
		PlaySound(SFX_BlockSwap); 
}								  
								  
void Sounds::LineClear()		  
{								  
	if (IsSoundReady(SFX_LineClear)) // && !IsSoundPlaying(SFX_LineClear))
		PlaySound(SFX_LineClear); 
}								  
								  
void Sounds::GameOver()			  
{								  
	if (IsSoundReady(SFX_GameOver))  //&& !IsSoundPlaying(SFX_GameOver))
		PlaySound(SFX_GameOver);
}

void Sounds::PlayBgm()
{
	UpdateMusicStream(BGM);
}
