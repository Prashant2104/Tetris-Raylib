#pragma once
#include "raylib.h"

class UI {
public:
	UI();

	void Setup();
	void DrawUI();
	void UpdateScoreText(int score);
	void CanSwap(bool can);
	void DrawGameOverScreen();
private:
	void DisplayScore();
	void NextBlockHolder();
	void HeldBlockHolder();
	void ShowControls();
private:
	Font HeadingFont;
	Font DetailFont;

	Texture2D LockedIcon;
	Texture2D UnlockedIcon;
	Texture2D GameEndSS;

	char scoreText[10];
	bool canSwap;
	bool gameOver;
};